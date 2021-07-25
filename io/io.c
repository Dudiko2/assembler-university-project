#include "io.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void printErrorMessage(errorMessage msgType, char *str) {
    char *errMsg = calloc(100, sizeof(char));
    strcpy(errMsg, "Unknown error: %s\n");

    switch (msgType) {
        case INVALID_FNAME:
            strcpy(errMsg, "Invalid file name: %s\n");
            break;

        case FILE_OPEN_FAIL:
            strcpy(errMsg, "Error opening file: %s\n");
            break;
        case INVALID_LABEL:
            strcpy(errMsg, "Invalid label at %s\n");
        default:
            break;
    }

    /*fprintf(stderr, errMsg, str);*/
    printf(errMsg, str);
    free(errMsg);
}

static unsigned int hasValidExtension(char *str) {
    int i;
    int pos = -1; /*position of the dot, initialized as invalid*/

    /*finds the last dot, if exists*/
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.') pos = i;
    }

    return (pos > -1 && strcmp(str + pos, AS_EXT_STR) == 0);
}
