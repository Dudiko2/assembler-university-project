#include "symbols.h"

#include <stdio.h>
#include <stdlib.h>

Symbol* newSymbol() {
    Symbol* sym = malloc(sizeof(Symbol));
    if (sym == NULL)
        return NULL;

    return sym;
}

void freeSymbol(Symbol* sym) {
    if (sym == NULL)
        return;

    free(sym->name);
    free(sym);
}
