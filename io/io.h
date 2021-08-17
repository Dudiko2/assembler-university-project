#ifndef IO_H
#define IO_H

#include <stdio.h>

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
    NUM_EXCEEDS_BIN
} errorCode;

/*
    parses the command line arguments and returns the valid filenames in a string array.
    return value should be freed (free()) after use
*/
char **getFilenamesFromArgs(int argc, char *argv[]);

void printErrorMessage(errorCode msgType, char *str);

FILE *readFile(char *name);

char *readNextLine(char *line);

void closeFile();

#endif