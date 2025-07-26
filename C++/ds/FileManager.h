// FileManager.h
#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <system_error>
#include <cerrno>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <algorithm>
#include <optional>
#include <bit>
#include <cassert>

namespace storage {

enum class FileOpenMode { CACHED, DIRECT_IO, ASYNC_BUFFERED };
enum class FlushMode { NONE, DATA_ONLY, FULL_SYNC };
enum class FileType { WRITE_AHEAD_LOG, BLOCK_METADATA, SORTED_RUN, INDEX_FILE, TEMP_FILE };
enum class WALOpType : uint8_t { PUT = 1, DELETE = 2 };

/*
 FileManager: POSIX-focused file handle wrapper.
 - Owns a file descriptor.
 - Provides read/pread/write/preallocate/flush/seek/size/etc.
 - All direct system calls are inside this class.
*/
class FileManager {
public:
    explicit FileManager(std::string path = {},
                         FileOpenMode mode = FileOpenMode::CACHED,
                         FileType type = FileType::SORTED_RUN,
                         size_t buffer_size = 64 * 1024)
        : path_(std::move(path)),
          mode_(mode),
          type_(type),
          buffer_size_(buffer_size),
          fd_(-1),
          file_pos_(0)
    {
        // nothing else — call openForWrite/openForRead explicitly
    }

    ~FileManager() {
        try { close(); } catch (...) {}
    }

    FileManager(const FileManager&) = delete;
    FileManager& operator=(const FileManager&) = delete;
    FileManager(FileManager&& o) noexcept
        : path_(std::move(o.path_)),
          mode_(o.mode_),
          type_(o.type_),
          buffer_size_(o.buffer_size_),
          fd_(o.fd_),
          file_pos_(o.file_pos_)
    {
        o.fd_ = -1;
        o.file_pos_ = 0;
    }
    FileManager& operator=(FileManager&& o) noexcept {
        if (this != &o) {
            close();
            path_ = std::move(o.path_);
            mode_ = o.mode_;
            type_ = o.type_;
            buffer_size_ = o.buffer_size_;
            fd_ = o.fd_;
            file_pos_ = o.file_pos_;
            o.fd_ = -1;
            o.file_pos_ = 0;
        }
        return *this;
    }

    // open for write (create/truncate/append)
    void openForWrite(bool append = false, bool create = true) {
        int flags = O_WRONLY;
        if (create) flags |= O_CREAT;
        if (append) flags |= O_APPEND;
        else flags |= O_TRUNC;

        if (mode_ == FileOpenMode::DIRECT_IO) {
#ifdef O_DIRECT
            flags |= O_DIRECT;
#endif
        }
        if (mode_ == FileOpenMode::ASYNC_BUFFERED) {
#ifdef O_ASYNC
            flags |= O_ASYNC;
#endif
        }

        fd_ = ::open(path_.c_str(), flags, 0644);
        if (fd_ < 0) throw std::system_error(errno, std::system_category(), "openForWrite failed: " + path_);
        file_pos_ = append ? lseek(fd_, 0, SEEK_END) : 0;
    }

    // open for read-only
    void openForRead() {
        int flags = O_RDONLY;
        if (mode_ == FileOpenMode::DIRECT_IO) {
#ifdef O_DIRECT
            flags |= O_DIRECT;
#endif
        }
        fd_ = ::open(path_.c_str(), flags);
        if (fd_ < 0) throw std::system_error(errno, std::system_category(), "openForRead failed: " + path_);
        file_pos_ = 0;
    }

    bool isOpen() const { return fd_ >= 0; }

    // low-level writes (immediate)
    // returns bytes written or throws on error
    ssize_t writeRaw(const void* data, size_t size) {
        if (fd_ < 0) throw std::runtime_error("writeRaw: file not open");
        ssize_t n = ::write(fd_, data, size);
        if (n < 0) throw std::system_error(errno, std::system_category(), "writeRaw failed");
        file_pos_ += n;
        return n;
    }

    // convenience: writeFully (throws on short write)
    void writeFully(const void* data, size_t size) {
        const uint8_t* p = static_cast<const uint8_t*>(data);
        size_t remaining = size;
        while (remaining > 0) {
            ssize_t n = writeRaw(p, remaining);
            if (n <= 0) throw std::runtime_error("writeFully failed");
            p += n;
            remaining -= static_cast<size_t>(n);
        }
    }

    // low-level read
    ssize_t readRaw(void* buffer, size_t size) {
        if (fd_ < 0) throw std::runtime_error("readRaw: file not open");
        ssize_t n = ::read(fd_, buffer, size);
        if (n < 0) throw std::system_error(errno, std::system_category(), "readRaw failed");
        file_pos_ += n;
        return n;
    }

    // pread (does not change file_pos_)
    ssize_t preadRaw(void* buffer, size_t size, off_t offset) const {
        if (fd_ < 0) throw std::runtime_error("preadRaw: file not open");
        ssize_t n = ::pread(fd_, buffer, size, offset);
        if (n < 0) throw std::system_error(errno, std::system_category(), "preadRaw failed");
        return n;
    }

    // seek (and update file_pos_)
    off_t seek(off_t offset, int whence = SEEK_SET) {
        if (fd_ < 0) throw std::runtime_error("seek: file not open");
        off_t r = lseek(fd_, offset, whence);
        if (r < 0) throw std::system_error(errno, std::system_category(), "seek failed");
        file_pos_ = r;
        return r;
    }

    // get current position
    off_t tell() const { return file_pos_; }

    // get file size
    size_t size() const {
        if (fd_ < 0) throw std::runtime_error("size: file not open");
        struct stat st;
        if (fstat(fd_, &st) < 0) throw std::system_error(errno, std::system_category(), "fstat failed");
        return static_cast<size_t>(st.st_size);
    }

    // preallocate
    void preallocate(size_t sz) {
#ifdef __linux__
        if (fallocate(fd_, 0, 0, static_cast<off_t>(sz)) < 0) {
            // fallback
            if (ftruncate(fd_, static_cast<off_t>(sz)) < 0) throw std::system_error(errno, std::system_category(), "preallocate failed");
        }
#else
        if (ftruncate(fd_, static_cast<off_t>(sz)) < 0) throw std::system_error(errno, std::system_category(), "preallocate failed");
#endif
    }

    // flush/durability
    void flush(FlushMode mode = FlushMode::DATA_ONLY) {
        if (fd_ < 0) throw std::runtime_error("flush: file not open");
        if (mode == FlushMode::NONE) return;
        if (mode == FlushMode::DATA_ONLY) {
#ifdef __APPLE__
            if (fcntl(fd_, F_FULLFSYNC) < 0) throw std::system_error(errno, std::system_category(), "flush DATA_ONLY failed");
#else
            if (fdatasync(fd_) < 0) throw std::system_error(errno, std::system_category(), "flush DATA_ONLY failed");
#endif
        } else {
            if (fsync(fd_) < 0) throw std::system_error(errno, std::system_category(), "flush FULL_SYNC failed");
        }
    }

    // POSIX advice helpers (no-ops if not available)
    void adviseSequential() const {
#ifdef POSIX_FADV_SEQUENTIAL
        posix_fadvise(fd_, 0, 0, POSIX_FADV_SEQUENTIAL);
#endif
    }
    void adviseRandom() const {
#ifdef POSIX_FADV_RANDOM
        posix_fadvise(fd_, 0, 0, POSIX_FADV_RANDOM);
#endif
    }
    void adviseWillNeed(off_t off, size_t len) const {
#ifdef POSIX_FADV_WILLNEED
        posix_fadvise(fd_, off, len, POSIX_FADV_WILLNEED);
#endif
    }
    void adviseDontNeed(off_t off, size_t len) const {
#ifdef POSIX_FADV_DONTNEED
        posix_fadvise(fd_, off, len, POSIX_FADV_DONTNEED);
#endif
    }

    // close
    void close() {
        if (fd_ >= 0) {
            ::close(fd_);
            fd_ = -1;
            file_pos_ = 0;
        }
    }

    // expose fd for advanced uses (careful)
    int fd() const { return fd_; }
    const std::string& path() const { return path_; }

private:
    std::string path_;
    FileOpenMode mode_;
    FileType type_;
    size_t buffer_size_;

    int fd_;
    off_t file_pos_;
};

} // namespace storage