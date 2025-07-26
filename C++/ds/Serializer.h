#pragma once

#include <cstdint>
#include <cstring>
#include <span>
#include <string>
#include <optional>
#include <vector>
#include <bit>
#include <stdexcept>
#include <concepts>

using std::byte;

// ---------------------------------------------------------------------------
// Types (adjust if needed)
// ---------------------------------------------------------------------------
using LSN = uint64_t;
using Key = std::string;
using Value = std::string;

enum class WALOpType : uint8_t { NONE = 0, PUT = 1, DELETE = 2 };

struct WALEntry {
    LSN lsn = 0;
    WALOpType op = WALOpType::NONE;
    Key key;
    std::optional<Value> value;  // only for PUT
};

struct BlockMetadata {
    Key minKey;
    Key maxKey;
    uint64_t offset = 0;
    uint32_t size = 0;
    uint32_t compressedSize = 0;
    struct Bloom {
        size_t numBits = 0;
        size_t numHashes = 0;
        std::vector<uint8_t> bits;
    } bloom;
};

struct SSTableEntry {
    std::string key;
    std::string value;
    bool tombstone = false;
    uint64_t seqNum = 0;
};

// ---------------------------------------------------------------------------
// Serializer – Zero-copy, Raw Buffer API
// ---------------------------------------------------------------------------
class Serializer {
public:
    // --- Varint (LEB128) ---
    static inline byte* putVarint(byte* dst, byte* dst_end, uint64_t val) {
        do {
            if (dst >= dst_end) return nullptr;
            uint8_t byte = val & 0x7F;
            val >>= 7;
            if (val != 0) byte |= 0x80;
            *dst++ = static_cast<byte>(byte);
        } while (val != 0);
        return dst;
    }

    static inline const byte* getVarint(const byte* src, const byte* src_end, uint64_t& out) {
        out = 0;
        int shift = 0;
        while (src < src_end) {
            uint8_t b = static_cast<uint8_t>(*src++);
            out |= static_cast<uint64_t>(b & 0x7F) << shift;
            if ((b & 0x80) == 0) return src;
            shift += 7;
            if (shift >= 64) return nullptr;  // overflow
        }
        return nullptr;
    }

    // --- Fixed-size primitive (big-endian) ---
    template<typename T>
        requires (std::is_arithmetic_v<T> || std::is_enum_v<T>) && sizeof(T) <= 8
    static inline byte* putFixed(byte* dst, byte* dst_end, T val) {
        if (dst + sizeof(T) > dst_end) return nullptr;
        if constexpr (sizeof(T) > 1) {
            if constexpr (std::endian::native == std::endian::little) {
                val = std::byteswap(val);
            }
        }
        std::memcpy(dst, &val, sizeof(T));
        return dst + sizeof(T);
    }

    template<typename T>
        requires (std::is_arithmetic_v<T> || std::is_enum_v<T>) && sizeof(T) <= 8
    static inline const byte* getFixed(const byte* src, const byte* src_end, T& out) {
        if (src + sizeof(T) > src_end) return nullptr;
        std::memcpy(&out, src, sizeof(T));
        src += sizeof(T);
        if constexpr (sizeof(T) > 1) {
            if constexpr (std::endian::native == std::endian::little) {
                out = std::byteswap(out);
            }
        }
        return src;
    }

    // --- String ---
    static inline byte* putString(byte* dst, byte* dst_end, const std::string& s) {
        dst = putVarint(dst, dst_end, s.size());
        if (!dst || dst + s.size() > dst_end) return nullptr;
        std::memcpy(dst, s.data(), s.size());
        return dst + s.size();
    }

    static inline const byte* getString(const byte* src, const byte* src_end, std::string& out) {
        uint64_t len = 0;
        src = getVarint(src, src_end, len);
        if (!src || src + len > src_end) return nullptr;
        out.assign(reinterpret_cast<const char*>(src), len);
        return src + len;
    }

    // --- Optional<T> ---
    template<typename T, typename PutFn>
    static inline byte* putOptional(byte* dst, byte* dst_end, const std::optional<T>& opt, PutFn putFn) {
        bool has = opt.has_value();
        dst = putFixed(dst, dst_end, has);
        if (!dst) return nullptr;
        if (has) return putFn(dst, dst_end, *opt);
        return dst;
    }

    template<typename T, typename GetFn>
    static inline const byte* getOptional(const byte* src, const byte* src_end, std::optional<T>& out, GetFn getFn) {
        bool has = false;
        src = getFixed(src, src_end, has);
        if (!src) return nullptr;
        if (has) {
            T val{};
            src = getFn(src, src_end, val);
            if (!src) return nullptr;
            out = std::move(val);
        } else {
            out = std::nullopt;
        }
        return src;
    }

    // --- Vector<uint8_t> ---
    static inline byte* putVector(byte* dst, byte* dst_end, const std::vector<uint8_t>& v) {
        dst = putVarint(dst, dst_end, v.size());
        if (!dst || dst + v.size() > dst_end) return nullptr;
        std::memcpy(dst, v.data(), v.size());
        return dst + v.size();
    }

    static inline const byte* getVector(const byte* src, const byte* src_end, std::vector<uint8_t>& out) {
        uint64_t len = 0;
        src = getVarint(src, src_end, len);
        if (!src || src + len > src_end) return nullptr;
        out.assign(src, src + len);
        return src + len;
    }

    // ---------------------------------------------------------------------------
    // WALEntry
    // ---------------------------------------------------------------------------
    static inline byte* putWALEntry(byte* dst, byte* dst_end, const WALEntry& e) {
        dst = putFixed(dst, dst_end, e.lsn);
        if (!dst) return nullptr;
        dst = putFixed(dst, dst_end, static_cast<uint8_t>(e.op));
        if (!dst) return nullptr;
        dst = putString(dst, dst_end, e.key);
        if (!dst) return nullptr;
        auto putValue = [](byte* d, byte* de, const Value& v) { return putString(d, de, v); };
        dst = putOptional(dst, dst_end, e.value, putValue);
        return dst;
    }

    static inline const byte* getWALEntry(const byte* src, const byte* src_end, WALEntry& e) {
        src = getFixed(src, src_end, e.lsn);
        if (!src) return nullptr;
        uint8_t op = 0;
        src = getFixed(src, src_end, op);
        if (!src) return nullptr;
        e.op = static_cast<WALOpType>(op);
        src = getString(src, src_end, e.key);
        if (!src) return nullptr;
        auto getValue = [](const byte* s, const byte* se, Value& v) { return getString(s, se, v); };
        src = getOptional(src, src_end, e.value, getValue);
        return src;
    }

    // ---------------------------------------------------------------------------
    // SSTableEntry (SortedRun data block)
    // ---------------------------------------------------------------------------
    static inline byte* putSSTableEntry(byte* dst, byte* dst_end, const SSTableEntry& e) {
        dst = putString(dst, dst_end, e.key);
        if (!dst) return nullptr;
        dst = putString(dst, dst_end, e.value);
        if (!dst) return nullptr;
        dst = putFixed(dst, dst_end, e.tombstone);
        if (!dst) return nullptr;
        dst = putFixed(dst, dst_end, e.seqNum);
        return dst;
    }

    static inline const byte* getSSTableEntry(const byte* src, const byte* src_end, SSTableEntry& e) {
        src = getString(src, src_end, e.key);
        if (!src) return nullptr;
        src = getString(src, src_end, e.value);
        if (!src) return nullptr;
        src = getFixed(src, src_end, e.tombstone);
        if (!src) return nullptr;
        src = getFixed(src, src_end, e.seqNum);
        return src;
    }

    // ---------------------------------------------------------------------------
    // BlockMetadata (footer)
    // ---------------------------------------------------------------------------
    static inline byte* putBlockMetadata(byte* dst, byte* dst_end, const BlockMetadata& m) {
        dst = putString(dst, dst_end, m.minKey);
        if (!dst) return nullptr;
        dst = putString(dst, dst_end, m.maxKey);
        if (!dst) return nullptr;
        dst = putFixed(dst, dst_end, m.offset);
        if (!dst) return nullptr;
        dst = putFixed(dst, dst_end, m.size);
        if (!dst) return nullptr;
        dst = putFixed(dst, dst_end, m.compressedSize);
        if (!dst) return nullptr;
        dst = putFixed(dst, dst_end, m.bloom.numBits);
        if (!dst) return nullptr;
        dst = putFixed(dst, dst_end, m.bloom.numHashes);
        if (!dst) return nullptr;
        dst = putVector(dst, dst_end, m.bloom.bits);
        return dst;
    }

    static inline const byte* getBlockMetadata(const byte* src, const byte* src_end, BlockMetadata& m) {
        src = getString(src, src_end, m.minKey);
        if (!src) return nullptr;
        src = getString(src, src_end, m.maxKey);
        if (!src) return nullptr;
        src = getFixed(src, src_end, m.offset);
        if (!src) return nullptr;
        src = getFixed(src, src_end, m.size);
        if (!src) return nullptr;
        src = getFixed(src, src_end, m.compressedSize);
        if (!src) return nullptr;
        src = getFixed(src, src_end, m.bloom.numBits);
        if (!src) return nullptr;
        src = getFixed(src, src_end, m.bloom.numHashes);
        if (!src) return nullptr;
        src = getVector(src, src_end, m.bloom.bits);
        return src;
    }

    // ---------------------------------------------------------------------------
    // Helper: Estimate size (for pre-allocation)
    // ---------------------------------------------------------------------------
    static inline size_t estimateWALEntrySize(const WALEntry& e) {
        size_t size = 1 + 1 + 1 + e.key.size() + 1;
        if (e.value) size += e.value->size();
        return size + 10;  // varint overhead
    }

    static inline size_t estimateSSTableEntrySize(const SSTableEntry& e) {
        return 1 + e.key.size() + 1 + e.value.size() + 1 + 8 + 5;
    }

    static inline size_t estimateBlockMetadataSize(const BlockMetadata& m) {
        return 1 + m.minKey.size() + 1 + m.maxKey.size() + 8 + 4 + 4 + 8 + 8 + 1 + m.bloom.bits.size() + 10;
    }
};

class WALWriter {
    int fd_;
    byte* buffer_;
    byte* cur_;
    byte* end_;
    static constexpr size_t PAGE = 4096;

public:
    WALWriter(const std::string& path) {
        fd_ = open(path.c_str(), O_RDWR | O_CREAT | O_APPEND, 0644);
        buffer_ = static_cast<byte*>(aligned_alloc(PAGE, PAGE));
        cur_ = buffer_;
        end_ = buffer_ + PAGE;
    }

    ~WALWriter() {
        flush();
        close(fd_);
        free(buffer_);
    }

    void append(const WALEntry& entry) {
        cur_ = Serializer::putWALEntry(cur_, end_, entry);
        if (!cur_) {
            flush();
            cur_ = Serializer::putWALEntry(buffer_, end_, entry);
            if (!cur_) throw std::runtime_error("WAL entry too large");
        }
    }

    void flush() {
        if (cur_ == buffer_) return;
        ssize_t n = write(fd_, buffer_, cur_ - buffer_);
        if (n < 0 || size_t(n) != cur_ - buffer_) throw std::system_error(errno, std::system_category());
        cur_ = buffer_;
    }
};

void writeSSTable(const std::vector<SSTableEntry>& entries, const BlockMetadata& meta, const std::string& path) {
    int fd = open(path.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0644);
    size_t total = 0;
    for (const auto& e : entries) total += Serializer::estimateSSTableEntrySize(e);
    total += Serializer::estimateBlockMetadataSize(meta);

    ftruncate(fd, total);
    byte* map = static_cast<byte*>(mmap(nullptr, total, PROT_WRITE, MAP_SHARED, fd, 0));
    byte* cur = map;
    byte* end = map + total;

    for (const auto& e : entries) {
        cur = Serializer::putSSTableEntry(cur, end, e);
    }

    meta.offset = 0;
    meta.size = cur - map;
    cur = Serializer::putBlockMetadata(cur, end, meta);

    msync(map, total, MS_SYNC);
    munmap(map, total);
    close(fd);
}

BlockMetadata readSSTableMetadata(const std::string& path, std::span<SSTableEntry>& out_entries) {
    // mmap entire file
    int fd = open(path.c_str(), O_RDONLY);
    off_t size = lseek(fd, 0, SEEK_END);
    byte* map = static_cast<byte*>(mmap(nullptr, size, PROT_READ, MAP_PRIVATE, fd, 0));
    const byte* cur = map;
    const byte* end = map + size;

    // Read metadata from end (assume last N bytes)
    const byte* meta_start = end - 256;  // or read footer size
    BlockMetadata meta;
    Serializer::getBlockMetadata(meta_start, end, meta);

    // Read entries
    const byte* data_end = map + meta.offset + meta.size;
    while (cur < data_end) {
        SSTableEntry e;
        cur = Serializer::getSSTableEntry(cur, data_end, e);
        out_entries.push_back(e);
    }

    munmap(map, size);
    close(fd);
    return meta;
}