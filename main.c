#include <stdio.h>
#include "./parser/parser.h"
#include "./errors/errors.h"

int main(int argc, char *argv[]) {
    int i;
    /* Get an array of valid file name strings */
    char **args = parseCommandLine(argc, argv);
    
    /* Iterate over all valid file names */
    for (i=0; args[i]; i++) {
        FILE *srcFile = fopen(args[i], "r");
        if (!srcFile) {
            /* Error, skip to the next file name */
            printErrorMessage(FILE_OPEN_FAIL, args[i]);
            continue;
        }

        /* Iterate over srcFile twice */
        while(!feof(srcFile)) {
            putchar(getc(srcFile));
        }
        fseek(srcFile, 0, SEEK_SET);
        while(!feof(srcFile)) {
            putchar(getc(srcFile));
        }


        fclose(srcFile);
    }

    return 0;
}