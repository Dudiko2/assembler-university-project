#ifndef IO_H
#define IO_H

#include <stdio.h>

#include "../utils/utils.h"

#define AS_EXT_STR ".as"

typedef enum errorCode {
    INVALID_FNAME,
    FILE_OPEN_FAIL,
    INVALID_LABEL,
    INVALID_LABEL_CHARS,
    LONG_LABEL,
    INVALID_OPERATION,
    INVALID_ARG,
    TOO_MANY_ARGS,
    MISSING_ARGS,
    COMMA_START,
    COMMA_END,
    SYMBOL_EXISTS,
    SYMBOL_DOES_NOT_EXIST,
    NO_EXTERN_SYMBOL_EXISTS,
    NUM_EXCEEDS_BIN,
    INVALID_ENTRY_NO_SYMBOL,
    INVALID_ENTRY_SYMBOL_EXTERN
} errorCode;

/*
    parses the command line arguments and returns the valid filenames in a string array.
    return value should be freed (free()) after use
*/
char **getFilenamesFromArgs(int argc, char *argv[]);

/*
prints a error message into stderr.
takes str as additional information (information type varies from one errorCode to another).
notifies the module to not create output files for the current source file
*/
void printErrorMessage(errorCode msgType, char *str);

/*reads a file*/
FILE *readFile(char *name);

/*reads next line, keeps track of line number*/
char *readNextLine(char *line);

/*closes the currently open (by readFile) source file*/
void closeSourceFile();

/*gets the name of a file minus the path and the extension*/
char *getBasename(char *name);

/*creates .ob file*/
int genObjectFile(char *basename, Node *codeImageHead, Node *dataImageHead, int ICF, int DCF);

/*creates .ent file*/
int genEntriesFile(char *basename, Node *symbolsHead);

/*creates .ext file*/
int genExternalsFile(char *basename, Node *externCallsHead);

/*returns whether or not to create output files for the currently open (by readFile) source file */
int shouldGenerateFiles();

#endif