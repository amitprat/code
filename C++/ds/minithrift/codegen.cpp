#include "idl_parser.h"
#include "codegen.h"
#include "CodeBuilder.h"
#include <fstream>
#include <iostream>

void generateCpp(const std::vector<Struct>& structs, const std::string& outputDir) {
    for (const auto& s : structs) {
        std::string headerFile = outputDir + "/" + s.name + ".h";
        std::string cppFile    = outputDir + "/" + s.name + ".cpp";

        // ------------------ Generate Header ------------------
        CodeBuilder hcb;
        hcb.addLine("#pragma once");
        hcb.addLine("#include <string>");
        hcb.addLine("#include <ostream>");
        hcb.addLine("#include <istream>");
        hcb.addLine("#include <cstdint>");
        hcb.addLine("");

        hcb.openBlock("class " + s.name + " {");
        hcb.addLine("public:");
        for (auto& f : s.fields) {
            std::string typeStr = (f.type == "int") ? "int" : "std::string";
            hcb.addLine(typeStr + " " + f.name + ";");
        }

        hcb.addLine("");
        hcb.addLine("void serialize(std::ostream& os) const;");
        hcb.addLine("void deserialize(std::istream& is);");
        hcb.closeBlock(); // end class

        std::ofstream foutH(headerFile);
        if (!foutH) {
            std::cerr << "Cannot open file " << headerFile << "\n";
            continue;
        }
        foutH << hcb.str();
        std::cout << "Generated " << headerFile << "\n";

        // ------------------ Generate CPP ------------------
        CodeBuilder ccb;
        ccb.addLine("#include \"" + s.name + ".h\"");
        ccb.addLine("");

        // Serialize method
        ccb.openBlock("void " + s.name + "::serialize(std::ostream& os) const {");
        for (auto& f : s.fields) {
            if (f.type == "int") {
                ccb.addLine("os.write(reinterpret_cast<const char*>(&" + f.name + "), sizeof(" + f.name + "));");
            } else if (f.type == "string") {
                ccb.addLine("uint32_t len_" + f.name + " = " + f.name + ".size();");
                ccb.addLine("os.write(reinterpret_cast<const char*>(&len_" + f.name + "), sizeof(len_" + f.name + "));");
                ccb.addLine("os.write(" + f.name + ".c_str(), len_" + f.name + ");");
            }
        }
        ccb.closeBlock();

        // Deserialize method
        ccb.addLine("");
        ccb.openBlock("void " + s.name + "::deserialize(std::istream& is) {");
        for (auto& f : s.fields) {
            if (f.type == "int") {
                ccb.addLine("is.read(reinterpret_cast<char*>(&" + f.name + "), sizeof(" + f.name + "));");
            } else if (f.type == "string") {
                ccb.addLine("uint32_t len_" + f.name + ";");
                ccb.addLine("is.read(reinterpret_cast<char*>(&len_" + f.name + "), sizeof(len_" + f.name + "));");
                ccb.addLine("char* buf = new char[len_" + f.name + "];");
                ccb.addLine("is.read(buf, len_" + f.name + ");");
                ccb.addLine(f.name + " = std::string(buf, len_" + f.name + ");");
                ccb.addLine("delete[] buf;");
            }
        }
        ccb.closeBlock();

        std::ofstream foutCpp(cppFile);
        if (!foutCpp) {
            std::cerr << "Cannot open file " << cppFile << "\n";
            continue;
        }
        foutCpp << ccb.str();
        std::cout << "Generated " << cppFile << "\n";
    }
}
