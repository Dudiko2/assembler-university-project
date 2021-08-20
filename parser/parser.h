#ifndef PARSER_H
#define PARSER_H

/*initial amount of args to be allocated to argument list*/
#define ARGS_LEN 3

#include "../commands/commands.h"
#include "../globals.h"
#include "../utils/utils.h"

/*
parses the command in cmdStr.
should be free()'d using freeCommand
*/
Command *parseCommand(char *cmdStr);

/*
parses the label in str.
return value should be free()'d after use
*/
char *parseLabel(char *str);

/*
parses the operation in str.
return value should be free()'d after use
*/
char *parseOperation(char *str);

/*
parses the args in a linked list of tokens.
return value should be free()'d after use
*/
char **parseArgumentList(Node *token);

#endif