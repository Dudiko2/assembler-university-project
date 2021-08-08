#include "commands.h"

#include <stdio.h>
#include <stdlib.h>

#include "../utils/utils.h"

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
    freeStringArray(cmd->arguments);
    free(cmd);
}

void printCommand(Command *cmd) {
    if (cmd == NULL)
        return;

    if (cmd->label != NULL)
        printf("label: %s\n", cmd->label);

    if (cmd->op != NULL)
        printf("operation: %s\n", cmd->op);

    if (cmd->arguments != NULL) {
        int i = 0;
        printf("args: ");
        while ((cmd->arguments)[i] != NULL) {
            printf("%s ", (cmd->arguments)[i]);

            i++;
        }
        printf("\n");
    }
}