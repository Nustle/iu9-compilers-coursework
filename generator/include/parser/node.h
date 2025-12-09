#ifndef NODE_H
#define NODE_H

#include <vector>
#include "include/lexer/token.h"

class Node {
public:
    virtual ~Node() = default;
    virtual void OutputTree(ostream& os) = 0;
};

class InnerNode : public Node {
public:
    explicit InnerNode(const string &non_terminal)
    : non_terminal(non_terminal) {}

    vector<unique_ptr<Node>>& GetChildren() {
        return children;
    }

    const vector<unique_ptr<Node>>& GetChildren() const {
        return children;
    }

    const string &GetNonTerminal() const {
        return non_terminal;
    }

    Node& AddChild(unique_ptr<Node> &&node) {
        children.push_back(std::move(node));
        return *children.back();
    }
    void OutputTree(ostream& os) override;
private:
    string non_terminal;
    vector<unique_ptr<Node>> children;
};

class LeafNode : public Node {
public:
    explicit LeafNode(unique_ptr<Token> &&token)
    : token(std::move(token)) {}

    unique_ptr<Token>& GetToken() {
        return token;
    }

    void OutputTree(ostream& os) override {}
private:
    unique_ptr<Token> token;
};

#endif

