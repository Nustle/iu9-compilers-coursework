#include "include/lexer/compiler.h"

#include <iostream>


int Compiler::AddName(const string &name) {
    auto nameCode = nameCodes.find(name);
    if (nameCode != nameCodes.end()) {
        return nameCode->second;
    } else {
        int code = (int) names.size();
        names.push_back(name);
        nameCodes[name] = code;
        return code;
    }
}

const string &Compiler::GetName(int code) {
    return names[code];
}

void Compiler::AddMessage(Position pos, MessageType type, const string &text) {
    messages[pos] = Message(type, text);
}

void Compiler::OutputMessages() {
    for (const auto &message: messages) {
        cout << message.first << ": " << message.second << endl;
    }
}
