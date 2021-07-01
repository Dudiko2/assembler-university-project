CC = gcc
FLAGS = -Wall -ansi -pedantic -g
OBJECTS = main.o parser/parser.o errors/errors.o
HEADERS = parser/parser.h errors/errors.h
TARGET = assembler

$(TARGET): $(OBJECTS) $(HEADERS)
	$(CC) $(FLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f */*.o
