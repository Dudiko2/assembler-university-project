#include "parser.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../io/io.h"
#include "../operations/operations.h"

/*returns whether the characters in LABEL are allowed*/
static int validLabelChars(char *label, int len);
static int startsWith(char *str, int c);
static int endsWith(char *str, int c);
static int isComment(char *str);
/*returns whether STR is a properly declared string (according to the spec)*/
static int isString(char *str);

Command *parseCommand(char *cmdStr) {
    char error = 0;
    char *trimmed;
    Command *cmd = newCommand();
    Node *tokenListHead = NULL;

    trimmed = trim(cmdStr);
    /*handle cmd max length*/

    /*nothing to parse */
    if (isComment(trimmed) || isEmptyStr(trimmed)) {
        free(trimmed);
        freeCommand(cmd);
        return NULL;
    }

    tokenListHead = strtokSplit(trimmed, " \t", '\"');
    error = mapTokenListToCmd(cmd, tokenListHead);

    free(trimmed);
    freeListShallow(tokenListHead);

    if (error) {
        freeCommand(cmd);
        return NULL;
    }

    return cmd;
}

int mapTokenListToCmd(Command *cmd, Node *headToken) {
    cmd->label = parseLabel(headToken->data);

    /*invalid label*/
    if (cmd->label == NULL) {
        return -1;
    }

    /*label found, next token*/
    if (!isEmptyStr(cmd->label)) {
        headToken = headToken->next;
    }

    cmd->op = parseOperation(headToken->data);
    if (cmd->op == NULL) {
        return -1;
    }

    headToken = headToken->next;

    cmd->arguments = parseArgumentList(headToken);
    if (cmd->arguments == NULL) {
        return -1;
    }

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

    op = newStringCopy(str);

    return op;
}

char **parseArgumentList(Node *token) {
    int argsLen = ARGS_LEN + 1;
    int i;
    char **arguments = calloc(argsLen, sizeof(char *));
    char *temp;
    Node *head = NULL;
    Node *curr;

    /*no args, return empty*/
    if (token == NULL) {
        return arguments;
    }

    /*handle comma at beginning and end of args*/
    if (startsWith(token->data, ',')) {
        freeStringArray(arguments);
        return NULL;
    }

    while (token != NULL) {
        char *data = token->data;

        if (token->next == NULL && endsWith(data, ',')) {
            freeStringArray(arguments);
            freeListShallow(head);

            return NULL;
        }

        /*check if token holds an asciz string before splitting*/
        if (isString(data)) {
            char *copy = newStringCopy(data);

            insertLast(&head, copy);
        } else {
            insertNodeLast(&head, split(data, ","));
        }

        token = token->next;
    }

    /*convert list to string array here*/
    i = 0;
    curr = head;
    while (curr != NULL) {
        temp = newStringCopy(curr->data);

        if (i == argsLen) {
            int j;

            argsLen += ARGS_LEN;
            arguments = realloc(arguments, argsLen * sizeof(char *));
            for (j = i; j < argsLen; j++) {
                arguments[j] = '\0';
            }
        }

        arguments[i] = temp;

        curr = curr->next;
        i++;
    }

    freeListShallow(head);

    return arguments;
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

static int startsWith(char *str, int c) {
    return str[0] == c;
}

static int endsWith(char *str, int c) {
    return str[strlen(str) - 1] == c;
}

static int isComment(char *str) {
    return startsWith(str, ';');
}

static int isString(char *str) {
    return startsWith(str, '\"') && endsWith(str, '\"');
}