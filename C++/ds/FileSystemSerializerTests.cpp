// example.cpp
#include "FileSystemSerializer.h"
#include <iostream>

using namespace fsser;

int main() {
    try {
        // --- WAL example ---
        {
            storage::FileManager fm("example.wal");
            fm.openForWrite();
            
            WALWriter wal(fm);
            
            WALEntry e1;
            e1.lsn = 1;
            e1.op = storage::WALOpType::PUT;
            e1.key = "hello";
            e1.value = std::string("world");
            
            wal.append(e1);
            wal.flush();
            wal.close();
            
            fm.close();
        }

        std::cout << "WAL written\n";

        // --- SSTable example ---
        {
            std::vector<SSTableEntry> entries;
            
            SSTableEntry s;
            s.key = "k1";
            s.value = "v1";
            s.seqNum = 100;
            s.tombstone = false;
            entries.push_back(s);
            
            BlockMetadata meta;
            meta.minKey = "k1";
            meta.maxKey = "k1";
            meta.numEntries = 1;
            
            writeSSTable(entries, meta, "example.sst");
        }

        std::cout << "SSTable written\n";

        // --- Read SSTable back ---
        {
            std::vector<SSTableEntry> read_entries;
            BlockMetadata read_meta = readSSTableMetadata("example.sst", read_entries);
            
            std::cout << "Read SSTable meta:\n";
            std::cout << "  minKey: " << read_meta.minKey << "\n";
            std::cout << "  maxKey: " << read_meta.maxKey << "\n";
            std::cout << "  numEntries: " << read_meta.numEntries << "\n";
            std::cout << "  entries read: " << read_entries.size() << "\n";
            
            if (!read_entries.empty()) {
                std::cout << "First entry:\n";
                std::cout << "  key: " << read_entries[0].key << "\n";
                std::cout << "  value: " << read_entries[0].value << "\n";
                std::cout << "  seqNum: " << read_entries[0].seqNum << "\n";
                std::cout << "  tombstone: " << (read_entries[0].tombstone ? "true" : "false") << "\n";
            }
        }

    } catch (const std::exception& ex) {
        std::cerr << "ERROR: " << ex.what() << "\n";
        return 1;
    }
    
    return 0;
}