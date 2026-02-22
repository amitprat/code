#pragma once
#include <string>
#include <vector>

enum class TokenType {
    PRINT, LET, IDENT, NUMBER, STRING,
    PLUS, EQUAL, NEWLINE, END
};

struct Token {
    TokenType type;
    std::string text;
};

class Lexer {
    std::string input;
    size_t pos = 0;

    char peek();
    char next();
public:
    Lexer(const std::string& src);
    std::vector<Token> tokenize();
};
