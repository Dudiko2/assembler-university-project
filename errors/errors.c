#include "errors.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printErrorMessage(errorMessage msgType, char *str) {
    char *errMsg = calloc(100, sizeof(char));
    strcpy(errMsg, "Unknown error: %s\n");

    switch (msgType) {
        case INVALID_FNAME:
            strcpy(errMsg, "Invalid file name: %s\n");
            break;

        case FILE_OPEN_FAIL:
            strcpy(errMsg, "Error opening file: %s\n");
            break;
        case INVALID_LABEL:
            strcpy(errMsg, "Invalid label at %s\n");
        default:
            break;
    }

    /*fprintf(stderr, errMsg, str);*/
    printf(errMsg, str);
    free(errMsg);
}
