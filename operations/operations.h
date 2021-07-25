#ifndef OPERATIONS_H
#define OPERATIONS_H

typedef struct operation {
    char *name;
    int opcode;
    int funct;
} Operation;

/*
returns whether STR is a reserved keyword
TODO: add guidance commands
*/
int isKeyword(char *str);

#endif