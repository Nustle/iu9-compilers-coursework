#ifndef PARSER_H
#define PARSER_H

#include "include/parser/node.h"
#include "include/lexer/scanner.h"
#include "include/parser/table.h"



class Parser {
public:
    unique_ptr<Node> Parse(Scanner *scanner);

private:
    Table table = {
        #include "include/parser/table.h"
    };
};

#endif
