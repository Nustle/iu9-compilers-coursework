#ifndef MESSAGE_H
#define MESSAGE_H

#include <vector>
#include <string>

using namespace std;

enum class MessageType {
    Error,
};

class Message {
public:
    MessageType type;
    string text;

    Message() = default;

    Message(MessageType type, const string &text)
    : type(type), text(text) {}

    friend ostream& operator<<(ostream& os, const Message &message) {
        string msg_type;
        switch (message.type) {
            case MessageType::Error: {
                msg_type = "Error";
            }
        }
        string sep = " ";
        os << msg_type << sep << message.text;
        return os;
    }

};

#endif
