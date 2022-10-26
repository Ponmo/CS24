#ifndef NODES_H
#define NODES_H

#include "AST.h"

// Declare your AST subclasses here.
// Implement their member functions in Nodes.cpp.

class Double: public AST {
public:
    double number;

public:
    ~Double() {}
    std::string prefix()  const;
    std::string postfix() const;
    double      value()   const;
};

class Addition: public AST { //only left and right for operands
public:
    char a;
    AST* left;
    AST* right;

public:
    ~Addition() {}
    std::string prefix()  const;
    std::string postfix() const;
    double      value()   const;
};
















class Subtraction: public AST {
public:
    char s = '-';

public:
    ~Subtraction() {}
    std::string prefix()  const;
    std::string postfix() const;
    double      value()   const;
};

class Multiplication: public AST {
public:
    char m = '*';

public:
    ~Multiplication() {}
    std::string prefix()  const;
    std::string postfix() const;
    double      value()   const;
};

class Division: public AST {
public:
    char d = '/';

public:
    ~Division() {}
    std::string prefix()  const;
    std::string postfix() const;
    double      value()   const;
};

class Modulo: public AST {
public:
    char m = '%';

public:
    ~Modulo() {}
    std::string prefix()  const;
    std::string postfix() const;
    double      value()   const;
};

class Negate: public AST {
public:
    char d = '~';

public:
    ~Negate() {}
    std::string prefix()  const;
    std::string postfix() const;
    double      value()   const;
};



#endif
