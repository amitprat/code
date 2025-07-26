// FileSystemSerializer.h
#pragma once

#include "FileManager.h"

#include <string>
#include <vector>
#include <cstdint>
#include <optional>
#include <cstring>
#include <stdexcept>
#include <system_error>
#include <memory>
#include <cassert>
#include <fstream>

using namespace storage;
using std::byte;
using LSN = uint64_t;

namespace fsser {

// ---------------------------
// Data structures matching example usage
// ---------------------------
struct WALEntry {
    LSN lsn = 0;
    storage::WALOpType op = storage::WALOpType::PUT;
    std::string key;
    std::optional<std::string> value;
};

struct SSTableEntry {
    std::string key;
    std::string value;
    bool tombstone = false;
    uint64_t seqNum = 0;
};

struct BlockMetadata {
    std::string minKey;
    std::string maxKey;
    uint64_t numEntries = 0;
    uint64_t dataSize = 0;
};

class FileWriter;
class FileReader;

// ---------------------------
// Low-level serialization helpers (std::byte oriented)
// ---------------------------
class Serializer {
public:
    // varint (unsigned LEB128)
    static inline size_t encodeVarintToBuffer(uint64_t v, byte* out) {
        // write to out, return bytes written (max 10)
        size_t i = 0;
        do {
            uint8_t b = static_cast<uint8_t>(v & 0x7Fu);
            v >>= 7;
            if (v) b |= 0x80u;
            out[i++] = static_cast<byte>(b);
        } while (v);
        return i;
    }

    // decode from a contiguous buffer (pointer + len); returns bytes consumed or 0 on error
    static inline size_t decodeVarintFromBuffer(const byte* src, size_t len, uint64_t& out) {
        out = 0;
        int shift = 0;
        size_t i = 0;
        while (i < len && shift < 64) {
            uint8_t b = static_cast<uint8_t>(src[i++]);
            out |= (uint64_t)(b & 0x7Fu) << shift;
            if ((b & 0x80u) == 0) {
                return i;
            }
            shift += 7;
        }
        return 0; // failure / overflow
    }

    // Forward declarations for methods that need complete types
    template<typename T>
    static inline void writeFixedTo(FileWriter& w, T val);

    template<typename T>
    static inline void readFixedFrom(const FileReader& r, off_t offset, T& out);

    static inline void putVarintToWriter(FileWriter& w, uint64_t v);
    static inline void putStringToWriter(FileWriter& w, const std::string& s);
    
    template <typename ByteVec>
    static inline void putBlobToWriter(FileWriter& w, const ByteVec& v);
};

// ---------------------------
// FileWriter - buffering writer built on top of FileManager
// ---------------------------
class FileWriter {
public:
    explicit FileWriter(storage::FileManager& fm, size_t bufSize = 64 * 1024)
        : fm_(fm), buf_(bufSize), cur_(0) {
        if (!fm_.isOpen()) throw std::runtime_error("FileWriter requires FileManager open for write");
    }

    // append raw bytes (copies to internal buffer; flushes to file when needed)
    void appendRaw(const void* data, size_t len) {
        const byte* p = reinterpret_cast<const byte*>(data);
        size_t remaining = len;
        while (remaining > 0) {
            size_t space = buf_.size() - cur_;
            if (space == 0) flush();
            space = buf_.size() - cur_;
            size_t to_copy = std::min(remaining, space);
            std::memcpy(buf_.data() + cur_, p, to_copy);
            cur_ += to_copy;
            p += to_copy;
            remaining -= to_copy;
        }
    }

    // flush internal buffer to file (uses FileManager::writeFully)
    void flush() {
        if (cur_ == 0) return;
        fm_.writeFully(buf_.data(), cur_);
        cur_ = 0;
    }

    // convenience
    off_t position() const { return fm_.tell() + static_cast<off_t>(cur_); }

    // write a POD directly (copy into buffer)
    template<typename T>
    void appendPod(const T& v) {
        appendRaw(&v, sizeof(T));
    }

    // close/flush at destruction or explicitly
    void close() { flush(); }

private:
    storage::FileManager& fm_;
    std::vector<byte> buf_;
    size_t cur_;
};

// Now define template methods that depend on FileWriter
template<typename T>
inline void Serializer::writeFixedTo(FileWriter& w, T val) {
    static_assert(std::is_arithmetic_v<T> || std::is_enum_v<T>);
    if constexpr (sizeof(T) > 1) {
        if constexpr (std::endian::native == std::endian::little) {
            val = std::byteswap(val);
        }
    }
    w.appendRaw(&val, sizeof(T));
}
// ---------------------------
// FileReader - read operations via FileManager
// ---------------------------
class FileReader {
public:
    explicit FileReader(storage::FileManager& fm)
        : fm_(fm)
    {
        if (!fm_.isOpen()) throw std::runtime_error("FileReader requires FileManager open for read");
    }

    // read exactly len bytes into buffer starting at given offset (throws on short read)
    void readAt(void* outBuf, size_t len, off_t offset) const {
        size_t remaining = len;
        byte* dest = reinterpret_cast<byte*>(outBuf);
        while (remaining > 0) {
            ssize_t n = fm_.preadRaw(dest, remaining, offset);
            if (n <= 0) throw std::system_error(errno, std::system_category(), "readAt failed/short read");
            dest += n;
            offset += n;
            remaining -= static_cast<size_t>(n);
        }
    }

    // read up to len bytes at offset (returns bytes read)
    ssize_t readSomeAt(void* outBuf, size_t len, off_t offset) const {
        return fm_.preadRaw(outBuf, len, offset);
    }

private:
    storage::FileManager& fm_;
};


template<typename T>
inline void Serializer::readFixedFrom(const FileReader& r, off_t offset, T& out) {
    static_assert(std::is_arithmetic_v<T> || std::is_enum_v<T>);
    r.readAt(&out, sizeof(T), offset);
    if constexpr (sizeof(T) > 1) {
        if constexpr (std::endian::native == std::endian::little) {
            out = std::byteswap(out);
        }
    }
}

// Implement methods that use FileWriter
inline void Serializer::putVarintToWriter(FileWriter& w, uint64_t v) {
    byte temp[10];
    size_t l = encodeVarintToBuffer(v, temp);
    w.appendRaw(temp, l);
}

inline void Serializer::putStringToWriter(FileWriter& w, const std::string& s) {
    putVarintToWriter(w, s.size());
    if (!s.empty()) w.appendRaw(reinterpret_cast<const byte*>(s.data()), s.size());
}

template <typename ByteVec>
inline void Serializer::putBlobToWriter(FileWriter& w, const ByteVec& v) {
    putVarintToWriter(w, v.size());
    if (!v.empty()) w.appendRaw(reinterpret_cast<const byte*>(v.data()), v.size());
}

// ---------------------------
// WAL: direct streaming appends into FileWriter (no temporary vector)
// ---------------------------
class WALWriter {
public:
    explicit WALWriter(storage::FileManager& fm)
        : fm_(fm), writer_(fm_, 64 * 1024) {
        if (!fm_.isOpen()) throw std::runtime_error("WALWriter requires open FileManager");
        fm_.adviseSequential();
    }

    // append a WALEntry directly (overload for struct)
    void append(const WALEntry& entry) {
        append(entry.lsn, static_cast<uint8_t>(entry.op), entry.key, entry.value);
    }

    // append a WALEntry directly (original signature)
    void append(const LSN lsn, uint8_t op, const std::string& key, const std::optional<std::string>& val) {
        // lsn (fixed 8), op (1), key (varint+bytes), value optional (bool + varint+bytes)
        Serializer::writeFixedTo(writer_, lsn);
        writer_.appendRaw(&op, 1);
        Serializer::putStringToWriter(writer_, key);
        if (val.has_value()) {
            uint8_t has = 1;
            writer_.appendRaw(&has, 1);
            Serializer::putStringToWriter(writer_, *val);
        } else {
            uint8_t has = 0;
            writer_.appendRaw(&has, 1);
        }
    }

    void flush() { writer_.flush(); fm_.flush(FlushMode::DATA_ONLY); }
    void close() { flush(); /* caller may close fm_ */ }

private:
    storage::FileManager& fm_;
    FileWriter writer_;
};

// ---------------------------
// SSTable layout + footer (fixed size)
// ---------------------------
struct Footer {
    uint64_t index_offset;
    uint64_t index_size;
    uint64_t bloom_offset;
    uint64_t bloom_size;
    uint64_t magic;
};

// Magic constant to validate footer
constexpr uint64_t SSTABLE_FOOTER_MAGIC = 0xFAB0FAB0D1A5E5ABULL;
static_assert(sizeof(Footer) == 40, "Footer size expected to be 40 bytes");

// A small metadata view returned by readSSTableMetadata
struct SSTableMetadata {
    uint64_t index_offset = 0;
    uint64_t index_size = 0;
    uint64_t bloom_offset = 0;
    uint64_t bloom_size = 0;
};

// ---------------------------
// Streaming serializers for SSTable pieces
// ---------------------------

inline void writeString(FileWriter& w, const std::string& s) {
    Serializer::putVarintToWriter(w, s.size());
    if (!s.empty()) w.appendRaw(reinterpret_cast<const byte*>(s.data()), s.size());
}

inline void writeBlob(FileWriter& w, const std::vector<byte>& b) {
    Serializer::putVarintToWriter(w, b.size());
    if (!b.empty()) w.appendRaw(b.data(), b.size());
}

// Write a single SSTable entry: key, value, tombstone (uint8), seqNum (uint64)
inline void writeSSTableEntry(FileWriter& w, const std::string& key, const std::string& value, bool tombstone, uint64_t seqNum) {
    writeString(w, key);
    writeString(w, value);
    uint8_t t = tombstone ? 1 : 0;
    w.appendRaw(&t, 1);
    Serializer::writeFixedTo(w, seqNum);
}

// ---------------------------
// Write full SSTable (simplified API for example usage)
// ---------------------------
inline void writeSSTable(const std::vector<SSTableEntry>& entries,
                         const BlockMetadata& meta,
                         const std::string& path_out) 
{
    storage::FileManager fm(path_out);
    fm.openForWrite(false, true);

    FileWriter w(fm, 64 * 1024);
    
    // 1) Data blocks: write all entries sequentially
    std::vector<std::pair<std::string, uint64_t>> computed_index;
    for (const auto& e : entries) {
        off_t entry_offset = w.position();
        writeSSTableEntry(w, e.key, e.value, e.tombstone, e.seqNum);
        computed_index.emplace_back(e.key, static_cast<uint64_t>(entry_offset));
    }

    // 2) Index block
    off_t index_offset = w.position();
    Serializer::putVarintToWriter(w, computed_index.size());
    for (auto const& kv : computed_index) {
        writeString(w, kv.first);
        Serializer::putVarintToWriter(w, kv.second);
    }
    off_t index_size = w.position() - index_offset;

    // 3) Bloom block (empty for now)
    off_t bloom_offset = w.position();
    std::vector<byte> empty_bloom;
    writeBlob(w, empty_bloom);
    off_t bloom_size = w.position() - bloom_offset;

    // 4) Footer (fixed size)
    Footer f;
    f.index_offset = static_cast<uint64_t>(index_offset);
    f.index_size = static_cast<uint64_t>(index_size);
    f.bloom_offset = static_cast<uint64_t>(bloom_offset);
    f.bloom_size = static_cast<uint64_t>(bloom_size);
    f.magic = SSTABLE_FOOTER_MAGIC;

    Serializer::writeFixedTo(w, f.index_offset);
    Serializer::writeFixedTo(w, f.index_size);
    Serializer::writeFixedTo(w, f.bloom_offset);
    Serializer::writeFixedTo(w, f.bloom_size);
    Serializer::writeFixedTo(w, f.magic);

    w.flush();
    fm.flush(FlushMode::FULL_SYNC);
}

// ---------------------------
// Read SSTable metadata and entries (simplified API)
// ---------------------------
inline BlockMetadata readSSTableMetadata(const std::string& path, std::vector<SSTableEntry>& entries) {
    storage::FileManager fm(path);
    fm.openForRead();

    size_t footer_sz = sizeof(Footer);
    size_t fsize = fm.size();
    if (fsize < footer_sz) throw std::runtime_error("file too small for footer");

    off_t footer_offset = static_cast<off_t>(fsize - footer_sz);
    std::array<uint8_t, sizeof(Footer)> buf;
    fm.preadRaw(buf.data(), buf.size(), footer_offset);

    auto read_u64_from_ptr = [](const byte* p)->uint64_t {
        uint64_t v;
        std::memcpy(&v, p, sizeof(uint64_t));
        if constexpr (std::endian::native == std::endian::little) v = std::byteswap(v);
        return v;
    };

    const byte* cur = reinterpret_cast<const byte*>(buf.data());
    uint64_t index_offset = read_u64_from_ptr(cur); cur += 8;
    uint64_t index_size   = read_u64_from_ptr(cur); cur += 8;
    uint64_t bloom_offset = read_u64_from_ptr(cur); cur += 8;
    uint64_t bloom_size   = read_u64_from_ptr(cur); cur += 8;
    uint64_t magic        = read_u64_from_ptr(cur); cur += 8;

    if (magic != SSTABLE_FOOTER_MAGIC) throw std::runtime_error("bad sstable footer magic");

    // Read index to find entries
    std::vector<byte> index_data(index_size);
    fm.preadRaw(index_data.data(), index_size, index_offset);
    
    const byte* idx_ptr = index_data.data();
    size_t idx_remaining = index_size;
    
    uint64_t num_entries = 0;
    size_t consumed = Serializer::decodeVarintFromBuffer(idx_ptr, idx_remaining, num_entries);
    if (consumed == 0) throw std::runtime_error("Failed to read entry count");
    idx_ptr += consumed;
    idx_remaining -= consumed;

    // Parse index entries (key + offset pairs)
    std::vector<std::pair<std::string, uint64_t>> index_entries;
    for (uint64_t i = 0; i < num_entries; ++i) {
        uint64_t key_len = 0;
        consumed = Serializer::decodeVarintFromBuffer(idx_ptr, idx_remaining, key_len);
        if (consumed == 0) throw std::runtime_error("Failed to read key length");
        idx_ptr += consumed;
        idx_remaining -= consumed;

        std::string key(reinterpret_cast<const char*>(idx_ptr), key_len);
        idx_ptr += key_len;
        idx_remaining -= key_len;

        uint64_t offset = 0;
        consumed = Serializer::decodeVarintFromBuffer(idx_ptr, idx_remaining, offset);
        if (consumed == 0) throw std::runtime_error("Failed to read offset");
        idx_ptr += consumed;
        idx_remaining -= consumed;

        index_entries.emplace_back(key, offset);
    }

    // Read actual entries from data section
    BlockMetadata meta;
    if (!index_entries.empty()) {
        meta.minKey = index_entries.front().first;
        meta.maxKey = index_entries.back().first;
        meta.numEntries = num_entries;
    }

    // For simplicity, read all entries
    for (size_t i = 0; i < index_entries.size(); ++i) {
        uint64_t entry_offset = index_entries[i].second;
        uint64_t next_offset = (i + 1 < index_entries.size()) ? index_entries[i + 1].second : index_offset;
        size_t entry_size = next_offset - entry_offset;

        std::vector<byte> entry_data(entry_size);
        fm.preadRaw(entry_data.data(), entry_size, entry_offset);

        const byte* entry_ptr = entry_data.data();
        size_t entry_remaining = entry_size;

        // Read key
        uint64_t key_len = 0;
        consumed = Serializer::decodeVarintFromBuffer(entry_ptr, entry_remaining, key_len);
        entry_ptr += consumed; entry_remaining -= consumed;
        std::string key(reinterpret_cast<const char*>(entry_ptr), key_len);
        entry_ptr += key_len; entry_remaining -= key_len;

        // Read value
        uint64_t val_len = 0;
        consumed = Serializer::decodeVarintFromBuffer(entry_ptr, entry_remaining, val_len);
        entry_ptr += consumed; entry_remaining -= consumed;
        std::string value(reinterpret_cast<const char*>(entry_ptr), val_len);
        entry_ptr += val_len; entry_remaining -= val_len;

        // Read tombstone
        uint8_t tomb = *reinterpret_cast<const uint8_t*>(entry_ptr);
        entry_ptr += 1; entry_remaining -= 1;

        // Read seqNum
        uint64_t seqNum = 0;
        std::memcpy(&seqNum, entry_ptr, sizeof(uint64_t));
        if constexpr (std::endian::native == std::endian::little) seqNum = std::byteswap(seqNum);

        SSTableEntry e;
        e.key = key;
        e.value = value;
        e.tombstone = (tomb != 0);
        e.seqNum = seqNum;
        entries.push_back(e);
    }

    return meta;
}

} // namespace fsser