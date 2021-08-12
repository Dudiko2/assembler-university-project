#ifndef PARSER_H
#define PARSER_H

/*initial amount of args to be allocated to argument list*/
#define ARGS_LEN 3

#include "../commands/commands.h"
#include "../globals.h"
#include "../utils/utils.h"

/*undone*/
Command *parseCommand(char *cmdStr);

int mapTokenListToCmd(Command *cmd, Node *headToken);

/*undone*/
char *parseLabel(char *str);

char *parseOperation(char *str);

char **parseArgumentList(Node *token);

#endif