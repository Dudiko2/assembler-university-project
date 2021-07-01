#include "parser.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../errors/errors.h"

/* Checks if an argument string has a valid extension and returns 1 (true) or 0 (false) accordingly */
static unsigned int hasValidExtension(char *str);

char **parseCommandLineArgs(int argc, char *argv[]) {
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

static unsigned int hasValidExtension(char *str) {
    int i;
    int pos = -1; /*position of the dot, initialized as invalid*/

    /*finds the last dot, if exists*/
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.') pos = i;
    }

    return (pos > -1 && strcmp(str + pos, AS_EXT_STR) == 0);
}

/*parseCommand*/
/* - parseLabel*/
/* - parseOperator*/
/* - parseOperands*/

command *genCommand() {
    command *cmd = malloc(sizeof(command));
    cmd->label = calloc(80, sizeof(char));
    cmd->op = calloc(80, sizeof(char));
    cmd->arguments = calloc(10, sizeof(char *));

    return cmd;
}

void freeCommand(command *cmd) {
    free(cmd->label);
    free(cmd->op);
    free(cmd->arguments);
    free(cmd);
}

int parseCommand(command *parsed, char *cmdStr) {
    int statusCode;
    char *newStr;
    newStr = calloc(strlen(cmdStr), sizeof(char));

    /*
    should move to a (yet to be written) parseLine
    that parses every line of the source code, not just cmd's
    */
    trim(newStr, cmdStr);

    statusCode = parseLabel(parsed->label, newStr);
    if (statusCode < 0) {
        printErrorMessage(INVALID_LABEL, newStr);
        return statusCode;
    }

    free(newStr);

    return 1;
}

int parseLabel(char *dest, char *cmdStr) {
    /*UNDONE*/

    int i;
    int j;
    int maxLen;
    char c;

    maxLen = strlen(cmdStr);

    for (i = 0; (c = cmdStr[i]); i++) {
        if (c == ':') {
            if (i == 0)
                return -1;
            else
                break;
        }
    }

    if (i > 0 && i < maxLen) {
        for (j = 0; j < i; j++) {
            /*assuming cmdStr was trimmed before this function was called*/
            if (isspace(cmdStr[j]))
                return -1;
        }
        /*make sure here the label is not a reserved keyword*/
        strncpy(dest, cmdStr, i);
        return i;
    }

    return 0;
}

char *trim(char *dest, char *str) {
    int len = strlen(str);
    int left;
    int right;

    for (left = 0; isspace(str[left]); left++)
        ;
    for (right = len; isspace(str[right]); right--)
        ;

    if (left >= right)
        return NULL;

    return strncpy(dest, str + left, right - left - 1);
}