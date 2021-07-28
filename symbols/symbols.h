#ifndef SYMBOLS_H
#define SYMBOLS_H

#include "../utils/utils.h"

typedef struct symbol {
    unsigned int address;
    char* name;
    unsigned int code : 1;
    unsigned int data : 1;
    unsigned int entry : 1;
    unsigned int external : 1;
} Symbol;

Symbol* newSymbol();

#endif