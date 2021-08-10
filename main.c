#include <stdio.h>
#include <stdlib.h>

#include "./globals.h"
#include "./io/io.h"
#include "./operations/operations.h"
#include "./parser/parser.h"
#include "./symbols/symbols.h"

int main(int argc, char *argv[]) {
    int i;
    /* For temporary temp storage */
    char temp[MAX_COMMAND_LEN];
    /* Get an array of valid file name strings */
    char **filenames = getFilenamesFromArgs(argc, argv);
    if (filenames == NULL) return 0;

    /* Iterate over all valid file names */
    for (i = 0; *(filenames + i); i++) {
        FILE *srcFile = fopen(filenames[i], "r");
        if (!srcFile) {
            /* Error, skip to the next file name */
            printErrorMessage(FILE_OPEN_FAIL, filenames[i]);
            continue;
        }

        /* PHASE 1 */
        while (fgets(temp, MAX_COMMAND_LEN, srcFile) != NULL) {
            Command *cmd = parseCommand(temp);
            /*puts(temp);*/

            printCommand(cmd);
            printf("\n");
            freeCommand(cmd);
        }

        /* PHASE 2 */

        /* CLEANUP */
        fclose(srcFile);

        /*Generate output files if no errors occurred*/
    }

    free(filenames);

    return 0;
}