#include "commands.h"

#include <stdlib.h>

Command *newCommand() {
    Command *cmd = malloc(sizeof(Command));
    if (cmd == NULL) return NULL;

    cmd->label = NULL;
    cmd->op = NULL;
    cmd->arguments = NULL;

    return cmd;
}

void freeCommand(Command *cmd) {
    if (cmd == NULL)
        return;

    free(cmd->label);
    free(cmd->op);
    free(cmd->arguments);
    free(cmd);
}