#ifndef OPERATIONS_H
#define OPERATIONS_H

#define CODES_NUM 27
#define DATA_NUM 6

typedef struct codeOperation {
    char *name;
    int opcode;
    int funct;
} CodeOperation;

typedef struct dataOperation {
    char *name;
} DataOperation;

/*
returns whether STR is a reserved keyword
TODO: add guidance commands
*/
int isKeyword(char *str);
int isCodeOperation(char *str);
int isDataOperation(char *str);
CodeOperation *getCodeOperation(const char *name);

#endif