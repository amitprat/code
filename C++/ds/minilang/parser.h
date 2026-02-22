#pragma once
#include "Lexer.h"
#include "AST.h"
#include <vector>

class Parser {
    std::vector<Token> tokens;
    size_t pos = 0;
    Token peek();
    Token next();
public:
    Parser(const std::vector<Token>& toks);
    std::vector<Stmt*> parse();
private:
    Stmt* parsePrint();
    Stmt* parseLet();
    Expr* parseExpr();
};
