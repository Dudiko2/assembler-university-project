#include "symbols.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../io/io.h"
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

    if (symbolExists(*headSymbolRef, sym)) {
        printErrorMessage(SYMBOL_EXISTS, sym->name);

        return 0;
    }

    insertInfront(headSymbolRef, sym);
    return 1;
}

int symbolExists(Node* headSymbol, Symbol* sym) {
    Node* symNode;
    Symbol* temp;

    symNode = headSymbol;

    while (symNode) {
        temp = symNode->data;
        if (strMatch(temp->name, sym->name)) {
            return 1;
        }

        symNode = symNode->next;
    }

    return 0;
}

void updateDataAdresses(Node* symHead, int ICF) {
    Symbol* sym;
    while (symHead) {
        sym = symHead->data;
        if (sym->data) {
            sym->address += ICF;
        }

        symHead = symHead->next;
    }
}

Symbol* getSymbol(Node* symHead, char* name) {
    Symbol* sym;

    while (symHead) {
        sym = symHead->data;
        if (strMatch(sym->name, name)) {
            return sym;
        }

        symHead = symHead->next;
    }

    return NULL;
}

int storeExtern(Node** headSymbolRef, char* label) {
    Symbol* sym;
    Symbol* alreadyDefined = NULL;

    /*ignore if extern symbol exists, error if not extern*/
    alreadyDefined = getSymbol(*headSymbolRef, label);
    if (alreadyDefined) {
        if (alreadyDefined->data || alreadyDefined->code || !(alreadyDefined->external)) {
            printErrorMessage(NO_EXTERN_SYMBOL_EXISTS, label);
            return 0;
        }

        return 1;
    }

    sym = newSymbol();
    if (!sym)
        return 0;

    sym->name = newStringCopy(label);
    sym->external = 1;
    sym->address = 0;

    insertInfront(headSymbolRef, sym);
    return 1;
}
