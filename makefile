CC = gcc
FLAGS = -Wall -ansi -pedantic
OBJECTS = main.o

assembler: $(OBJECTS)
	$(CC) $(FLAGS) $< -o assembler

%.o: %.c
	$(CC) $(FLAGS) -c $<