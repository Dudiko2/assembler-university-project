#ifndef IO_H
#define IO_H

#define AS_EXT_STR ".as"

typedef enum errorMessage {
    INVALID_FNAME,
    FILE_OPEN_FAIL,
    INVALID_LABEL
} errorMessage;

/*
    parses the command line arguments and returns the valid filenames in a string array.
    return value should be freed (free()) after use
*/
char **getFilenamesFromArgs(int argc, char *argv[]);

void printErrorMessage(errorMessage msgType, char *str);

#endif