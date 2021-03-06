#ifndef OPERATIONS_H
#define OPERATIONS_H

#define CODES_NUM 27
#define DATA_NUM 6
#define FORMATS_NUM 5

/*
meaning of chars in formats:
- n = number / integer (e.g. 1, -67...)
- r = register (e.g. $6)
- l = label (e.g. MAIN)
- s = string (e.g. "hello")
- + = infinite amout of arg (e.g. "n+")
*/

typedef struct codeOperation {
    char *name;
    int opcode;
    int funct;
    char *argFormats[FORMATS_NUM];
} CodeOperation;

typedef struct dataOperation {
    char *name;
    char *argFormats[FORMATS_NUM];
} DataOperation;

/*
returns whether STR is a reserved keyword
*/
int isKeyword(char *str);

int isCodeOperation(char *str);

int isDataOperation(char *str);

/*
gets the code operation named NAME, if exists
*/
CodeOperation *getCodeOperation(char *name);

/*
gets the argument formats for OPNAME, if it's valid
*/
char **getArgFormats(char *opname);

#endif