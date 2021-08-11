#include "utils.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "../globals.h"

Node *nodify(void *ptrData) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL)
        return NULL;

    newNode->data = ptrData;
    newNode->next = NULL;

    return newNode;
}

void freeNodeShallowData(Node *node) {
    if (node == NULL)
        return;

    free(node->data);
    free(node);
}

void freeListShallow(Node *head) {
    Node *temp;

    if (head == NULL)
        return;

    while (head != NULL) {
        temp = head->next;
        freeNodeShallowData(head);
        head = temp;
    }
}

void insertInfront(Node **ptrHead, void *ptrData) {
    Node *node;

    node = nodify(ptrData);
    node->next = (*ptrHead);

    (*ptrHead) = node;
}

void insertLast(Node **ptrHead, void *ptrData) {
    Node *node;
    Node *head = *ptrHead;
    node = nodify(ptrData);

    if (head == NULL) {
        *ptrHead = node;
        return;
    }

    while (head->next != NULL) {
        head = head->next;
    }

    head->next = node;
}

void insertNodeLast(Node **list, Node *node) {
    Node *head = *list;

    if (head == NULL) {
        *list = node;
        return;
    }

    while (head->next != NULL) {
        head = head->next;
    }

    head->next = node;
}

Node *strtokSplit(char *str, char *delim, int stopSplitAt) {
    char temp[MAX_COMMAND_LEN];
    char *token;
    char *p;
    char *stop;
    char remainder[MAX_COMMAND_LEN];
    Node *head = NULL;

    strcpy(temp, str);

    stop = strchr(temp, stopSplitAt);
    if (stop != NULL) {
        strcpy(remainder, stop);
        stop[0] = '\0';
    }

    p = strtok(temp, delim);
    while (p != NULL) {
        token = newStringCopy(p);
        insertLast(&head, token);

        p = strtok(NULL, delim);
    }

    if (stop != NULL) {
        token = newStringCopy(remainder);
        insertLast(&head, token);
    }

    return head;
}

Node *split(char *str, char *phrase) {
    int left;
    int right;
    int len;
    int phraseLen;
    char *temp;
    Node *head = NULL;

    len = strlen(str);
    phraseLen = strlen(phrase);
    if (len == 0 || phraseLen == 0) {
        return NULL;
    }

    /*NOTE: consider dropping the tests at the edges in order to clean the code at parseArgumentList*/
    /*match at the begining*/
    if (strncmp(str, phrase, phraseLen) == 0) {
        left = phraseLen;
    } else {
        left = 0;
    }

    for (right = left + 1; right < len; right++) {
        if (strncmp(str + right, phrase, phraseLen) == 0) {
            temp = calloc(right - left + 1, sizeof(char));
            strncpy(temp, str + left, right - left);

            insertLast(&head, temp);

            left = right + phraseLen;
            right = left;
        }
    }

    /*add rest if there is any*/
    temp = calloc(right - left + 1, sizeof(char));
    strcpy(temp, str + left);

    if (isEmptyStr(temp)) {
        free(temp);
        return head;
    }

    insertLast(&head, temp);

    return head;
}

char *trim(char *str) {
    int len = strlen(str);
    int left;
    int right;
    char *newStr;

    newStr = calloc(len + 1, sizeof(char));

    for (left = 0; isspace(str[left]); left++)
        ;

    /*empty*/
    if (left == len) {
        return newStr;
    }

    for (right = len - 1; isspace(str[right]); right--)
        ;

    strncpy(newStr, str + left, right - left + 1);

    return newStr;
}

int isEmptyStr(char *str) {
    return (*str) == '\0';
}

void freeStringArray(char **arr) {
    int i;

    if (arr == NULL) {
        return;
    }

    for (i = 0; *(arr + i); i++) {
        free(*(arr + i));
    }

    free(arr);
}

char *newStringCopy(char *str) {
    char *copy = calloc(strlen(str) + 1, sizeof(char));
    strcpy(copy, str);

    return copy;
}

int startsWith(char *str, int c) {
    return str[0] == c;
}

int endsWith(char *str, int c) {
    return str[strlen(str) - 1] == c;
}