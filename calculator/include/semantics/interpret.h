#ifndef INTERPRET_H
#define INTERPRET_H

#include "include/parser/node.h"
    
class Interpreter {
public:
    int Interpret(const InnerNode& root);
private:
    int ParseE(const InnerNode& e);
    int ParseE1(const InnerNode& e1);
    int ParseT(const InnerNode& t);
    int ParseT1(const InnerNode& t1);
    int ParseF(const InnerNode& f);
};

#endif
