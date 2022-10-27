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
    size_t count = 0;
    Stack Stack;

    std::string john = expression;
    std::istringstream expr2(john);
    size_t count2 = 0;
    std::string line;
    while (std::getline(expr2, line, ' ' ) ) ++count2;

    while (expr >> temp) { //Loop through each token in expression
        count++;
        auto result = double();
        auto i = std::istringstream(temp);
        i >> result;   
        //!(sscanf(temp.c_str(), "%lf",s &num) != 1) && 
        if (!i.fail() && i.eof()) { // It's a double, so just insert stack
            Double* a = new Double;
            a->number = result;
            Stack.push(a);
            if(count == count2) {
                a->top = true;
            }
        }
        else if (temp == "+") { //You call the function to add the previous two numbers, and then add that to the stack.
            if (Stack.counter < 2) {
                while(Stack.counter) {
                    delete Stack.pop();
                }
                throw std::runtime_error("Not enough operands.");
            }
            else {
                Addition* a = new Addition;
                a -> right = Stack.pop();
                a -> left = Stack.pop();
                Stack.push(a);
                if(count == count2) {
                    a->top = true;
                }
            }
        }
        else if (temp == "-") {
            if (Stack.counter < 2) {
                while(Stack.counter) {
                    delete Stack.pop();
                }
                throw std::runtime_error("Not enough operands.");
            }
            else {
                Subtraction* a = new Subtraction;
                a -> right = Stack.pop();
                a -> left = Stack.pop();
                Stack.push(a);
                if(count == count2) {
                    a->top = true;
                }
            }
        }
        else if (temp == "*") {
            if (Stack.counter < 2) {
                while(Stack.counter) {
                    delete Stack.pop();
                }
                throw std::runtime_error("Not enough operands.");
            }
            else {
                Multiplication* a = new Multiplication;
                a -> right = Stack.pop();
                a -> left = Stack.pop();
                Stack.push(a);
                if(count == count2) {
                    a->top = true;
                }
            }
        }
        else if (temp == "/") {
            if (Stack.counter < 2) {
                while(Stack.counter) {
                    delete Stack.pop();
                }
                throw std::runtime_error("Not enough operands.");
            }
            else {
                Division* a = new Division;
                a -> right = Stack.pop();
                a -> left = Stack.pop();
                Stack.push(a);
                if(count == count2) {
                    a->top = true;
                }
            }
        }
        else if (temp == "%") {
            if (Stack.counter < 2) {
                while(Stack.counter) {
                    delete Stack.pop();
                }
                throw std::runtime_error("Not enough operands.");
            }
            else {
                Modulo* a = new Modulo;
                a -> right = Stack.pop();
                a -> left = Stack.pop();
                Stack.push(a);
                if(count == count2) {
                    a->top = true;
                }
            }
        }
        else if (temp == "~") {
            if (Stack.counter < 1) {
                while(Stack.counter) {
                    delete Stack.pop();
                }
                throw std::runtime_error("Not enough operands.");
            }
            else {
                Negate* a = new Negate;
                a -> reverseAlignment = Stack.pop();
                Stack.push(a);
                if(count == count2) {
                    a->top = true;
                }
            }
        }
        else {
            while(Stack.counter) {
                delete Stack.pop();
            }
            throw std::runtime_error("Invalid token: " + temp);
        }
    }
    if (Stack.counter == 0) { 
        throw std::runtime_error("No input.");
    }
    else if (Stack.counter > 1) {
        while(Stack.counter) {
            delete Stack.pop();
        }
        throw std::runtime_error("Too many operands.");
    }


    //set top true for the top node

    // - If there is nothing on the stack at the end of parsing, say `No input.`
    // - If there are multiple nodes on the stack at the end of parsing, say `Too many operands.`
    // - If there aren't enough operands for an operator, say `Not enough operands.`
    // - If you encounter an invalid token, say `Invalid token: XXX`, where `XXX` is the invalid token.

    return Stack.pop();
}
