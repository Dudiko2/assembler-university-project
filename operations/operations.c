#include "operations.h"

#include <string.h>

#include "../utils/utils.h"

/*table of operations used for validation purposes*/
static CodeOperation codeTable[] = {
    {"add", 0, 1},
    {"sub", 0, 2},
    {"and", 0, 3},
    {"or", 0, 4},
    {"nor", 0, 5},
    {"move", 1, 1},
    {"mvhi", 1, 2},
    {"mvlo", 1, 3},
    {"addi", 10},
    {"subi", 11},
    {"andi", 12},
    {"ori", 13},
    {"nori", 14},
    {"bne", 15},
    {"beq", 16},
    {"blt", 17},
    {"bgt", 18},
    {"lb", 19},
    {"sb", 20},
    {"lw", 21},
    {"sw", 22},
    {"lh", 23},
    {"sh", 24},
    {"jmp", 30},
    {"la", 31},
    {"call", 32},
    {"stop", 63},
};

static DataOperation dataTable[] = {
    {".db", {"n+", 0}},
    {".dw", {"n+", 0}},
    {".dh", {"n+", 0}},
    {".asciz", {"s", 0}},
    {".entry", {"l", 0}},
    {".extern", {"l", 0}},
};

int isKeyword(char* str) {
    return isCodeOperation(str) || isDataOperation(str);
}

int isCodeOperation(char* str) {
    int i;
    for (i = 0; i < CODES_NUM; i++) {
        if (strMatch(str, codeTable[i].name))
            return 1;
    }

    return 0;
}

int isDataOperation(char* str) {
    int i;
    for (i = 0; i < DATA_NUM; i++) {
        if (strMatch(str, dataTable[i].name))
            return 1;
    }

    return 0;
}

CodeOperation* getCodeOperation(char* name) {
    int i;
    for (i = 0; i < CODES_NUM; i++) {
        if (strMatch(name, codeTable[i].name))
            return &(codeTable[i]);
    }

    return NULL;
}

char** getArgFormats(char* opname) {
    int i;
    for (i = 0; i < CODES_NUM; i++) {
        if (strMatch(opname, codeTable[i].name))
            return codeTable[i].argFormats;
    }

    for (i = 0; i < DATA_NUM; i++) {
        if (strMatch(opname, dataTable[i].name))
            return dataTable[i].argFormats;
    }

    return NULL;
}