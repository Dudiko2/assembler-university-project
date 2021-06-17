#include <stdio.h>
#include "errors.h"

void printErrorMessage(errorMessage msgType, char *str) {
    switch (msgType)
    {
    case INVALID_FNAME:
        fprintf(stderr, "Invalid file name: %s\n", str);
        break;

    case FILE_OPEN_FAIL:
        fprintf(stderr, "Error opening file: %s\n", str);
        break;
    
    default:
        break;
    }
}
