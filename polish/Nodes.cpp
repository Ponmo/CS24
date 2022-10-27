#include "Nodes.h"
#include <cmath>
#include <string>
#include <stdexcept>
#include <stdlib.h>

// Implement your AST subclasses' member functions here.


// To format a double for output:
//   std::ostringstream stream;
//   stream << value;
//   return stream.str();

std::string global = "M";

// std::string reverse(std::string str)
// {
//     std::string reversedString;
//     for (int i = str.length() - 1; i >= 0; i--) {
//         reversedString.push_back(str[i]);
//     }
//     return reversedString;
// }
 


std::string Double::prefix() const {
    std::string str = std::to_string (number);
    str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
    str.erase ( str.find_last_not_of('.') + 1, std::string::npos ); 
    if(!top) {
        return str + " ";
    }
    return str;
}

std::string Double::postfix() const {
    std::string str = std::to_string (number);
    str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
    str.erase ( str.find_last_not_of('.') + 1, std::string::npos ); 
    if(!top) {
        return str + " ";
    }
    return str;
}

double Double::value() const {
    return number;
}

Addition::~Addition () {
    delete left;
    delete right;
}
std::string Addition::prefix()  const {
    std::string curr = "+ " + left -> prefix() + right -> prefix();
    if(!top) {
        return curr;
    }
    if (!curr.empty()) {
        curr.resize(curr.size() - 1);
    }
    return curr;
    // return left -> postfix() + right -> postfix() + "+";
}
std::string Addition::postfix() const {
    if(!top) {
        return left -> postfix() + right -> postfix() + "+ ";
    }
    return left -> postfix() + right -> postfix() + "+";
}
double Addition::value() const {
    return left->value() + right->value();
}

Subtraction::~Subtraction () {
    delete left;
    delete right;
}
std::string Subtraction::prefix()  const {
    std::string curr = "- " + left -> prefix() + right -> prefix();
    if(!top) {
        return curr;
    }
    if (!curr.empty()) {
        curr.resize(curr.size() - 1);
    }
    return curr;
    // return reverse(left -> postfix() + right -> postfix() + "-");
}
std::string Subtraction::postfix() const {
    if(!top) {
        return left -> postfix() + right -> postfix() + "- ";
    }
    return left -> postfix() + right -> postfix() + "-";
}
double Subtraction::value() const {
    return left->value() - right->value();
}
Multiplication::~Multiplication () {
    delete left;
    delete right;
}
std::string Multiplication::prefix()  const {
    std::string curr = "* " + left -> prefix() + right -> prefix();
    if(!top) {
        return curr;
    }
    if (!curr.empty()) {
        curr.resize(curr.size() - 1);
    }
    return curr;
    // return reverse(left -> postfix() + right -> postfix() + "*");
}
std::string Multiplication::postfix() const {
    if(!top) {
        return left -> postfix() + right -> postfix() + "* ";
    }
    return left -> postfix() + right -> postfix() + "*";
}
double Multiplication::value() const {
    return left->value() * right->value();
}
Division::~Division () {
    delete left;
    delete right;
}
std::string Division::prefix()  const {
    std::string curr = "/ " + left -> prefix() + right -> prefix();
    if(!top) {
        return curr;
    }
    if (!curr.empty()) {
        curr.resize(curr.size() - 1);
    }
    return curr;
    // return reverse(left -> postfix() + right -> postfix() + "/");
}
std::string Division::postfix() const {
    if(!top) {
        return left -> postfix() + right -> postfix() + "/ ";
    }
    return left -> postfix() + right -> postfix() + "/";
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
    std::string curr = "% " + left -> prefix() + right -> prefix();
    if(!top) {
        return curr;
    }
    if (!curr.empty()) {
        curr.resize(curr.size() - 1);
    }
    return curr;
    // return reverse(left -> postfix() + right -> postfix() + "%");
}
std::string Modulo::postfix() const {
    if(!top) {
        return left -> postfix() + right -> postfix() + "% ";
    }
    return left -> postfix() + right -> postfix() + "%";
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
    std::string curr = "~ " + reverseAlignment->prefix();
    if(!top) {
        return curr;
    }
    if (!curr.empty()) {
        curr.resize(curr.size() - 1);
    }
    return curr;
    // return reverse(reverseAlignment -> postfix() + "~");
}
std::string Negate::postfix() const {
    if(!top) {
        return reverseAlignment -> postfix() + "~ ";
    }
    return reverseAlignment -> postfix() + "~";
}
double Negate::value() const {
    return -reverseAlignment->value();
}



// DIvision by 0: std::runtime_error` with the message `Division by zero.`