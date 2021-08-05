#ifndef UTILS_H
#define UTILS_H

/*Represents a list node*/
typedef struct Node Node;

struct Node {
    void *data;
    Node *next;
};

/*takes a pointer to some data and wraps it inside a node. NOTE: this function does not make a copy of the data, but uses the existing data instead.*/
Node *nodify(void *ptrData);

/*takes a ref to the head of a list (ptrHead) and a pointer to some data, then puts a new node containing ptrData as the head*/
void insertInfront(Node **ptrHead, void *ptrData);

/*takes a ref to the head of a list (ptrHead) and a pointer to some data, then puts a new node containing ptrData as the tail*/
void insertLast(Node **ptrHead, void *ptrData);

/*Removes the first node of a list and returns it*/
Node *popFirst(Node **ptrHead);

/*
Splits a string into a linked list of words. uses strtok.
Each word has to be free()'d to prevent memory leaks
*/
Node *strSplit(char *str, char *delim);

/*
returns a new copy of str minus the spaces surronding it.
return value needs to be free()'d after use
 */
char *trim(char *str);

/*returns whether STR is an empty string*/
int isEmptyStr(char *str);

#endif