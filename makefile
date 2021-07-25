CC = gcc
FLAGS = -Wall -ansi -pedantic -g
OBJECTS = main.o parser/parser.o io/io.o operations/operations.o commands/commands.o utils/utils.o
HEADERS = parser/parser.h io/io.h operations/operations.h commands/commands.h utils/utils.h
TARGET = assembler

$(TARGET): $(OBJECTS) $(HEADERS)
	$(CC) $(FLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f */*.o
