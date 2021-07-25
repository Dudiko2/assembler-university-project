#include "commands.h"

#include <stdlib.h>

Command *newCommand() {
    Command *cmd = malloc(sizeof(Command));
    if (cmd == NULL) return NULL;

    cmd->label = calloc(80, sizeof(char));
    cmd->op = calloc(80, sizeof(char));
    cmd->arguments = calloc(10, sizeof(char *));

    if (cmd->label == NULL || cmd->op == NULL || cmd->arguments == NULL) {
        freeCommand(cmd);
        return NULL;
    }

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