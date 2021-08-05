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

void insertLast(Node *head, void *ptrData) {
    Node *node;

    if (head == NULL)
        return;

    node = nodify(ptrData);

    while (head->next != NULL) {
        head = head->next;
    }

    head->next = node;
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
    if (left > right) {
        return newStr;
    }

    strncpy(newStr, str + left, right - left + 1);

    return newStr;
}

int isEmptyStr(char *str) {
    return (*str) == '\0';
}