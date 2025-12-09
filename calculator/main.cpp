#include <fstream>
#include "include/parser/parser.h"
#include "include/semantics/interpret.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_path> <tree_path>" << endl;
        return 1;
    }

    string input_path = argv[1];
    string tree_path = argv[2];

    ifstream file(input_path);
    string program_text((istreambuf_iterator<char>(file)),
                        (istreambuf_iterator<char>()));
    file.close();

    Compiler compiler;
    Scanner scanner(program_text, &compiler);
    Parser parser = Parser();

    ofstream output_file(tree_path);

    try {
        unique_ptr<Node> root = parser.Parse(&scanner);
        root->OutputTree(output_file);

        const auto& program_node = dynamic_cast<const InnerNode&>(*root);
        Interpreter interpreter{};
        int ans = interpreter.Interpret(program_node);
        cout << ans << endl;
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}