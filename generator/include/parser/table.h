#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <unordered_map>
#include <variant>
#include <optional>

#include "symbol.h"

using namespace std;

struct Shift {
    int state;
    explicit Shift(int s) : state(s) {}
};

struct Reduce {
    Symbol lhs;
    vector<Symbol> rhs;
    Reduce(Symbol l, vector<Symbol> r) : lhs(std::move(l)), rhs(std::move(r)) {}
};

struct Accept {};

using Action = variant<Shift, Reduce, Accept>;

class Table {
    Symbol axiom;
    unordered_map<int, unordered_map<Symbol, Action>> action_table;
    unordered_map<int, unordered_map<Symbol, int>> goto_table;

public:
    Table();

    const Symbol& GetAxiom() const {
        return axiom;
    }

    optional<Action> GetAction(int state, const Symbol& terminal) const {
        auto stateIt = action_table.find(state);
        if (stateIt == action_table.cend()) {
            return nullopt;
        }
        const auto& row = stateIt->second;
        auto colIt = row.find(terminal);
        if (colIt == row.cend()) {
            return nullopt;
        }
        return colIt->second;
    }

    optional<int> GetGoto(int state, const Symbol& non_terminal) const {
        auto stateIt = goto_table.find(state);
        if (stateIt == goto_table.cend()) {
            return nullopt;
        }
        const auto& row = stateIt->second;
        auto colIt = row.find(non_terminal);
        if (colIt == row.cend()) {
            return nullopt;
        }
        return colIt->second;
    }
};

#endif
