CC = gcc
FLAGS = -Wall -ansi -pedantic -g
MAIN_OBJ = main.o
TESTER_OBJ = tester.o
OBJECTS = parser/parser.o io/io.o operations/operations.o commands/commands.o utils/utils.o symbols/symbols.o encoder/encoder.o
HEADERS = parser/parser.h io/io.h operations/operations.h commands/commands.h utils/utils.h symbols/symbols.h encoder/encoder.h
TARGET = assembler

$(TARGET): $(MAIN_OBJ) $(OBJECTS) $(HEADERS)
	$(CC) $(FLAGS) $(MAIN_OBJ) $(OBJECTS) -o $(TARGET)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f */*.o
	rm -f tester

tester: $(TESTER_OBJ) $(OBJECTS) $(HEADERS)
	$(CC) $(FLAGS) $(TESTER_OBJ) $(OBJECTS) -o $@

leaks: clean $(ARGS)
	valgrind --leak-check=yes ./$(ARGS) inputfiles/ps.as