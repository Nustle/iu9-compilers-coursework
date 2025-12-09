#include "include/parser/parser.h"
#include <sstream>
#include <stack>

void ThrowParseError(const Token& token, const string& message = "") {
    ostringstream err;
    err << token.GetCoords() << ": ";
    if (!message.empty()) {
        err << message;
    } else {
        err << "unexpected token " << ToStringToken(token);
    }
    throw runtime_error(err.str());
}

unique_ptr<Node> Parser::Parse(Scanner *scanner) {
    stack<int> state_stack;
    stack<unique_ptr<Node>> node_stack;

    state_stack.push(0);
    unique_ptr<Token> token = scanner->NextToken();

    while (true) {
        int current_state = state_stack.top();
        Symbol current_symbol{ToStringTag(token->GetTag()), Symbol::Type::Terminal};

        auto action_opt = table.GetAction(current_state, current_symbol);
        if (!action_opt) {
            ThrowParseError(*token);
        }

        const Action& action = *action_opt;

        if (holds_alternative<Shift>(action)) {
            int next_state = get<Shift>(action).state;
            state_stack.push(next_state);
            node_stack.push(make_unique<LeafNode>(std::move(token)));
            token = scanner->NextToken();
        } else if (holds_alternative<Reduce>(action)) {
            const auto& reduction = get<Reduce>(action);

            auto reduced_node = make_unique<InnerNode>(reduction.lhs.GetName());
            vector<unique_ptr<Node>> children;

            for (size_t i = 0; i < reduction.rhs.size(); ++i) {
                children.push_back(std::move(node_stack.top()));
                node_stack.pop();
                state_stack.pop();
            }

            reverse(children.begin(), children.end());
            for (auto& child : children) {
                reduced_node->AddChild(std::move(child));
            }

            int prev_state = state_stack.top();
            auto goto_state_opt = table.GetGoto(prev_state, reduction.lhs);

            if (!goto_state_opt) {
                ThrowParseError(*token, "Goto table error for NonTerminal " + reduction.lhs.GetName());
            }

            state_stack.push(*goto_state_opt);
            node_stack.push(std::move(reduced_node));
        } else if (holds_alternative<Accept>(action)) {
            if (node_stack.size() != 1) {
                ThrowParseError(*token, "Accept error");
            }
            return std::move(node_stack.top());
        }
    }
}
