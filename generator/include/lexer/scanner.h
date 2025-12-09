#ifndef SCANNER_H
#define SCANNER_H

#include <memory>
#include <iostream>
#include "include/lexer/token.h"
#include "include/lexer/compiler.h"


class Scanner {
public:
    Scanner(const string &text, Compiler *compiler)
    : program(text), compiler(compiler), cur(&program) {}

    unique_ptr <Token> NextToken();

    void OutputComments() {
        for (auto comment : comments) {
            cout << comment << endl;
        }
    }

private:
    string program;
    Compiler *compiler;
    vector <Fragment> comments;
    Position cur;
};


#endif
