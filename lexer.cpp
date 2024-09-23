//lexer.cpp
#include "lexer.h"
#include <iostream>
#include <cctype>
#include <unordered_map>

std::vector<Token> lexer(const std::string &input)
{
    std::vector<Token> tokens;
    size_t i = 0;

    // Map of keywords
    std::unordered_map<std::string, TokenType> keywords = {
        {"if", IF},
        {"else", ELSE},
        {"while", WHILE},
        {"int", INT_KEYWORD}};

    while (i < input.size())
    {
        char current = input[i];

        if (isspace(current))
        {
            i++;
            continue;
        }

        if (isdigit(current))
        {
            std::string num;
            while (i < input.size() && isdigit(input[i]))
            {
                num += input[i++];
            }
            tokens.push_back(Token(NUMBER, num));
        }
        else if (isalpha(current))
        {
            std::string id;
            if (id == "int")
            {
                tokens.push_back(Token(INT, id)); // Use the new INT token type
            }
            else
            {
                tokens.push_back(Token(IDENTIFIER, id));
            }

            while (i < input.size() && (isalnum(input[i]) || input[i] == '_'))
            {
                id += input[i++];
            }

            // Check if it's a keyword
            if (keywords.find(id) != keywords.end())
            {
                tokens.push_back(Token(keywords[id], id));
            }
            else
            {
                // Otherwise, it's an identifier
                tokens.push_back(Token(IDENTIFIER, id));
            }
        }
        else
        {
            switch (current)
            {
            case '=':
                tokens.push_back(Token(ASSIGN, "="));
                break;
            case '+':
                tokens.push_back(Token(ADD, "+"));
                break;
            case '-':
                tokens.push_back(Token(SUB, "-"));
                break;
            case '*':
                tokens.push_back(Token(MUL, "*"));
                break;
            case '/':
                tokens.push_back(Token(DIV, "/"));
                break;
            case '(':
                tokens.push_back(Token(LPAREN, "("));
                break;
            case ')':
                tokens.push_back(Token(RPAREN, ")"));
                break;
            case ';':
                tokens.push_back(Token(SEMICOLON, ";"));
                break;
            default:
                tokens.push_back(Token(UNKNOWN, std::string(1, current)));
                break;
            }
            i++;
        }
    }
    tokens.push_back(Token(EOF_TOKEN, ""));
    return tokens;
}