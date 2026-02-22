#include "Bytecode.h"
#include <typeinfo>
#include <stdexcept>

void BytecodeGen::generate(const std::vector<Stmt*>& stmts){
    for(auto s: stmts){
        if(auto p = dynamic_cast<PrintStmt*>(s)){
            genExpr(p->expr);
            code.push_back({OpCode::PRINT,"",0});
        } else if(auto l = dynamic_cast<LetStmt*>(s)){
            genExpr(l->expr);
            code.push_back({OpCode::STORE,l->name,0});
        }
    }
    code.push_back({OpCode::HALT,"",0});
}

void BytecodeGen::genExpr(Expr* e){
    if(auto n = dynamic_cast<NumberExpr*>(e)) code.push_back({OpCode::PUSH_INT,"",n->value});
    else if(auto s = dynamic_cast<StringExpr*>(e)) code.push_back({OpCode::PUSH_STR,s->value,0});
    else if(auto v = dynamic_cast<VarExpr*>(e)) code.push_back({OpCode::LOAD,v->name,0});
    else if(auto b = dynamic_cast<BinaryExpr*>(e)){
        genExpr(b->left);
        genExpr(b->right);
        code.push_back({OpCode::ADD,"",0});
    } else throw std::runtime_error("Unknown expr type");
}
