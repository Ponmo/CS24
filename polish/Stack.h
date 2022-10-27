#ifndef STACK_H
#define STACK_H
#include "AST.h"

// Use this file to define your Stack type.
// Implement its member functions in Stack.cpp.

struct Stack {
    // TODO: Probably want to implement a resizable vector instead of a set length or a linked list but that's a lot of work (+ even my TI-84 calculator can't take in pseudo-infinite numbers (like 40 in total)
    AST* array[100];
    unsigned long counter = 0;

    ~Stack();
    AST* pop();
    void push(AST*);

};

#endif
