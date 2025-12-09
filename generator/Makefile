CC = g++
FLAGS = -std=c++17 -w
INCLUDES = -I.
TARGET = generator

SELF_GRAMMAR = example/self_program.txt
SELF_TREE = output/self_tree.txt
SELF_TABLE = src/parser/table.cpp
SELF_AUTOMATON = output/self_automaton.txt

CALC_GRAMMAR = example/program.txt
CALC_TREE = output/tree.txt
CALC_TABLE = ../calculator/src/parser/table.cpp
CALC_AUTOMATON = output/automaton.txt

OBJS = main.o \
       src/lexer/scanner.o \
       src/lexer/compiler.o \
       src/lexer/position.o \
       src/parser/parser.o \
       src/parser/node.o \
       src/parser/table.o \
       src/semantics/ast.o \
       src/semantics/table_generator.o \
       src/semantics/lr0_automaton.o

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(FLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp
	$(CC) $(FLAGS) $(INCLUDES) -c main.cpp

src/lexer/scanner.o: src/lexer/scanner.cpp
	$(CC) $(FLAGS) $(INCLUDES) -c src/lexer/scanner.cpp -o src/lexer/scanner.o

src/lexer/compiler.o: src/lexer/compiler.cpp
	$(CC) $(FLAGS) $(INCLUDES) -c src/lexer/compiler.cpp -o src/lexer/compiler.o

src/lexer/position.o: src/lexer/position.cpp
	$(CC) $(FLAGS) $(INCLUDES) -c src/lexer/position.cpp -o src/lexer/position.o

src/parser/parser.o: src/parser/parser.cpp
	$(CC) $(FLAGS) $(INCLUDES) -c src/parser/parser.cpp -o src/parser/parser.o

src/parser/node.o: src/parser/node.cpp
	$(CC) $(FLAGS) $(INCLUDES) -c src/parser/node.cpp -o src/parser/node.o

src/parser/table.o: src/parser/table.cpp
	$(CC) $(FLAGS) $(INCLUDES) -c src/parser/table.cpp -o src/parser/table.o

src/semantics/ast.o: src/semantics/ast.cpp
	$(CC) $(FLAGS) $(INCLUDES) -c src/semantics/ast.cpp -o src/semantics/ast.o

src/semantics/table_generator.o: src/semantics/table_generator.cpp
	$(CC) $(FLAGS) $(INCLUDES) -c src/semantics/table_generator.cpp -o src/semantics/table_generator.o

src/semantics/lr0_automaton.o: src/semantics/lr0_automaton.cpp
	$(CC) $(FLAGS) $(INCLUDES) -c src/semantics/lr0_automaton.cpp -o src/semantics/lr0_automaton.o

run: $(TARGET)
	./$(TARGET) $(SELF_GRAMMAR) $(SELF_TREE) $(SELF_TABLE) $(SELF_AUTOMATON)
	./$(TARGET) $(CALC_GRAMMAR) $(CALC_TREE) $(CALC_TABLE) $(CALC_AUTOMATON)

clean:
	rm -f $(OBJS) $(TARGET)
