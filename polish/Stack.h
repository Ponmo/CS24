#ifndef STACK_H
#define STACK_H
#include "AST.h"

// Use this file to define your Stack type.
// Implement its member functions in Stack.cpp.

struct Stack {
    // TODO: Probably want to implement a resize instead of a set length like either through a vector, or a linked list but that's a lot of work.
    AST* array[100];
    unsigned long counter = 0;

    ~Stack();
    AST* pop();
    void push(AST*);

};

#endif
