#pragma once
#include <sstream>
#include <string>

class CodeBuilder {
    std::ostringstream oss;
    int indentLevel = 0;
    std::string indentStr = "    "; // 4 spaces
public:
    // Add a single line with current indentation
    void addLine(const std::string& line) {
        for (int i = 0; i < indentLevel; ++i) oss << indentStr;
        oss << line << "\n";
    }

    // Open a block (e.g., class, method)
    void openBlock(const std::string& line) {
        addLine(line);
        ++indentLevel;
    }

    // Close a block
    void closeBlock() {
        --indentLevel;
        addLine("}");
    }

    // Get full generated code as string
    std::string str() const {
        return oss.str();
    }
};
