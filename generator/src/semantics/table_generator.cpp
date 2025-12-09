#include "include/semantics/table_generator.h"
#include <fstream>
#include <algorithm>

void FirstFollow::BuildFirst(const shared_ptr<Program>& program) {
    for (const auto& nt : program->GetNonterminals()) {
        first[nt] = {};
    }

    bool changed;
    do {
        changed = false;
        for (const auto& rule : program->GetRules()) {
            auto left = rule->GetLhs();
            for (const auto& alt_ptr : rule->GetRhs()) {
                const auto& alpha = *alt_ptr;
                bool all_nullable = true;
                for (const auto & sym_alpha : alpha) {
                    if (sym_alpha.GetType() == Symbol::Type::Terminal) {
                        if (first[left].insert(sym_alpha).second) {
                            changed = true;
                        }
                        all_nullable = false;
                        break;
                    }
                    for (auto& t : first[sym_alpha]) {
                        if (t != Epsilon) {
                            if (first[left].insert(t).second) {
                                changed = true;
                            }
                        }
                    }
                    if (!first[sym_alpha].count(Epsilon)) {
                        all_nullable = false;
                        break;
                    }
                }
                if (all_nullable) {
                    if (first[left].insert(Epsilon).second) {
                        changed = true;
                    }
                }
            }
        }

    } while (changed);
}

void FirstFollow::BuildFollow(const shared_ptr<Program>& program) {
    for (auto const& left : program->GetNonterminals()) {
        follow[left] = {};
    }
    follow[program->GetAxiom()].insert(EndOfProgram);

    bool changed;
    do {
        changed = false;
        for (auto const& rule_ptr : program->GetRules()) {
            const auto& left = rule_ptr->GetLhs();
            for (auto const& alt_ptr : rule_ptr->GetRhs()) {
                const auto& alpha = *alt_ptr;
                for (size_t i = 0; i < alpha.size(); ++i) {
                    const auto& sym_alpha = alpha[i];
                    if (sym_alpha.GetType() != Symbol::Type::NonTerminal) {
                        continue;
                    }
                    bool all_nullable = true;
                    for (size_t j = i + 1; j < alpha.size(); ++j) {
                        const auto& sym_alpha_next = alpha[j];
                        if (sym_alpha_next.GetType() == Symbol::Type::Terminal) {
                            if (follow[sym_alpha].insert(sym_alpha_next).second) {
                                changed = true;
                            }
                            all_nullable = false;
                            break;
                        }
                        for (auto const& t : first[sym_alpha_next]) {
                            if (t != Epsilon) {
                                if (follow[sym_alpha].insert(t).second) {
                                    changed = true;
                                }
                            }
                        }
                        if (!first[sym_alpha_next].count(Epsilon)) {
                            all_nullable = false;
                            break;
                        }
                    }
                    if (all_nullable) {
                        for (auto const& t : follow[left]) {
                            if (follow[sym_alpha].insert(t).second) {
                                changed = true;
                            }
                        }
                    }
                }
            }
        }
    } while (changed);
}

TableGenerator::TableGenerator(const shared_ptr<Program>& program_, const FirstFollow &first_follow_)
: program(program_), first_follow(first_follow_) {
    automaton = make_unique<LR0Automaton>(program);

    const auto& states = automaton->GetStates();
    const auto& transitions = automaton->GetTransitions();
    const auto& follow_sets = first_follow.GetFollow();

    for (const auto& transition : transitions) {
        const Symbol& symbol = transition.symbol;

        if (symbol.GetType() == Symbol::Type::Terminal) {
            action_table[transition.from_state].emplace(symbol, Shift{transition.to_state});
        } else {
            goto_table[transition.from_state].emplace(symbol, transition.to_state);
        }
    }

    for (const auto& state : states) {
        for (const auto& item : state.items) {
            if (item.IsComplete()) {
                if (item.lhs == automaton->GetStart()) {
                    action_table[state.id].emplace(EndOfProgram, Accept{});
                } else {
                    auto follow_it = follow_sets.find(item.lhs);
                    if (follow_it != follow_sets.end()) {
                        for (const auto& terminal : follow_it->second) {
                            action_table[state.id].emplace(terminal, Reduce{item.lhs, item.rhs});
                        }
                    }
                }
            }
        }
    }
}

void TableGenerator::Generate(const string& out_path) const {
    ofstream ofs(out_path);

    ofs << "#include \"include/parser/table.h\"\n\n";
    ofs << "Table::Table()\n"
           ": axiom({\"" << GetAxiom().GetName() << "\", Symbol::Type::NonTerminal}),\n"
           "  action_table({\n";

    vector<int> state_ids;
    for (const auto& [state_id, _] : action_table) {
        state_ids.push_back(state_id);
    }
    sort(state_ids.begin(), state_ids.end());

    bool first_state = true;
    for (int state_id : state_ids) {
        const auto& actions = action_table.at(state_id);

        if (!first_state) ofs << ",\n\n";
        first_state = false;

        ofs << "  \t{" << state_id << ", {\n";

        bool first_action = true;
        for (const auto& [symbol, action] : actions) {
            if (!first_action) ofs << ",\n";
            first_action = false;

            ofs << "  \t\t{{\"" << symbol.GetName() << "\", Symbol::Type::Terminal}, ";

            if (holds_alternative<Shift>(action)) {
                ofs << "Shift(" << get<Shift>(action).state << ")";
            } else if (holds_alternative<Reduce>(action)) {
                const auto& reduce = get<Reduce>(action);
                ofs << "Reduce(\n";
                ofs << "  \t\t\t{\"" << reduce.lhs.GetName() << "\", Symbol::Type::NonTerminal},\n";
                ofs << "  \t\t\t{";
                for (size_t i = 0; i < reduce.rhs.size(); ++i) {
                    if (i > 0) ofs << ", ";
                    ofs << "{\"" << reduce.rhs[i].GetName() << "\", Symbol::Type::"
                        << (reduce.rhs[i].GetType() == Symbol::Type::NonTerminal ? "NonTerminal" : "Terminal")
                        << "}";
                }
                ofs << "}\n  \t\t)";
            } else if (holds_alternative<Accept>(action)) {
                ofs << "Accept{}";
            }
            ofs << "}";
        }

        ofs << "\n  \t}}";
    }

    ofs << "\n  }),\n";
    ofs << "  goto_table({\n";

    vector<int> goto_state_ids;
    for (const auto& [state_id, _] : goto_table) {
        goto_state_ids.push_back(state_id);
    }
    sort(goto_state_ids.begin(), goto_state_ids.end());

    bool first_goto_state = true;
    for (int state_id : goto_state_ids) {
        const auto& gotos = goto_table.at(state_id);

        if (!first_goto_state) ofs << ",\n\n";
        first_goto_state = false;

        ofs << "  \t{" << state_id << ", {\n";

        bool first_goto = true;
        for (const auto& [symbol, target_state] : gotos) {
            if (!first_goto) ofs << ",\n";
            first_goto = false;

            ofs << "  \t\t{{\"" << symbol.GetName() << "\", Symbol::Type::NonTerminal}, "
                << target_state << "}";
        }

        ofs << "\n  \t}}";
    }

    ofs << "\n  }) {}\n";
}
