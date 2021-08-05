#ifndef PARSER_H
#define PARSER_H

#define LABEL_MAX_LEN 31

#include "../commands/commands.h"
#include "../utils/utils.h"

/*undone*/
Command *parseCommand(char *cmdStr);
int mapListToCmd(Command *cmd, Node **tokenList);
/*undone*/
char *parseLabel(char *str);
char *parseOperation(char *str);
#endif