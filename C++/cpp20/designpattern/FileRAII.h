#pragma once
#include "../../header.h"

class FileRAII {
   private:
    ofstream file;

   public:
    static void test() {
        try {
            FileRAII file("file.txt", std::ios::out);
            file.get() << "RAII in modern c++" << endl;
        } catch (exception e) {
            cerr << "Exception: " << e.what() << endl;
        }
    }

   public:
    FileRAII(const string& filename, std::ios::openmode mode) {
        file.open(filename, mode);
        if (!file.is_open()) {
            throw runtime_error(format("Failed to open file {}", filename));
        }

        cout << "Opened file: " << filename << endl;
    }

    ~FileRAII() {
        if (file.is_open()) {
            file.close();
            cout << "Closed file." << endl;
        }
    }

    ofstream& get() { return file; }

    FileRAII(const FileRAII&) = delete;
    FileRAII& operator=(const FileRAII&) = delete;

    FileRAII(FileRAII&& other) noexcept : file(std::move(other.file)) {}
    FileRAII& operator=(FileRAII&& other) noexcept {
        file = std::move(other.file);
        return *this;
    }
};