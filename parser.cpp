//parser.cpp
#include "parser.h"
#include <iostream>

ASTNode *parseTerm(std::vector<Token> &tokens, int &pos)
{
    if (tokens[pos].type == NUMBER)
    {
        int value = std::stoi(tokens[pos++].value);
        return new NumberNode(value);
    }
    else if (tokens[pos].type == IDENTIFIER)
    {
        std::string name = tokens[pos++].value;
        return new VariableNode(name);
    }
    std::cerr << "Unexpected token: " << tokens[pos].value << std::endl;
    exit(1);
}

ASTNode *parseExpression(std::vector<Token> &tokens, int &pos)
{
    ASTNode *left = parseTerm(tokens, pos);

    while (pos < tokens.size() &&
           (tokens[pos].type == ADD || tokens[pos].type == SUB ||
            tokens[pos].type == MUL || tokens[pos].type == DIV))
    {
        char op = tokens[pos].value[0];
        pos++;
        ASTNode *right = parseTerm(tokens, pos);
        left = new BinaryOpNode(op, left, right);
    }

    return left;
}

ASTNode *parseAssignment(std::vector<Token> &tokens, int &pos)
{
    if (tokens[pos].type == INT_KEYWORD)
    {
        pos++; 
    }

    if (tokens[pos].type == IDENTIFIER)
    {
        std::string varName = tokens[pos++].value;
        if (tokens[pos].type == ASSIGN)
        {
            pos++; 
            ASTNode *expression = parseExpression(tokens, pos);
            return new AssignmentNode(varName, expression);
        }
    }

    std::cerr << "Syntax error in assignment." << std::endl;
    exit(1);
}

ASTNode *parseIfStatement(std::vector<Token> &tokens, int &pos)
{
    pos++;                                              
    ASTNode *condition = parseExpression(tokens, pos); 
    ASTNode *thenBranch = parseExpression(tokens, pos); 
    ASTNode *elseBranch = nullptr;

    if (tokens[pos].type == ELSE)
    {
        pos++;                                     
        elseBranch = parseExpression(tokens, pos); 
    }

    return new IfNode(condition, thenBranch, elseBranch);
}

ASTNode *parseWhileLoop(std::vector<Token> &tokens, int &pos)
{
    pos++; // Skip "while"
    ASTNode *condition = parseExpression(tokens, pos);
    ASTNode *body = parseExpression(tokens, pos);
    return new WhileNode(condition, body);
}

void printAST(ASTNode *node)
{
    if (auto *num = dynamic_cast<NumberNode *>(node))
    {
        std::cout << "Number: " << num->value << std::endl;
    }
    else if (auto *binOp = dynamic_cast<BinaryOpNode *>(node))
    {
        std::cout << "Binary Op: " << binOp->op << std::endl;
        printAST(binOp->left);
        printAST(binOp->right);
    }
    else if (auto *assign = dynamic_cast<AssignmentNode *>(node))
    {
        std::cout << "Assignment: " << assign->varName << std::endl;
        printAST(assign->expression);
    }
    else if (auto *ifNode = dynamic_cast<IfNode *>(node))
    {
        std::cout << "If Condition" << std::endl;
        printAST(ifNode->condition);
        std::cout << "Then Branch" << std::endl;
        printAST(ifNode->thenBranch);
        if (ifNode->elseBranch)
        {
            std::cout << "Else Branch" << std::endl;
            printAST(ifNode->elseBranch);
        }
    }
    else if (auto *whileNode = dynamic_cast<WhileNode *>(node))
    {
        std::cout << "While Loop" << std::endl;
        printAST(whileNode->condition);
        std::cout << "Loop Body" << std::endl;
        printAST(whileNode->body);
    }
}
