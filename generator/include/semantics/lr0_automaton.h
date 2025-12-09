#ifndef LR0_AUTOMATON_H
#define LR0_AUTOMATON_H

#include "ast.h"
#include <set>
#include <map>

struct Situation {
    Symbol lhs;
    SententialForm rhs;
    size_t dot_position;

    Situation(Symbol l, SententialForm r, size_t pos = 0)
        : lhs(std::move(l)), rhs(std::move(r)), dot_position(pos) {}

    bool operator==(const Situation& other) const {
        return lhs == other.lhs && rhs == other.rhs && dot_position == other.dot_position;
    }

    bool operator<(const Situation& other) const {
        if (lhs.GetName() != other.lhs.GetName())
            return lhs.GetName() < other.lhs.GetName();
        if (dot_position != other.dot_position)
            return dot_position < other.dot_position;
        if (rhs.size() != other.rhs.size())
            return rhs.size() < other.rhs.size();
        for (size_t i = 0; i < rhs.size(); ++i) {
            if (rhs[i].GetName() != other.rhs[i].GetName())
                return rhs[i].GetName() < other.rhs[i].GetName();
        }
        return false;
    }

    bool IsComplete() const {
        return dot_position >= rhs.size();
    }

    optional<Symbol> GetSymbolAfterDot() const {
        if (dot_position < rhs.size()) {
            return rhs[dot_position];
        }
        return nullopt;
    }

    Situation Advance() const {
        return Situation(lhs, rhs, dot_position + 1);
    }
};

struct State {
    int id;
    set<Situation> items;

    explicit State(int id_val) : id(id_val) {}

    bool operator==(const State& other) const {
        return items == other.items;
    }
};

struct Transition {
    int from_state;
    int to_state;
    Symbol symbol;

    Transition(int from, int to, Symbol sym)
        : from_state(from), to_state(to), symbol(std::move(sym)) {}
};

class LR0Automaton {
public:
    explicit LR0Automaton(const shared_ptr<Program>& program);

    const vector<State>& GetStates() const {
        return states;
    }

    const vector<Transition>& GetTransitions() const {
        return transitions;
    }

    const Symbol& GetStart() const {
        return start;
    }

    void OutputAutomaton(const string& output_path) const;
private:
    void BuildAutomaton();
    set<Situation> Closure(const set<Situation>& items);
    set<Situation> Goto(const set<Situation>& items, const Symbol& symbol);
    int CreateState(const set<Situation>& items);
    pair<int, bool> HasState(const set<Situation>& items);

    shared_ptr<Program> program;
    Symbol start;
    vector<State> states;
    vector<Transition> transitions;
    unordered_map<Symbol, vector<SententialForm>> grammar_rules;
};

#endif
