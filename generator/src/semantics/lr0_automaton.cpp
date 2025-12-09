#include "include/semantics/lr0_automaton.h"
#include <queue>
#include <unordered_set>
#include <fstream>

LR0Automaton::LR0Automaton(const shared_ptr<Program>& program_)
    : program(program_), start({"dummy", Symbol::Type::NonTerminal}) {

    for (const auto& rule : program->GetRules()) {
        const Symbol& lhs = rule->GetLhs();
        const auto& rhs_list = rule->GetRhs();

        for (const auto& rhs_ptr : rhs_list) {
            grammar_rules[lhs].push_back(*rhs_ptr);
        }
    }

    BuildAutomaton();
}

set<Situation> LR0Automaton::Closure(const set<Situation>& items) {
    set<Situation> res = items;
    queue<Situation> queue_states;

    for (const auto& item : items) {
        queue_states.push(item);
    }

    while (!queue_states.empty()) {
        Situation current = queue_states.front();
        queue_states.pop();

        auto symbol_opt = current.GetSymbolAfterDot();
        if (!symbol_opt || symbol_opt->GetType() != Symbol::Type::NonTerminal) {
            continue;
        }

        const Symbol& non_terminal = *symbol_opt;

        if (grammar_rules.count(non_terminal)) {
            for (const auto& rhs : grammar_rules[non_terminal]) {
                Situation new_item(non_terminal, rhs, 0);

                if (res.insert(new_item).second) {
                    queue_states.push(new_item);
                }
            }
        }
    }

    return res;
}

set<Situation> LR0Automaton::Goto(const set<Situation>& items, const Symbol& symbol) {
    set<Situation> res;

    for (const auto& item : items) {
        auto symbol_after_dot = item.GetSymbolAfterDot();

        if (symbol_after_dot && *symbol_after_dot == symbol) {
            res.insert(item.Advance());
        }
    }

    return Closure(res);
}

pair<int, bool> LR0Automaton::HasState(const set<Situation>& items) {
    pair<int, bool> res = {0, false};
    for (const auto& state : states) {
        if (state.items == items) {
            res = {state.id, true};
        }
    }
    return res;
}

int LR0Automaton::CreateState(const set<Situation>& items) {
    int new_id = static_cast<int>(states.size());
    State new_state(new_id);
    new_state.items = items;
    states.push_back(new_state);

    return new_id;
}

void LR0Automaton::BuildAutomaton() {
    Situation start_item(start, {program->GetAxiom()}, 0);
    set<Situation> start_items = {start_item};
    set<Situation> start_closure = Closure(start_items);

    int start_state_id = CreateState(start_closure);

    queue<int> queue_states;
    set<int> processed;
    queue_states.push(start_state_id);

    while (!queue_states.empty()) {
        int current_state_id = queue_states.front();
        queue_states.pop();

        if (processed.count(current_state_id)) {
            continue;
        }
        processed.insert(current_state_id);

        set<Situation> current_items = states[current_state_id].items;

        unordered_set<Symbol> symbols_after_dot;
        for (const auto& item : current_items) {
            auto symbol_opt = item.GetSymbolAfterDot();
            if (symbol_opt) {
                symbols_after_dot.insert(*symbol_opt);
            }
        }

        for (const auto& symbol : symbols_after_dot) {
            set<Situation> goto_items = Goto(current_items, symbol);

            if (!goto_items.empty()) {
                pair<int, bool> has_state = HasState(goto_items);
                int target_state_id = has_state.first;
                if (!has_state.second) {
                    target_state_id = CreateState(goto_items);
                }

                transitions.emplace_back(
                    current_state_id, target_state_id, symbol
                );

                queue_states.push(target_state_id);
            }
        }
    }
}

void LR0Automaton::OutputAutomaton(const string& output_path) const {
    ofstream os(output_path);

    os << "digraph {\n";

    for (const auto& state : states) {
        string label;
        for (const auto& item : state.items) {
            label += item.lhs.GetName() + " -> ";

            for (size_t i = 0; i < item.rhs.size(); ++i) {
                if (i == item.dot_position) {
                    label += ". ";
                }
                label += item.rhs[i].GetName() + " ";
            }

            if (item.dot_position >= item.rhs.size()) {
                label += ".";
            }

            label += "\\n";
        }

        if (!label.empty() && label.size() >= 2) {
            label = label.substr(0, label.size() - 2);
        }

        bool is_accept = false;
        for (const auto& item : state.items) {
            if (item.lhs == start && item.IsComplete()) {
                is_accept = true;
                break;
            }
        }

        os << "  " << state.id << " [shape = \"rectangle\"";
        if (is_accept) {
            os << " peripheries = 2";
        }
        os << " label = \"" << label << "\"]\n";
    }

    for (const auto& transition : transitions) {
        os << "  " << transition.from_state << " -> " << transition.to_state
           << " [label = \"" << transition.symbol.GetName() << "\"]\n";
    }

    os << "}\n";
}
