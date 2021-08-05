#include "utils.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

Node *nodify(void *ptrData) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL)
        return NULL;

    newNode->data = ptrData;
    newNode->next = NULL;

    return newNode;
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

Node *popFirst(Node **ptrHead) {
    Node *node;

    if (*ptrHead == NULL)
        return NULL;

    node = *ptrHead;
    *ptrHead = node->next;
    node->next = NULL;

    return node;
}

Node *strSplit(char *str, char *delim) {
    char *token;
    char *p;
    Node *head = NULL;

    p = strtok(str, delim);
    while (p != NULL) {
        token = calloc(strlen(p) + 1, sizeof(char));
        strcpy(token, p);
        insertLast(&head, token);

        p = strtok(NULL, delim);
    }

    /*handle leaks*/

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
    for (right = len; isspace(str[right]); right--)
        ;

    /*empty*/
    if (left >= right) {
        return newStr;
    }

    strncpy(newStr, str + left, right - left - 1);

    return newStr;
}

int isEmptyStr(char *str) {
    return (*str) == '\0';
}