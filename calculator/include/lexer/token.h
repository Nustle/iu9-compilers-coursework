#ifndef TOKEN_H
#define TOKEN_H

#include "include/lexer/fragment.h"

enum class DomainTag {
    Number,
    Plus,
    Star,
    LeftParen,
    RightParen,
    EndOfProgram,
};

inline string ToStringTag(const DomainTag tag) {
    switch (tag) {
        case DomainTag::Number: return "Number";
        case DomainTag::Plus: return "Plus";
        case DomainTag::Star: return "Star";
        case DomainTag::LeftParen: return "LeftParen";
        case DomainTag::RightParen: return "RightParen";
        case DomainTag::EndOfProgram: return "EOF";
    }
}

inline ostream& operator<<(ostream& os, const DomainTag &tag) {
    return os << ToStringTag(tag);
}

class Token {
public:
    virtual ~Token() = default;
    DomainTag GetTag() const {
        return Tag;
    }
    Fragment GetCoords() const {
        return Coords;
    }

protected:
    const DomainTag Tag;
    Fragment Coords;
    Token(DomainTag tag, const Position &starting, const Position &following)
    : Tag(tag), Coords(starting, following) {}
};

class NumberToken : public Token {
public:
    NumberToken(int val, const Position &starting, const Position &following)
    : val(val), Token(DomainTag::Number, starting, following) {}

    int GetVal() const {
        return val;
    }
private:
    int val;
};

class SpecToken : public Token {
public:
    SpecToken(DomainTag tag, const Position &starting, const Position &following)
    : Token(tag, starting, following) {}
};

class EOFToken : public Token {
public:
    EOFToken(const Position &starting, const Position &following)
    : Token(DomainTag::EndOfProgram, starting, following) {}
};

inline string ToStringToken(const Token &token) {
    switch (token.GetTag()) {
        case DomainTag::EndOfProgram: return "EOF";
        case DomainTag::Plus: return "+";
        case DomainTag::Star: return "*";
        case DomainTag::LeftParen: return "(";
        case DomainTag::RightParen: return ")";
        case DomainTag::Number: return "n";
    }
}

inline ostream& operator<<(ostream& os, const Token &token) {
    os << token.GetTag() << " " << token.GetCoords() << ": ";
    if (token.GetTag() == DomainTag::Number) {
        NumberToken number = dynamic_cast<const NumberToken &>(token);
        os << to_string(number.GetVal());
    } else {
        os << ToStringToken(token);
    }
    return os;
}

#endif