#include "operations.h"

#include <string.h>

#include "../utils/utils.h"

/*table of operations used for validation purposes*/
static CodeOperation codeTable[] = {
    {"add", 0, 1, {"rrr", 0}},
    {"sub", 0, 2, {"rrr", 0}},
    {"and", 0, 3, {"rrr", 0}},
    {"or", 0, 4, {"rrr", 0}},
    {"nor", 0, 5, {"rrr", 0}},
    {"move", 1, 1, {"rr", 0}},
    {"mvhi", 1, 2, {"rr", 0}},
    {"mvlo", 1, 3, {"rr", 0}},
    {"addi", 10, 0, {"rnr", 0}},
    {"subi", 11, 0, {"rnr", 0}},
    {"andi", 12, 0, {"rnr", 0}},
    {"ori", 13, 0, {"rnr", 0}},
    {"nori", 14, 0, {"rnr", 0}},
    {"bne", 15, 0, {"rrl", 0}},
    {"beq", 16, 0, {"rrl", 0}},
    {"blt", 17, 0, {"rrl", 0}},
    {"bgt", 18, 0, {"rrl", 0}},
    {"lb", 19, 0, {"rnr", 0}},
    {"sb", 20, 0, {"rnr", 0}},
    {"lw", 21, 0, {"rnr", 0}},
    {"sw", 22, 0, {"rnr", 0}},
    {"lh", 23, 0, {"rnr", 0}},
    {"sh", 24, 0, {"rnr", 0}},
    {"jmp", 30, 0, {"l", "r", 0}},
    {"la", 31, 0, {"l", 0}},
    {"call", 32, 0, {"l", 0}},
    {"stop", 63, 0, {"", 0}},
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