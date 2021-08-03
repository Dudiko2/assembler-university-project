#ifndef OPERATIONS_H
#define OPERATIONS_H

#define CODES_NUM 27
#define DATA_NUM 6

typedef struct codeOperation {
    char *name;
    int opcode;
    int funct;
    char **argFormats;
} CodeOperation;

typedef struct dataOperation {
    char *name;
    char **argFormats;
} DataOperation;

/*
returns whether STR is a reserved keyword
TODO: add guidance commands
*/
int isKeyword(char *str);
int isCodeOperation(char *str);
int isDataOperation(char *str);

#endif