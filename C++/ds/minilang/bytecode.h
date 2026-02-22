#pragma once
#include <string>
#include <vector>
#include "AST.h"

enum class OpCode{PUSH_INT,PUSH_STR,LOAD,STORE,ADD,PRINT,HALT};

struct Instruction{
    OpCode op;
    std::string strVal;
    int intVal;
};

class BytecodeGen{
public:
    std::vector<Instruction> code;
    void generate(const std::vector<Stmt*>& stmts);
private:
    void genExpr(Expr* e);
};
