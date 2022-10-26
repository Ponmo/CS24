#ifndef NODES_H
#define NODES_H

#include "AST.h"

// Declare your AST subclasses here.
// Implement their member functions in Nodes.cpp.

class Double {
public:
    double number;

public:
    ~Double() {}
    std::string prefix()  const;
    std::string postfix() const;
    double      value()   const;
};

class Addition {
public:
    char a;

public:
    ~Addition() {}
    std::string prefix()  const;
    std::string postfix() const;
    double      value()   const;
};



#endif
