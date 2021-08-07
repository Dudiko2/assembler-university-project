#include "parser.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../io/io.h"
#include "../operations/operations.h"

/*returns whether the characters in LABEL are allowed*/
static int validLabelChars(char *label, int len);
static int isComment(char *str);

Command *parseCommand(char *cmdStr) {
    char error = 0;
    char *trimmed;
    Command *cmd = newCommand();
    Node *tokenListHead = NULL;

    trimmed = trim(cmdStr);

    /*nothing to parse */
    if (isComment(trimmed) || isEmptyStr(trimmed)) {
        free(trimmed);
        freeCommand(cmd);
        return NULL;
    }

    tokenListHead = strSplit(trimmed, " ");
    error = mapTokenListToCmd(cmd, tokenListHead);

    free(trimmed);
    freeListShallow(tokenListHead);

    if (error) {
        freeCommand(cmd);
        return NULL;
    }

    return cmd;
}

int mapTokenListToCmd(Command *cmd, Node *tokenNode) {
    cmd->label = parseLabel(tokenNode->data);
    if (cmd->label == NULL) {
        return -1;
    }

    if (!isEmptyStr(cmd->label)) {
        tokenNode = tokenNode->next;
    }
    cmd->op = parseOperation(tokenNode->data);
    if (cmd->op == NULL) {
        return -1;
    }

    /*
    token = pop
    args = token[]
    */

    /* VERIFY LATER */

    return 0;
}

char *parseLabel(char *str) {
    int len = strlen(str);
    char *label = calloc(len + 1, sizeof(char));

    /* no label, return empty */
    if (str[len - 1] != ':') {
        return label;
    }

    /*copy every char except ':'*/
    strncpy(label, str, len - 1);

    /*invalid label, return NULL*/
    if (!validLabelChars(label, len - 1)) {
        /*msg*/
        free(label);
        return NULL;
    }

    /*label too long, NULL*/
    if (strlen(label) > LABEL_MAX_LEN) {
        /*msg*/
        free(label);
        return NULL;
    }

    /*invalid token, NULL*/
    if (isKeyword(label)) {
        /*msg*/
        free(label);
        return NULL;
    }

    return label;
}

char *parseOperation(char *str) {
    char *op;

    if (!isKeyword(str)) {
        /*msg*/
        return NULL;
    }

    op = calloc(strlen(str) + 1, sizeof(char));
    strcpy(op, str);

    return op;
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