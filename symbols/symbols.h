#ifndef SYMBOLS_H
#define SYMBOLS_H

#include "../commands/commands.h"
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
Symbol* symbolFromCommand(Command* cmd);
void freeSymbol(void* ptr);
void freeSymbolList(Node* head);
int storeSymbol(Node** headSymbolRef, Symbol* sym, int address);
int symbolExists(Node** headSymbolRef, Symbol* sym);

#endif