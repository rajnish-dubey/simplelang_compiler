//code_generator.cpp
#include "code_generator.h"
#include <iostream>

void generateCode(ASTNode *node)
{
    if (auto *num = dynamic_cast<NumberNode *>(node))
    {
        std::cout << "PUSH " << num->value << std::endl;
    }
    else if (auto *var = dynamic_cast<VariableNode *>(node))
    {
        std::cout << "LOAD " << var->name << std::endl;
    }
    else if (auto *binOp = dynamic_cast<BinaryOpNode *>(node))
    {
        generateCode(binOp->left);
        generateCode(binOp->right);
        switch (binOp->op)
        {
        case '+':
            std::cout << "ADD" << std::endl;
            break;
        case '-':
            std::cout << "SUB" << std::endl;
            break;
        case '*':
            std::cout << "MUL" << std::endl;
            break;
        case '/':
            std::cout << "DIV" << std::endl;
            break;
        default:
            std::cerr << "Unknown operator" << std::endl;
        }
    }
    else if (auto *assign = dynamic_cast<AssignmentNode *>(node))
    {
        generateCode(assign->expression);
        std::cout << "STORE " << assign->varName << std::endl;
    }
    else if (auto *ifNode = dynamic_cast<IfNode *>(node))
    {
        generateCode(ifNode->condition);
        std::cout << "JZ ELSE_LABEL" << std::endl;
        generateCode(ifNode->thenBranch);
        std::cout << "JMP END_IF" << std::endl;
        std::cout << "ELSE_LABEL:" << std::endl;
        if (ifNode->elseBranch)
        {
            generateCode(ifNode->elseBranch);
        }
        std::cout << "END_IF:" << std::endl;
    }
    else if (auto *whileNode = dynamic_cast<WhileNode *>(node))
    {
        std::cout << "LOOP_START:" << std::endl;
        generateCode(whileNode->condition);
        std::cout << "JZ LOOP_END" << std::endl;
        generateCode(whileNode->body);
        std::cout << "JMP LOOP_START" << std::endl;
        std::cout << "LOOP_END:" << std::endl;
    }
}
