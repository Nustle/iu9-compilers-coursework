#ifndef COMPILER_H
#define COMPILER_H

#include <map>
#include <vector>
#include "include/lexer/message.h"
#include "include/lexer/position.h"

class Compiler {
public:
    Compiler() {
        messages = map<Position, Message>();
        nameCodes = map<string, int>();
        names = vector<string>();
    }

    int AddName(const string &name);

    const string &GetName(int code);

    void AddMessage(Position pos, MessageType type, const string &text);

    void OutputMessages();

private:
    map <Position, Message> messages;
    map<string, int> nameCodes;
    vector <string> names;
};

#endif