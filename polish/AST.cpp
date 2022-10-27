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
    Stack Stack;
    while (expr >> temp) { //Loop through each token in expression
        auto result = double();
        auto i = std::istringstream(temp);
        i >> result;   
        //!(sscanf(temp.c_str(), "%lf",s &num) != 1) && 
        if (!i.fail() && i.eof()) { // It's a double, so just insert stack
            Double* a = new Double;
            a->number = result;
            Stack.push(a);
        }
        else if (temp == "+") { //You call the function to add the previous two numbers, and then add that to the stack.
            Addition* a = new Addition;
            a -> right = Stack.pop();
            a -> left = Stack.pop();
                // throw std::runtime_error("Not enough operands")
            Stack.push(a);
        }
        else if (temp == "-") {
            Subtraction* a = new Subtraction;
            a -> right = Stack.pop();
            a -> left = Stack.pop();
            Stack.push(a);
        }
        else if (temp == "*") {
            Multiplication* a = new Multiplication;
            a -> right = Stack.pop();
            a -> left = Stack.pop();
            Stack.push(a);
        }
        else if (temp == "/") {
            Division* a = new Division;
            a -> right = Stack.pop();
            a -> left = Stack.pop();
            Stack.push(a);
        }
        else if (temp == "%") {
            Modulo* a = new Modulo;
            a -> right = Stack.pop();
            a -> left = Stack.pop();
            Stack.push(a);
        }
        else if (temp == "~") {
            Negate* a = new Negate;
            a -> reverseAlignment = Stack.pop();
            Stack.push(a);
        }
        else {
            throw std::runtime_error("Invalid token: " + temp);
        }
    }
    if (Stack.counter == 0) { 
        throw std::runtime_error("No input.");
    }
    else if (Stack.counter > 1) {
        throw std::runtime_error("Too many operands.");
    }

    // - If there is nothing on the stack at the end of parsing, say `No input.`
    // - If there are multiple nodes on the stack at the end of parsing, say `Too many operands.`
    // - If there aren't enough operands for an operator, say `Not enough operands.`
    // - If you encounter an invalid token, say `Invalid token: XXX`, where `XXX` is the invalid token.
    return Stack.pop();
}
