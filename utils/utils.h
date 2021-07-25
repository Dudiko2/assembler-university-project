#ifndef UTILS_H
#define UTILS_H

/*
returns a new copy of str minus the spaces surronding it.
return value needs to be free()'d after use
 */
char *trim(char *str);
/*returns whether STR is an empty string*/
int isEmptyStr(char *str);

#endif