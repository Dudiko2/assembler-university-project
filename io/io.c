#include "io.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../encoder/encoder.h"
#include "../globals.h"

static unsigned long int lineNum = 0;
static FILE *pf = NULL;
static int genFiles = 1;
/* Checks if an argument string has a valid extension and returns 1 (true) or 0 (false) accordingly */
static unsigned int hasValidExtension(char *str);

char **getFilenamesFromArgs(int argc, char *argv[]) {
    int i;
    int j;
    char **validArgs;

    if (argc < 2) return NULL;
    validArgs = calloc(argc, sizeof(char *));

    for (i = 1, j = 0; i < argc; i++) {
        char *currArg = argv[i];

        if (hasValidExtension(currArg)) {
            validArgs[j] = currArg;
            j++;
        } else {
            printErrorMessage(INVALID_FNAME, currArg);
        }
    }

    return validArgs;
}

void printErrorMessage(errorCode msgType, char *str) {
    int showLineNum = 0;
    char errMsg[100];

    strcpy(errMsg, "Unknown error: '%s'");
    genFiles = 0;

    switch (msgType) {
        case INVALID_FNAME:
            strcpy(errMsg, "Invalid file name '%s'");
            break;

        case FILE_OPEN_FAIL:
            strcpy(errMsg, "Error opening file '%s'");
            break;

        case INVALID_LABEL:
            strcpy(errMsg, "Invalid label name '%s'");
            showLineNum = 1;
            break;

        case INVALID_LABEL_CHARS:
            strcpy(errMsg, "Invalid characters in label '%s'");
            showLineNum = 1;
            break;

        case LONG_LABEL:
            strcpy(errMsg, "Label too long. Maximum size is 30");
            showLineNum = 1;
            break;

        case INVALID_OPERATION:
            strcpy(errMsg, "Invalid operation '%s'");
            showLineNum = 1;
            break;

        case INVALID_ARG:
            strcpy(errMsg, "Invalid argument at '%s'");
            showLineNum = 1;
            break;

        case TOO_MANY_ARGS:
            strcpy(errMsg, "Too many arguments");
            showLineNum = 1;
            break;

        case MISSING_ARGS:
            strcpy(errMsg, "Missing argument(s)");
            showLineNum = 1;
            break;

        case COMMA_START:
            strcpy(errMsg, "Unnecessary comma infront of arguments");
            showLineNum = 1;
            break;

        case COMMA_END:
            strcpy(errMsg, "Unnecessary comma at end of arguments");
            showLineNum = 1;
            break;

        case SYMBOL_EXISTS:
            strcpy(errMsg, "Symbol '%s' is already defined");
            showLineNum = 1;
            break;

        case SYMBOL_DOES_NOT_EXIST:
            strcpy(errMsg, "Undefined symbol %s");
            break;

        case NO_EXTERN_SYMBOL_EXISTS:
            strcpy(errMsg, "Invalid use of '.extern'. Symbol '%s' already defined as a non-external symbol");
            showLineNum = 1;
            break;

        case NUM_EXCEEDS_BIN:
            strcpy(errMsg, "Value too large to be stored in %s bit binary number");
            break;

        case INVALID_ENTRY_NO_SYMBOL:
            strcpy(errMsg, "Invalid use of '.entry'. Symbol '%s' is undefined");
            break;

        case INVALID_ENTRY_SYMBOL_EXTERN:
            strcpy(errMsg, "Invalid use of '.entry'. Symbol '%s' is external");
            break;

        default:
            break;
    }

    if (showLineNum)
        fprintf(stderr, "LINE %lu: ", lineNum);

    fprintf(stderr, errMsg, str);
    fprintf(stderr, "\n----\n");
}

FILE *readFile(char *name) {
    FILE *srcFile = fopen(name, "r");
    if (!srcFile) {
        printErrorMessage(FILE_OPEN_FAIL, name);
        return NULL;
    }

    pf = srcFile;
    lineNum = 0;
    genFiles = 1;

    return srcFile;
}

char *readNextLine(char *line) {
    char *ptr = fgets(line, MAX_COMMAND_LEN, pf);
    lineNum++;

    return ptr;
}

void closeFile() {
    fclose(pf);
    lineNum = 0;
}

static unsigned int hasValidExtension(char *str) {
    int i;
    int pos = -1; /*position of the dot, initialized as invalid*/

    /*finds the last dot, if exists*/
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.') pos = i;
    }

    return (pos > -1 && strMatch(str + pos, AS_EXT_STR));
}

char *getBasename(char *name) {
    char *copy = newStringCopy(name);
    char *basename = calloc(strlen(name) + 1, sizeof(char));
    int right = strlen(copy) - 1;
    int left;

    for (; right; right--) {
        if (copy[right] == '.') {
            copy[right] = '\0';
            break;
        }
    }

    for (left = right; left; left--) {
        if (copy[left] == '/') {
            left = left + 1;
            break;
        }
    }

    free(copy);
    strncpy(basename, name + left, right - left);

    return basename;
}