#ifndef NODES_H
#define NODES_H

#include "AST.h"

// Declare your AST subclasses here.
// Implement their member functions in Nodes.cpp.

class Double: public AST {
    public:
        double number;
        bool top = false;

    public:
        ~Double() {}
        std::string prefix()  const;
        std::string postfix() const;
        double      value()   const;
};

class Addition: public AST { //only left and right for operands
    public:
        AST* left;
        AST* right;
        bool top = false;

    public:
        ~Addition();
        std::string prefix()  const;
        std::string postfix() const;
        double      value()   const;
};

class Subtraction: public AST { 
    public:
        AST* left;
        AST* right;
        bool top = false;

    public:
        ~Subtraction();
        std::string prefix()  const;
        std::string postfix() const;
        double value() const;
};

class Multiplication: public AST {
    public:
        AST* left;
        AST* right;
        bool top = false;

    public:
        ~Multiplication();
        std::string prefix()  const;
        std::string postfix() const;
        double      value()   const;
};

class Division: public AST {
    public:
        AST* left;
        AST* right;
        bool top = false;

    public:
        ~Division();
        std::string prefix()  const;
        std::string postfix() const;
        double      value()   const;
};

class Modulo: public AST {
    public:
        AST* left;
        AST* right;
        bool top = false;

    public:
        ~Modulo();
        std::string prefix()  const;
        std::string postfix() const;
        double      value()   const;
};

class Negate: public AST {
    public:
        AST* reverseAlignment;
        bool top = false;

    public:
        ~Negate();
        std::string prefix()  const;
        std::string postfix() const;
        double      value()   const;
};



#endif
