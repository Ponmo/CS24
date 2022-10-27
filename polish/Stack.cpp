#include "Stack.h"

// Implement your Stack member functions here.

//Member functions include constructor, push, pop , deconstructor.

Stack::~Stack () {

}
AST* Stack::pop() {
    AST* child = array[counter - 1];
    counter--;
    return child;
}
void Stack::push(AST* curr) {
    array[counter] = curr;
    counter++;
    return;
}