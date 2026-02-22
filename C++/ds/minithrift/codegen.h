#pragma once
#include "idl_parser.h"
#include <string>

void generateCpp(const std::vector<Struct>& structs, const std::string& outputDir);
