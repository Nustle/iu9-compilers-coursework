CC = g++
FLAGS = -std=c++17 -w
INCLUDES = -I.
TARGET = calculator

INPUT_PATH = example/program.txt
TREE_PATH = output/tree.txt

OBJS = main.o \
       src/lexer/compiler.o \
       src/lexer/position.o \
       src/lexer/scanner.o \
       src/parser/table.o \
       src/parser/node.o \
       src/parser/parser.o \
       src/semantics/interpret.o

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(FLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp
	$(CC) $(FLAGS) $(INCLUDES) -c main.cpp

src/lexer/compiler.o: src/lexer/compiler.cpp
	$(CC) $(FLAGS) $(INCLUDES) -c src/lexer/compiler.cpp -o src/lexer/compiler.o

src/lexer/position.o: src/lexer/position.cpp
	$(CC) $(FLAGS) $(INCLUDES) -c src/lexer/position.cpp -o src/lexer/position.o

src/lexer/scanner.o: src/lexer/scanner.cpp
	$(CC) $(FLAGS) $(INCLUDES) -c src/lexer/scanner.cpp -o src/lexer/scanner.o

src/parser/table.o: src/parser/table.cpp
	$(CC) $(FLAGS) $(INCLUDES) -c src/parser/table.cpp -o src/parser/table.o

src/parser/node.o: src/parser/node.cpp
	$(CC) $(FLAGS) $(INCLUDES) -c src/parser/node.cpp -o src/parser/node.o

src/parser/parser.o: src/parser/parser.cpp
	$(CC) $(FLAGS) $(INCLUDES) -c src/parser/parser.cpp -o src/parser/parser.o

src/semantics/interpret.o: src/semantics/interpret.cpp
	$(CC) $(FLAGS) $(INCLUDES) -c src/semantics/interpret.cpp -o src/semantics/interpret.o

run: $(TARGET)
	./$(TARGET) $(INPUT_PATH) $(TREE_PATH)

clean:
	rm -f $(OBJS) $(TARGET)
