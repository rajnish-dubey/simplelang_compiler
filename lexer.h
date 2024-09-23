//lexer.h header
#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

enum TokenType
{
    NUMBER,
    IDENTIFIER,
    ASSIGN,
    ADD,
    SUB,
    MUL,
    DIV,
    LPAREN,
    RPAREN,
    SEMICOLON,
    IF,
    ELSE,
    WHILE,
    INT_KEYWORD,
    EOF_TOKEN,
    UNKNOWN,
    INT 
};

struct Token
{
    TokenType type;
    std::string value;

    Token(TokenType type, const std::string &value) : type(type), value(value) {}
};

std::vector<Token> lexer(const std::string &input);

#endif
