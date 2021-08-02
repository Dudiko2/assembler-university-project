#ifndef UTILS_H
#define UTILS_H

typedef struct Node Node;

struct Node {
    void *data;
    Node *next;
};

Node *nodify(void *ptrData);
void insertInfront(Node **ptrHead, void *ptrData);
/*
returns a new copy of str minus the spaces surronding it.
return value needs to be free()'d after use
 */
char *trim(char *str);
/*returns whether STR is an empty string*/
int isEmptyStr(char *str);

#endif