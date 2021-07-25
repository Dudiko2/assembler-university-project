#include "operations.h"

#include <string.h>
/*table of operations used for validation purposes*/
static Operation table[] = {
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

int isKeyword(char* str) {
    int i;
    for (i = 0; i < 27; i++) {
        if (strcmp(str, table[i].name) == 0)
            return 1;
    }

    return 0;
}
