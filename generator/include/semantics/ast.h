#ifndef AST_H
#define AST_H

#include "include/parser/symbol.h"
#include "include/parser/node.h"
#include <cassert>
#include <iostream>
    
using SententialForm = vector<Symbol>;

class Rule {
public:
    Rule(Symbol&& lhs_in, vector<unique_ptr<SententialForm>>&& rhs_in)
    : lhs(std::move(lhs_in)) {
        rhs = std::move(rhs_in);
        assert(!rhs.empty());
    }
    const Symbol& GetLhs() const {
        return lhs;
    }
    const vector<unique_ptr<SententialForm>>& GetRhs() const {
        return rhs;
    }
private:
    Symbol lhs;
    vector<unique_ptr<SententialForm> > rhs;
};

class Program {
public:
    Program(Symbol&& axiom_, vector<Symbol>&& non_terminals_, vector<unique_ptr<Rule>>&& rules_)
    : axiom(std::move(axiom_)), non_terminals(non_terminals_), rules(std::move(rules_)) {
        CheckSemantics();
    }
    const Symbol& GetAxiom() {
        return axiom;
    }

    SententialForm GetNonterminals() {
        return non_terminals;
    }

    const vector<unique_ptr<Rule>>& GetRules() const {
        return rules;
    }
private:
    void CheckSemantics();
    Symbol axiom;
    SententialForm non_terminals;
    vector<unique_ptr<Rule>> rules;
};

class ConverterGrammar {
public:
    shared_ptr<Program> ParseProgram(const InnerNode& program);
    SententialForm ParseDeclaration(const InnerNode& declaration);
    SententialForm ParseDeclaration1(const InnerNode& declaration1);
    Symbol ParseNonterminalDecl(const InnerNode& nonterminal_decl);
    vector<unique_ptr<Rule>> ParseRules(const InnerNode& rules);
    unique_ptr<Rule> ParseRule(const InnerNode& rule);
    vector<unique_ptr<SententialForm>> ParseAlternatives(const InnerNode& alternatives);
    vector<unique_ptr<SententialForm>> ParseAlternatives1(const InnerNode& alternatives1);
    unique_ptr<SententialForm> ParseAlternative(const InnerNode& alternative);
    unique_ptr<SententialForm> ParseTerms(const InnerNode& terms);
    SententialForm ParseTerms1(const InnerNode& terms1);
    Symbol ParseTerm(const InnerNode& term);
private:
    unique_ptr<Symbol> axiom;
};

#endif
