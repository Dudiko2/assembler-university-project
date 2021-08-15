#include "operations.h"

#include <string.h>

#include "../utils/utils.h"

/*table of operations used for validation purposes*/
static CodeOperation codeTable[] = {
    {"add", 0, 1, {"rrr"}},
    {"sub", 0, 2, {"rrr"}},
    {"and", 0, 3, {"rrr"}},
    {"or", 0, 4, {"rrr"}},
    {"nor", 0, 5, {"rrr"}},
    {"move", 1, 1, {"rr"}},
    {"mvhi", 1, 2, {"rr"}},
    {"mvlo", 1, 3, {"rr"}},
    {"addi", 10, 0, {"rnr"}},
    {"subi", 11, 0, {"rnr"}},
    {"andi", 12, 0, {"rnr"}},
    {"ori", 13, 0, {"rnr"}},
    {"nori", 14, 0, {"rnr"}},
    {"bne", 15, 0, {"rrl"}},
    {"beq", 16, 0, {"rrl"}},
    {"blt", 17, 0, {"rrl"}},
    {"bgt", 18, 0, {"rrl"}},
    {"lb", 19, 0, {"rnr"}},
    {"sb", 20, 0, {"rnr"}},
    {"lw", 21, 0, {"rnr"}},
    {"sw", 22, 0, {"rnr"}},
    {"lh", 23, 0, {"rnr"}},
    {"sh", 24, 0, {"rnr"}},
    {"jmp", 30, 0, {"l", "r"}},
    {"la", 31, 0, {"l"}},
    {"call", 32, 0, {"l"}},
    {"stop", 63, 0, {""}},
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