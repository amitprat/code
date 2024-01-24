#include "../header.h"

class SortFile {
   public:
    static void test() {
        SortFile obj;
        obj.sortFile("C:\\C++\\careercup\\tmp.txt");
    }

   public:
    void sortFile(string fileName) {
        std::fstream file(fileName, std::ios::in);

        // Read the contents of the file
        vector<string> inputs;
        std::string line;
        while (std::getline(file, line)) {
            inputs.push_back(line);
        }

        // Close the file
        file.close();

        // Open a file for writing
        file.open(fileName, std::ios::out);

        sort(inputs.begin(), inputs.end());

        // Write to the file
        for (auto& line : inputs) {
            file << line << endl;
        }

        // Close the file
        file.close();
    }
};