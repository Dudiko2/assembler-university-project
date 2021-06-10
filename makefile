CC = gcc
FLAGS = -Wall -ansi -pedantic
OBJECTS = main.o parser.o
HEADERS = parser.h

assembler: $(OBJECTS) $(HEADERS)
	$(CC) $(FLAGS) $(OBJECTS) -o assembler

%.o: %.c
	$(CC) $(FLAGS) -c $<

clean:
	rm -f *.o