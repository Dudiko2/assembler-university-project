#ifndef ERROR_H
#define ERROR_H

typedef enum errorMessage {
    INVALID_FNAME,
    FILE_OPEN_FAIL
} errorMessage;

void printErrorMessage(errorMessage msgType, char *str);

#endif