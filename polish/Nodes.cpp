#include "Nodes.h"
#include <cmath>
#include <string>
#include <stdexcept>
// Implement your AST subclasses' member functions here.


// To format a double for output:
//   std::ostringstream stream;
//   stream << value;
//   return stream.str();

std::string global = "M";

std::string Double::prefix() const {
    return global;
}

std::string Double::postfix() const {
    return global;
}

double Double::value() const {
    return number;
}

Addition::~Addition () {
    delete left;
    delete right;
}

std::string Addition::prefix()  const {
    return global;
}
std::string Addition::postfix() const {
    return global;
}
double Addition::value() const {
    return left->value() + right->value();
}

Subtraction::~Subtraction () {
    delete left;
    delete right;
}

std::string Subtraction::prefix()  const {
    return global;
}
std::string Subtraction::postfix() const {
    return global;
}
double Subtraction::value() const {
    return left->value() - right->value();
}

Multiplication::~Multiplication () {
    delete left;
    delete right;
}
std::string Multiplication::prefix()  const {
    return global;
}
std::string Multiplication::postfix() const {
    return global;
}
double Multiplication::value() const {
    return left->value() * right->value();
}
Division::~Division () {
    delete left;
    delete right;
}
std::string Division::prefix()  const {
    return global;
}
std::string Division::postfix() const {
    return global;
}
double Division::value() const {
    if(right->value() != 0) {
        return left->value() / right->value();
    }
    throw std::runtime_error("Division by zero.");
}

Modulo::~Modulo () {
    delete left;
    delete right;
}
std::string Modulo::prefix()  const {
    return global;
}
std::string Modulo::postfix() const {
    return global;
}
double Modulo::value() const {
    if(right->value() != 0) {
        return std::fmod(left->value(), right->value());
    }
    throw std::runtime_error("Division by zero.");
}
Negate::~Negate () {
    delete reverseAlignment;
}
std::string Negate::prefix()  const {
    return global;
}
std::string Negate::postfix() const {
    return global;
}
double Negate::value() const {
    return -reverseAlignment->value();
}



// DIvision by 0: std::runtime_error` with the message `Division by zero.`