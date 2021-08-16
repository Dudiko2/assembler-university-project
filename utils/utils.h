#ifndef UTILS_H
#define UTILS_H

/*Represents a list node*/
typedef struct Node Node;

struct Node {
    void *data;
    Node *next;
};

/*
takes a pointer to some data and wraps it inside a node.
NOTE: this function does not make a copy of the data, but uses the existing data instead.
*/
Node *nodify(void *ptrData);

/*
frees the memory allocated to the node and it's data.
should only be used when the data is shallow (i.e. no pointers nested in data)
*/
void freeNodeShallowData(Node *node);

/*
frees an entire list using freeNodeShallowData
*/
void freeListShallow(Node *head);

/*
frees a list.
each node's data is freed using FUNC.
*/
void freeListWithFunc(Node *head, void (*func)(void *data));

/*
takes a ref to the head of a list (ptrHead) and a pointer to some data, then puts a new node containing ptrData as the head.
NOTE: this function does not make a copy of the data, but uses the existing data instead.
*/
void insertInfront(Node **ptrHead, void *ptrData);

/*
takes a ref to the head of a list (ptrHead) and a pointer to some data, then puts a new node containing ptrData as the tail.
NOTE: this function does not make a copy of the data, but uses the existing data instead.
*/
void insertLast(Node **ptrHead, void *ptrData);

void insertNodeLast(Node **list, Node *node);

/*
Splits a string into a linked list of words. uses strtok.
The list has to be free()'d to prevent memory leaks
*/
Node *strtokSplit(char *str, char *delim, int stopSplitAt);

/*
Splits a string into a linked list of words at points that match PHRASE exactly.
The list has to be free()'d to prevent memory leaks
*/
Node *split(char *str, char *phrase);

/*
returns a new copy of str minus the spaces surronding it.
return value needs to be free()'d after use
 */
char *trim(char *str);

/*returns whether STR is an empty string*/
int isEmptyStr(char *str);

void freeStringArray(char **arr);

/*
creates a new copy of STR.
needs to be free()'d after use
*/
char *newStringCopy(char *str);

int startsWith(char *str, int c);

int endsWith(char *str, int c);

int strMatch(char *str1, char *str2);

long int strToInt(char *str);

int isRegister(char *str);

int isNumber(char *str, int mayHaveSign);

#endif