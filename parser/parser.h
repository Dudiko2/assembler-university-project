#include "../commands/commands.h"

#ifndef PARSER_H
#define PARSER_H

#define LABEL_MAX_LEN 31

/*undone*/
Command *parseCommand(char *cmdStr);
/*undone*/
char *parseLabel(char *cmdStr);

#endif