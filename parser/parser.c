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
/*returns whether STR is a properly declared string (according to the spec)*/
static int isString(char *str);
static int validateOperationArgs(Command *cmd);
static int matchArgsToFormat(char **args, char *format);

Command *parseCommand(char *cmdStr) {
    int error = 0;
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

    tokenListHead = strtokSplit(trimmed, " \t", '\"');
    error = mapTokenListToCmd(cmd, tokenListHead);

    free(trimmed);
    freeListShallow(tokenListHead);

    if (error || !validateOperationArgs(cmd)) {
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
        printErrorMessage(INVALID_LABEL_CHARS, label);
        free(label);
        return NULL;
    }

    /*label too long, NULL*/
    if (strlen(label) > LABEL_MAX_LEN) {
        printErrorMessage(LONG_LABEL, label);
        free(label);
        return NULL;
    }

    /*invalid token, NULL*/
    if (isKeyword(label)) {
        printErrorMessage(INVALID_LABEL, label);
        free(label);
        return NULL;
    }

    return label;
}

char *parseOperation(char *str) {
    char *op;

    if (!isKeyword(str)) {
        printErrorMessage(INVALID_OPERATION, str);
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
        printErrorMessage(COMMA_START, "");
        freeStringArray(arguments);
        return NULL;
    }

    while (token != NULL) {
        char *data = token->data;

        if (token->next == NULL && endsWith(data, ',')) {
            printErrorMessage(COMMA_END, "");
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

static int isComment(char *str) {
    return startsWith(str, ';');
}

static int isString(char *str) {
    return startsWith(str, '\"') && endsWith(str, '\"');
}

static int validateOperationArgs(Command *cmd) {
    char *op = cmd->op;
    char **args = cmd->arguments;
    char **formats = getArgFormats(op);
    int i;
    int status;

    for (i = 0; formats[i]; i++) {
        status = matchArgsToFormat(args, formats[i]);

        if (!status)
            return 1;
    }

    printErrorMessage(status, "FIX THIS!!");

    return 0;
}

static int matchArgsToFormat(char **args, char *format) {
    int i = 0;
    int j = 0;
    char *arg;
    char formatArg;

    while ((arg = args[i]) && (formatArg = format[j])) {
        if (formatArg == '+') {
            j--;
            continue;
        }

        if ((formatArg == 'n' && isNumber(arg, 1)) ||
            (formatArg == 'r' && isRegister(arg)) ||
            (formatArg == 'l' && validLabelChars(arg, strlen(arg))) ||
            (formatArg == 's' && isString(arg))) {
            j++;
        } else {
            return INVALID_ARG;
        }

        i++;
    }

    if (args[i]) {
        return TOO_MANY_ARGS;
    }

    if (format[j] && format[j] != '+') {
        return MISSING_ARGS;
    }

    return 0;
}