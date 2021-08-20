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

/*each ExternCall represents a single use of an external label (.extern) in the input source code*/
typedef struct ExternCall {
    char* symName;
    unsigned int address;
} ExternCall;

/*
creates a new symbol.
should be freed using freeSymbol
*/
Symbol* newSymbol();

/*
creates a new symbol from a Command.
should be freed using freeSymbol
*/
Symbol* symbolFromCommand(Command* cmd);

void freeSymbol(void* ptr);

/*
frees a linked list of Symbols
*/
void freeSymbolList(Node* head);

/*
Stores SYM in a list of symbols.
returns whether or not the process was successful
*/
int storeSymbol(Node** headSymbolRef, Symbol* sym, int address);

/*
returns whether or not SYM exists in a list.
*/
int symbolExists(Node* headSymbol, Symbol* sym);

/*
increases all symbols (that are marked with data) in list by ICF
*/
void updateDataAdresses(Node* symHead, int ICF);

/*
gets a symbol named NAME from a symbol list
*/
Symbol* getSymbol(Node* symHead, char* name);

int storeExtern(Node** headSymbolRef, char* label);

int setEntry(Node* headSymbol, char* label);

int storeExternCall(Node** externalCalls, char* name, unsigned int address);

void freeExternCall(void* ptr);

void freeExternCallsList(Node* head);

#endif