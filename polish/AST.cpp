//Notes: So main.cpp tries to 


#include "AST.h"
#include "Nodes.h"
#include "Stack.h"
#include <sstream>
#include <iostream>

//Implement Parse Function, which searches through the stack (and its subtrees).

AST* AST::parse(const std::string& expression) { 
    std::istringstream expr(expression);
    std::string temp; 
    Stack stack;
    while (expr >> temp) { //Loop through each token in expression
        if (double a = stod(temp)) { // It's a double, so just insert stack
            
        }
        if (temp == "+") { //You call the function to add the previous two numbers, and then add that to the stack.

        }

        std::cout << temp;
    }

    // for(unsigned int i = 0; expression.length(); i+=2) { //Loop through every two things in the string. Then, find what type it is (+ val, etc.), which does a specific thing to the stack 

    // }

    // - If there is nothing on the stack at the end of parsing, say `No input.`
    // - If there are multiple nodes on the stack at the end of parsing, say `Too many operands.`
    // - If there aren't enough operands for an operator, say `Not enough operands.`
    // - If you encounter an invalid token, say `Invalid token: XXX`, where `XXX` is the invalid token.

    return nullptr;
}
