#ifndef TABLE_GENERATOR_H
#define TABLE_GENERATOR_H

#include "lr0_automaton.h"
#include "include/parser/table.h"
#include <unordered_set>

class FirstFollow {
public:
    explicit FirstFollow(const shared_ptr<Program>& program) {
        BuildFirst(program);
        BuildFollow(program);
    }

    const unordered_map<Symbol, unordered_set<Symbol>>& GetFirst() const {
        return first;
    }

    const unordered_map<Symbol, unordered_set<Symbol>>& GetFollow() const {
        return follow;
    }

private:
    void BuildFirst(const shared_ptr<Program>& program);
    void BuildFollow(const shared_ptr<Program>& program);
    unordered_map<Symbol, unordered_set<Symbol>> first;
    unordered_map<Symbol, unordered_set<Symbol>> follow;
};

class TableGenerator {
public:
    TableGenerator(const shared_ptr<Program>& program, const FirstFollow& first_follow);
    void Generate(const string& out_path) const;

    const Symbol& GetAxiom() const {
        return program->GetAxiom();
    }

    void GenerateAutomaton(const string& out_path) const {
        return automaton->OutputAutomaton(out_path);
    }

private:
    shared_ptr<Program> program;
    FirstFollow first_follow;
    unique_ptr<LR0Automaton> automaton;

    unordered_map<int, unordered_map<Symbol, Action>> action_table;
    unordered_map<int, unordered_map<Symbol, int>> goto_table;
};

#endif
