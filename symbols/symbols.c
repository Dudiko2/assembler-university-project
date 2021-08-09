#include "symbols.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../commands/commands.h"
#include "../operations/operations.h"

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
    Symbol* sym = newSymbol();

    sym->name = newStringCopy(cmd->label);
    sym->code = isCodeOperation(cmd->op);
    sym->data = isDataOperation(cmd->op);

    return sym;
}

void freeSymbol(Symbol* sym) {
    if (sym == NULL)
        return;

    free(sym->name);
    free(sym);
}
