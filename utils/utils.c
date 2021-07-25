#include "utils.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char *trim(char *str) {
    int len = strlen(str);
    int left;
    int right;
    char *newStr;

    newStr = calloc(len, sizeof(char));

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