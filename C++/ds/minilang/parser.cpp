#include "Parser.h"
#include <stdexcept>

Parser::Parser(const std::vector<Token>& toks): tokens(toks){}
Token Parser::peek(){return tokens[pos];}
Token Parser::next(){return tokens[pos++];}

std::vector<Stmt*> Parser::parse(){
    std::vector<Stmt*> stmts;
    while(peek().type!=TokenType::END){
        if(peek().type==TokenType::PRINT) stmts.push_back(parsePrint());
        else if(peek().type==TokenType::LET) stmts.push_back(parseLet());
        else next();
    }
    return stmts;
}

Stmt* Parser::parsePrint(){
    next();
    Expr* e = parseExpr();
    if(peek().type==TokenType::NEWLINE) next();
    return new PrintStmt(e);
}

Stmt* Parser::parseLet(){
    next();
    std::string name = next().text;
    if(peek().type!=TokenType::EQUAL) throw std::runtime_error("Expected =");
    next();
    Expr* e = parseExpr();
    if(peek().type==TokenType::NEWLINE) next();
    return new LetStmt(name,e);
}

Expr* Parser::parseExpr(){
    Token t = next();
    Expr* left=nullptr;
    if(t.type==TokenType::NUMBER) left = new NumberExpr(std::stoi(t.text));
    else if(t.type==TokenType::STRING) left = new StringExpr(t.text);
    else if(t.type==TokenType::IDENT) left = new VarExpr(t.text);
    else throw std::runtime_error("Unexpected token");

    if(peek().type==TokenType::PLUS){
        next();
        Expr* right = parseExpr();
        return new BinaryExpr(left,'+',right);
    }
    return left;
}
