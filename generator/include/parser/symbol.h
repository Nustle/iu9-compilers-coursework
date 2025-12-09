#pragma once

#include <string>
#include <vector>
#include <optional>
#include <functional>

using namespace std;

class Symbol {
public:
    enum class Type {
        Terminal,
        NonTerminal,
        Spec,
    };

    Symbol(string name, Type type)
    : name(std::move(name)), type(type) {}

    bool operator==(const Symbol& other) const {
        return type == other.type && name == other.name;
    }

    bool operator!=(const Symbol& other) const {
        return !(*this == other);
    }

    const string& GetName() const {
        return name;
    }
    Type GetType() const {
        return type;
    }

private:
    string name;
    Type type;
};

const auto Epsilon = Symbol{"ε", Symbol::Type::Spec};
const auto EndOfProgram = Symbol{"EOF", Symbol::Type::Terminal};

using SymbolVec    = vector<Symbol>;
using SymbolVecRef = reference_wrapper<const SymbolVec>;
using OptSymbolVec = optional<SymbolVecRef>;

namespace std {
    template<>
    struct hash<Symbol> {
        size_t operator()(Symbol const& s) const noexcept {
            auto h1 = hash<string>()(s.GetName());
            auto h2 = hash<int>()(static_cast<int>(s.GetType()));
            return h1 ^ (h2 << 1);
        }
    };
}
