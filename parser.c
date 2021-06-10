#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

#define AS_EXT_STR ".as"

/* Checks if an argument string has a valid extension and returns 1 (true) or 0 (false) accordingly */
static unsigned int hasValidExtension(char *str);

char **parseCommandLine(int argc, char *argv[]) {
    int i;
    int j;
    char **validArgs;

    if (argc < 2) return NULL;

    validArgs = calloc(argc-1, sizeof(char*));

    for (i=1, j=0; i < argc; i++) {
        char *currArg = argv[i];
        
        if (hasValidExtension(currArg)) {
            validArgs[j] = currArg;
            j++;
        }
    }

    return validArgs;
}

static unsigned int hasValidExtension(char *str) {
    int i;
    int pos = -1; /*position of the dot, initialized as invalid*/

    /*finds the last dot, if exists*/
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.') pos = i;
    }

    return (pos > -1 && strcmp(str+pos, AS_EXT_STR) == 0);
}