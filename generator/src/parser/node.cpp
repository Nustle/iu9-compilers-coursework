#include "include/parser/node.h"
#include <queue>
#include <iostream>

void InnerNode::OutputTree(ostream& os) {
    os << "digraph {\n";
    queue<Node*> q;
    unordered_map<const Node*, string> id;
    int n = 0;
    q.push(this);
    id[this] = "n" + to_string(n++);
    os << "  " << id[this] << " [label=\"" << GetNonTerminal() << "\"]\n";
    while (!q.empty()) {
        Node* cur = q.front();
        q.pop();
        if (auto* in = dynamic_cast<InnerNode*>(cur)) {
            vector<string> same;
            for (auto& up : in->GetChildren()) {
                Node* child = up.get();
                string cid = "n" + to_string(n++);
                id[child] = cid;
                if (auto* cIn = dynamic_cast<InnerNode*>(child)) {
                    os << "  " << cid << " [label=\"" << cIn->GetNonTerminal() << "\"]\n";
                } else {
                    auto* lf = dynamic_cast<LeafNode*>(child);
                    os << "  " << cid << " [shape=box,label=\"" << *lf->GetToken() << "\"]\n";
                }
                os << "  " << id[cur] << " -> " << cid << "\n";
                same.push_back(cid);
                q.push(child);
            }
            if (same.size() > 1) {
                os << "  { rank=same; ";
                for (size_t i = 0; i < same.size(); ++i) {
                    os << same[i];
                    if (i + 1 < same.size()) os << " -> ";
                }
                os << " [style=invis]; }\n";
            }
        }
    }
    os << "}\n";
}
