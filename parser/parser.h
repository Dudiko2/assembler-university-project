#ifndef PARSER_H
#define PARSER_H

#define AS_EXT_STR ".as"

typedef struct command {
    char *label;
    char *op;
    char **arguments;
} command;

/*
    parses the command line arguments and returns the valid filenames in a string array.
    return value should be freed (free()) after use
*/
char **parseCommandLineArgs(int argc, char *argv[]);
/*needs error handling*/
command *genCommand();
void freeCommand(command *cmd);
/*undone*/
int parseCommand(command *parsed, char *cmdStr);
/*
takes CMD_STR and finds looks for a valid label to save to DEST.
At success, returns the length of the label.
If no label was found, returns 0.
If the label found is invalid, returns -1.
*/
int parseLabel(char *dest, char *cmdStr);
/*Removes spaces from the sides of STR and saves the new string into DEST*/
char *trim(char *dest, char *str);

#endif