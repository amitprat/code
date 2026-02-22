#include "idl_parser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

std::vector<Struct> parseIDL(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin) {
        throw std::runtime_error("Cannot open IDL file");
    }

    std::vector<Struct> structs;
    std::string line;
    Struct current;
    bool inStruct = false;

    while (std::getline(fin, line)) {
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
        if (line.empty()) continue;

        if (line.substr(0,6) == "struct") {
            inStruct = true;
            current.name = line.substr(6); // get struct name
            current.name.erase(std::remove(current.name.begin(), current.name.end(), '{'), current.name.end());
            current.fields.clear();
        } else if (line == "}") {
            inStruct = false;
            structs.push_back(current);
        } else if (inStruct) {
            // field format: type name;
            auto pos = line.find(';');
            if (pos != std::string::npos) line = line.substr(0,pos);
            size_t space = line.find_first_of(" \t");
            if (space != std::string::npos) {
                Field f{line.substr(0,space), line.substr(space+1)};
                current.fields.push_back(f);
            }
        }
    }

    return structs;
}
