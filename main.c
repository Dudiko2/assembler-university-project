#include <stdio.h>
#include <stdlib.h>

#include "./errors/errors.h"
#include "./parser/parser.h"

#define MAX_COMMAND_LEN 82

int main(int argc, char *argv[]) {
    int i;
    int j;
    /* For temporary temp storage */
    char temp[MAX_COMMAND_LEN];
    /* Get an array of valid file name strings */
    char **filenames = parseCommandLineArgs(argc, argv);
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
        j = 1;
        while (fgets(temp, MAX_COMMAND_LEN, srcFile) != NULL) {
            command *cmd = genCommand();
            parseCommand(cmd, temp);

            printf("%d\t", j++);
            printf("%s\n", cmd->label);
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