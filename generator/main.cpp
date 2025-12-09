#include <fstream>

#include "include/parser/parser.h"
#include "include/semantics/table_generator.h"

void GenerateCompiler(const string& input_grammar_path, const string& output_tree_path,
                      const string& output_table_path, const string& automaton_path) {

    ifstream file(input_grammar_path);
    string program_text((istreambuf_iterator<char>(file)),
                       (istreambuf_iterator<char>()));
    file.close();

    Compiler compiler;
    Scanner scanner(program_text, &compiler);
    Parser parser = Parser();

    ofstream output_file(output_tree_path);

    unique_ptr<Node> root = parser.Parse(&scanner);
    root->OutputTree(output_file );

    const auto& program_node = dynamic_cast<const InnerNode&>(*root);
    auto converter_grammar = ConverterGrammar{};
    shared_ptr<Program> program = converter_grammar.ParseProgram(program_node);
    FirstFollow sets(program);
    TableGenerator generator(program, sets);

    generator.Generate(output_table_path);
    generator.GenerateAutomaton(automaton_path);
    cout << "compiler created" << endl;
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        cerr << "Usage: " << argv[0] << " <grammar_path> <tree_path> <table_path> <automaton_path>" << endl;
        return 1;
    }

    try {
        string grammar_path = argv[1];
        string tree_path = argv[2];
        string table_path = argv[3];
        string automaton_path = argv[4];

        GenerateCompiler(grammar_path, tree_path, table_path, automaton_path);
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}