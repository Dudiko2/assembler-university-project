#include "symbols.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../operations/operations.h"
#include "../utils/utils.h"

Symbol* newSymbol() {
    Symbol* sym = malloc(sizeof(Symbol));
    if (sym == NULL)
        return NULL;

    sym->address = 0;
    sym->name = NULL;
    sym->code = 0;
    sym->data = 0;
    sym->entry = 0;
    sym->external = 0;

    return sym;
}

Symbol* symbolFromCommand(Command* cmd) {
    Symbol* sym;

    if (cmd == NULL || isEmptyStr(cmd->label)) {
        return NULL;
    }

    sym = newSymbol();

    sym->name = newStringCopy(cmd->label);
    sym->code = isCodeOperation(cmd->op);
    sym->data = isDataOperation(cmd->op);

    return sym;
}

void freeSymbol(void* ptr) {
    Symbol* sym = ptr;

    if (sym == NULL)
        return;

    free(sym->name);
    free(sym);
}

void freeSymbolList(Node* head) {
    freeListWithFunc(head, freeSymbol);
}

int storeSymbol(Node** headSymbolRef, Symbol* sym, int address) {
    if (!sym)
        return 0;

    sym->address = address;

    if (headSymbolRef == NULL) {
        insertLast(headSymbolRef, sym);
        return 1;
    }

    if (symbolExists(headSymbolRef, sym)) {
        printf("%s already exists\n", sym->name);
        /*msg*/

        return 0;
    }

    insertInfront(headSymbolRef, sym);
    return 1;
}

int symbolExists(Node** headSymbolRef, Symbol* sym) {
    Node* symNode;
    Symbol* temp;

    symNode = *headSymbolRef;

    while (symNode != NULL) {
        temp = symNode->data;
        if (strcmp(temp->name, sym->name) == 0) {
            return 1;
        }

        symNode = symNode->next;
    }

    return 0;
}