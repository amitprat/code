#pragma once
#include <string>
#include <vector>

struct Field {
    std::string type;
    std::string name;
};

struct Struct {
    std::string name;
    std::vector<Field> fields;
};

std::vector<Struct> parseIDL(const std::string& filename);
