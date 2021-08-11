#ifndef COMMANDS_H
#define COMMANDS_H

#include "../utils/utils.h"

/*a structure that represents a parsed command string*/
typedef struct command {
    char *label;
    char *op;
    char **arguments;
} Command;

/*generates a new command structure and returns a pointer to it, or NULL if allocation fails*/
Command *newCommand();
/*frees the memory that was allocated for CMD by newCommand*/
void freeCommand(Command *cmd);

void printCommand(Command *cmd);

void freeCommandList(Node *head);

#endif