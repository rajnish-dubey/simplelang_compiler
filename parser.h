//parser.h header
#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include "lexer.h"

class ASTNode
{
public:
    virtual ~ASTNode() = default;
};

class NumberNode : public ASTNode
{
public:
    int value;
    NumberNode(int value) : value(value) {}
};

class VariableNode : public ASTNode
{
public:
    std::string name;
    VariableNode(const std::string &name) : name(name) {}
};

class BinaryOpNode : public ASTNode
{
public:
    char op;
    ASTNode *left, *right;

    BinaryOpNode(char op, ASTNode *left, ASTNode *right) : op(op), left(left), right(right) {}
};

class AssignmentNode : public ASTNode
{
public:
    std::string varName;
    ASTNode *expression;

    AssignmentNode(const std::string &varName, ASTNode *expression)
        : varName(varName), expression(expression) {}
};

class IfNode : public ASTNode
{
public:
    ASTNode *condition;
    ASTNode *thenBranch;
    ASTNode *elseBranch;

    IfNode(ASTNode *condition, ASTNode *thenBranch, ASTNode *elseBranch = nullptr)
        : condition(condition), thenBranch(thenBranch), elseBranch(elseBranch) {}
};

class WhileNode : public ASTNode
{
public:
    ASTNode *condition;
    ASTNode *body;

    WhileNode(ASTNode *condition, ASTNode *body) : condition(condition), body(body) {}
};

ASTNode *parseExpression(std::vector<Token> &tokens, int &pos);
ASTNode *parseAssignment(std::vector<Token> &tokens, int &pos);
ASTNode *parseIfStatement(std::vector<Token> &tokens, int &pos);
ASTNode *parseWhileLoop(std::vector<Token> &tokens, int &pos);
void printAST(ASTNode *node);

#endif
