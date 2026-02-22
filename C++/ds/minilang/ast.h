#pragma once
#include <string>

struct Expr { virtual ~Expr() = default; };
struct NumberExpr : Expr { int value; NumberExpr(int v): value(v){} };
struct StringExpr : Expr { std::string value; StringExpr(const std::string& v): value(v){} };
struct VarExpr : Expr { std::string name; VarExpr(const std::string& n): name(n){} };
struct BinaryExpr : Expr { Expr* left; char op; Expr* right; BinaryExpr(Expr* l,char o,Expr* r): left(l), op(o), right(r){} };

struct Stmt { virtual ~Stmt() = default; };
struct PrintStmt : Stmt { Expr* expr; PrintStmt(Expr* e): expr(e){} };
struct LetStmt : Stmt { std::string name; Expr* expr; LetStmt(const std::string& n, Expr* e): name(n), expr(e){} };
