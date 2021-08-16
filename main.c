#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./globals.h"
#include "./io/io.h"
#include "./operations/operations.h"
#include "./parser/parser.h"
#include "./symbols/symbols.h"

int main(int argc, char *argv[]) {
    int i;
    /* Get an array of valid file name strings */
    char **filenames = getFilenamesFromArgs(argc, argv);
    if (!filenames)
        return 0;

    /* Iterate over all valid file names */
    for (i = 0; filenames[i]; i++) {
        /* For temporary line storage */
        char line[MAX_COMMAND_LEN];
        FILE *srcFile = readFile(filenames[i]);
        Node *symbolsHead = NULL;
        Node *commandsHead = NULL;
        Node *currCmd = NULL;
        unsigned int IC = 100;
        unsigned int DC = 0;

        if (!srcFile) {
            /* Error, skip to the next file name */
            continue;
        }

        /* PHASE 1 */
        while (readNextLine(line)) {
            Command *cmd = parseCommand(line);
            Symbol *sym = symbolFromCommand(cmd);
            /*to save temp values of DC or IC*/
            int address = 0;

            if (!cmd)
                continue;

            if (startsWith(cmd->op, '.')) {
                /*encode it now*/

                address = DC;
                /*update DC, note the amount updated varies unlike IC*/
            } else {
                /*encode it after due to symbols undefined yet*/
                address = IC;
                IC += 4;
            }

            /*attempt to store*/
            /*should check .entry or external before*/
            if (strMatch(cmd->op, ".entry") || strMatch(cmd->op, ".external")) {
                /*warning msg*/
                freeSymbol(sym);
            } else {
                int stored = storeSymbol(&symbolsHead, sym, address);

                if (!stored)
                    freeSymbol(sym);
            }
            /*
            printCommand(cmd);
            printf("\n");*/

            insertLast(&commandsHead, cmd);
        }

        /* PHASE 2 */
        currCmd = commandsHead;
        while (currCmd) {
            /*encode commands*/

            currCmd = currCmd->next;
        }
        /*Generate output files if no errors occurred*/

        /* CLEANUP */
        closeFile();
        freeSymbolList(symbolsHead);
        freeCommandList(commandsHead);
    }

    free(filenames);

    return 0;
}