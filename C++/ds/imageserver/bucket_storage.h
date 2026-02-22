// bucket_storage.h
#pragma once
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>

struct IndexEntry {
    uint64_t offset;
    uint64_t size;
};

class BucketStorage {
public:
    BucketStorage(const std::string& bucket_id)
        : data_file_("bucket_" + bucket_id + ".dat"),
          index_file_("bucket_" + bucket_id + ".idx") {
        load_index();
    }

    void put(const std::string& image_id, const std::vector<char>& data) {
        std::ofstream out(data_file_, std::ios::binary | std::ios::app);
        uint64_t offset = out.tellp();
        out.write(data.data(), data.size());
        out.close();

        index_[image_id] = {offset, data.size()};
        persist_index();
    }

    std::vector<char> get(const std::string& image_id) {
        auto it = index_.find(image_id);
        if (it == index_.end()) throw std::runtime_error("not found");

        std::ifstream in(data_file_, std::ios::binary);
        in.seekg(it->second.offset);

        std::vector<char> buf(it->second.size);
        in.read(buf.data(), buf.size());
        return buf;
    }

private:
    void load_index() {
        std::ifstream in(index_file_, std::ios::binary);
        if (!in) return;

        size_t n;
        in.read((char*)&n, sizeof(n));
        for (size_t i = 0; i < n; i++) {
            size_t len;
            in.read((char*)&len, sizeof(len));
            std::string key(len, '\0');
            in.read(key.data(), len);

            IndexEntry e;
            in.read((char*)&e, sizeof(e));
            index_[key] = e;
        }
    }

    void persist_index() {
        std::ofstream out(index_file_, std::ios::binary | std::ios::trunc);
        size_t n = index_.size();
        out.write((char*)&n, sizeof(n));

        for (auto& [k, v] : index_) {
            size_t len = k.size();
            out.write((char*)&len, sizeof(len));
            out.write(k.data(), len);
            out.write((char*)&v, sizeof(v));
        }
    }

    std::string data_file_, index_file_;
    std::unordered_map<std::string, IndexEntry> index_;
};
