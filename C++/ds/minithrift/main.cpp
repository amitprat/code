#include "idl_parser.h"
#include "codegen.h"
#include <iostream>

int main() {
    std::string idlFile = "user.idl";
    std::string outDir = "generated";

    try {
        auto structs = parseIDL(idlFile);
        generateCpp(structs, outDir);
        std::cout << "Code generated successfully!\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}
