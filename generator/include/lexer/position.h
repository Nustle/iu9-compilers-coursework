#ifndef POSITION_H
#define POSITION_H

#include <string>
#include <ostream>

using namespace std;

class Position {
public:
    explicit Position(string *program)
    : line(1), pos(1), index(0), program(program) {}

    bool operator<(const Position &other) const {
        return index < other.index;
    }

    friend ostream &operator<<(ostream &os, const Position &p) {
        os << "(" << p.line << ", " << p.pos << ")";
        return os;
    };

    bool IsNewLine();
    bool EndOfProgram();

    Position& operator++(int) {
        if (index < program->size()) {
            auto c = static_cast<unsigned char>((*program)[index]);
            if (IsNewLine()) {
                if (c == '\r') {
                    index++;
                }
                line++;
                pos = 1;
            } else if ((c & 0xC0) != 0x80) {
                pos++;
            }
            index++;
        }
        return *this;
    }

    Position& operator+=(size_t k) {
        for (size_t i = 0; i < k; i++) {
            this->operator++(1);
        }
        return *this;
    }

    int GetLine() const;
    int GetPos() const;
    int GetIndex() const;
    void AdvanceLine();
    void AdvancePos();
    void AdvanceIndex();
    void PosDefault();
private:
    int line;
    int pos;
    int index;
    string *program;
};

#endif