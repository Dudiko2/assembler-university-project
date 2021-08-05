#include "parser.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../io/io.h"
#include "../operations/operations.h"
#include "../utils/utils.h"

/*returns whether the characters in LABEL are allowed*/
static int validLabelChars(char *label, int len);
static int isComment(char *str);

Command *parseCommand(char *cmdStr) {
    char error = 0;
    char *trimmed;
    Command *cmd = newCommand();

    trimmed = trim(cmdStr);

    /*nothing to parse */
    if (isComment(trimmed) || isEmptyStr(trimmed)) {
        free(trimmed);
        freeCommand(cmd);
        return NULL;
    }

    cmd->label = parseLabel(trimmed);

    if (cmd->label == NULL) {
        printErrorMessage(INVALID_LABEL, trimmed);
        error = 1;
    }

    free(trimmed);

    if (error) {
        freeCommand(cmd);
        return NULL;
    }

    return cmd;
}

char *parseLabel(char *cmdStr) {
    /*for looping and storing the length of the label*/
    int i;
    /*length of cmdStr*/
    int len;
    int error = 0;
    /*aux variable for chars*/
    char c;
    /*store label, if exists, here*/
    char *label = calloc(LABEL_MAX_LEN, sizeof(char));

    len = strlen(cmdStr);

    for (i = 0; (c = cmdStr[i]); i++) {
        if (c == ':') {
            if (i == 0) {
                /*print invalid*/
                free(label);
                return NULL;
            } else
                break;
        }
    }

    if (i < len) {
        /*label too long*/
        if (i > LABEL_MAX_LEN) {
            /*print too long*/
            free(label);
            return NULL;
        }

        strncpy(label, cmdStr, i);

        /*look for invalid chars*/
        error = !validLabelChars(label, i) ? 1 : error;

        /*make sure here the label is not a reserved keyword*/
        error = isKeyword(label) ? 1 : error;

        if (error) {
            free(label);
            return NULL;
        }

        return label;
    }

    /*return empty*/
    return label;
}

static int validLabelChars(char *label, int len) {
    int i;
    char c;

    for (i = 0; i < len; i++) {
        c = label[i];
        if (i == 0 && !(isalpha(c))) {
            return 0;
        } else if (!isalnum(c)) {
            return 0;
        }
    }

    return 1;
}

static int isComment(char *str) {
    return str[0] == ';';
}