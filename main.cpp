//main.cpp
#include <iostream>
#include <string>
#include "lexer.h"
#include "parser.h"
#include "code_generator.h"

void printAST(ASTNode *node); 

int main()
{
    std::string input;
    std::cout << "Welcome to SimpleLang Compiler!" << std::endl;
    std::cout << "Enter your expressions (type 'exit' to quit):" << std::endl;

    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, input);  // taking user input

        if (input == "exit")
            break;

        std::vector<Token> tokens = lexer(input);

        // Print tokens for debugging
        for (const auto &token : tokens)
        {
            std::cout << "Token Type: " << token.type << ", Value: " << token.value << std::endl;
        }

        int pos = 0;
        ASTNode *ast = parseExpression(tokens, pos);

        // Print the AST for debugging
        printAST(ast);

        std::cout << "Generated Assembly:" << std::endl;
        generateCode(ast);

        delete ast;
    }

    std::cout << "Exiting SimpleLang Compiler." << std::endl;
    return 0;
}



// no we will push it into our github repo
// lets go

// now we will add gitignore file