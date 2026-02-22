#include "CodeGen.h"
#include <sstream>

std::string generateCppFromBytecode(const std::vector<Instruction>& code){
    std::ostringstream out;
    out << "#include <iostream>\n#include <stack>\n#include <unordered_map>\n#include <variant>\n#include <string>\n\n";
    out << "int main(){\n";
    out << "using Value = std::variant<int,std::string>;\n";
    out << "std::stack<Value> stk;\nstd::unordered_map<std::string,Value> vars;\n";

    for(const auto& instr: code){
        switch(instr.op){
            case OpCode::PUSH_INT: out << "stk.push(" << instr.intVal << ");\n"; break;
            case OpCode::PUSH_STR: out << "stk.push(std::string(\"" << instr.strVal << "\"));\n"; break;
            case OpCode::LOAD: out << "stk.push(vars[\"" << instr.strVal << "\"]);\n"; break;
            case OpCode::STORE: out << "vars[\"" << instr.strVal << "\"]=stk.top(); stk.pop();\n"; break;
            case OpCode::ADD: out << "{ auto b=stk.top(); stk.pop(); auto a=stk.top(); stk.pop(); stk.push(std::get<int>(a)+std::get<int>(b)); }\n"; break;
            case OpCode::PRINT: out << "{ auto v=stk.top(); stk.pop(); std::cout << std::get<int>(v) << std::endl; }\n"; break;
            case OpCode::HALT: break;
        }
    }

    out << "return 0;\n}\n";
    return out.str();
}
