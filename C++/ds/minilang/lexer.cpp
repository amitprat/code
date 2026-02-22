#include "Lexer.h"
#include <cctype>

Lexer::Lexer(const std::string& src) : input(src) {}

char Lexer::peek() { return pos < input.size() ? input[pos] : 0; }
char Lexer::next() { return pos < input.size() ? input[pos++] : 0; }

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (true) {
        char c = peek();
        if (c == 0) break;
        if (isspace(c)) {
            if (c=='\n') tokens.push_back({TokenType::NEWLINE, "\n"});
            next();
        } else if (isalpha(c)) {
            std::string id;
            while (isalnum(peek())) id += next();
            if (id=="print") tokens.push_back({TokenType::PRINT,id});
            else if (id=="let") tokens.push_back({TokenType::LET,id});
            else tokens.push_back({TokenType::IDENT,id});
        } else if (isdigit(c)) {
            std::string num;
            while (isdigit(peek())) num += next();
            tokens.push_back({TokenType::NUMBER,num});
        } else if (c=='"') {
            next();
            std::string str;
            while(peek()!='"') str+=next();
            next();
            tokens.push_back({TokenType::STRING,str});
        } else if (c=='+') { next(); tokens.push_back({TokenType::PLUS,"+"}); }
        else if (c=='=') { next(); tokens.push_back({TokenType::EQUAL,"="}); }
        else { next(); } // ignore unknown
    }
    tokens.push_back({TokenType::END,""});
    return tokens;
}
