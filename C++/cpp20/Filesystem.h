#include "../header.h"

class Filesystem {
   public:
    static void test() {
        filesystem::path directorypath = "";

        // To check if the directory exists or not
        if (filesystem::exists(directorypath) && filesystem::is_directory(directorypath)) {
            // Loop through each item (file or subdirectory) in
            // the directory
            for (const auto& entry :
                 filesystem::directory_iterator(directorypath)) {
                // Output the path of the file or subdirectory
                cout << "File: " << entry.path() << endl;
            }
        } else {
            // Handle the case where the directory doesn't exist
            cerr << "Directory not found." << endl;
        }
    }
};