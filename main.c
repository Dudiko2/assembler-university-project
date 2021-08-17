#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./encoder/encoder.h"
#include "./globals.h"
#include "./io/io.h"
#include "./operations/operations.h"
#include "./parser/parser.h"
#include "./symbols/symbols.h"

/*for debug only*/
static void printBinList(Node *listhead);
static void printSymbolTable(Node *head);

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
        Node *codeImageHead = NULL;
        Node *dataImageHead = NULL;
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
                if (strMatch(cmd->op, ".extern")) {
                    /*store extern*/
                    storeExtern(&symbolsHead, cmd->arguments[0]);
                } else {
                    address = DC;

                    DC += encodeCmd(cmd, &dataImageHead, NULL, DC);
                }
            } else {
                /*encode it after due to symbols undefined yet*/
                address = IC;
                IC += 4;
            }

            /*attempt to store*/
            /*should check .entry or external before*/
            if (strMatch(cmd->op, ".entry") || strMatch(cmd->op, ".extern")) {
                /*warning msg*/
                printf("REPLACE THIS meaningless label for %s\n", cmd->op);
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

        /*Update data adresses in symbol table*/
        updateDataAdresses(symbolsHead, IC);

        /* PHASE 2 */
        IC = 100;
        currCmd = commandsHead;
        while (currCmd) {
            /*encode commands*/
            Command *cmd = currCmd->data;
            if (!startsWith(cmd->op, '.')) {
                IC += encodeCmd(cmd, &codeImageHead, &symbolsHead, IC);
            } else {
                /*set entries*/
            }

            currCmd = currCmd->next;
        }
        /*Generate output files if no errors occurred*/

        /*print for debug*/
        puts("\n\ncode image\n");
        printBinList(codeImageHead);
        puts("\n\ndata image\n");
        printBinList(dataImageHead);
        printSymbolTable(symbolsHead);

        /* CLEANUP */
        closeFile();
        freeSymbolList(symbolsHead);
        freeCommandList(commandsHead);
        freeListShallow(dataImageHead);
        freeListShallow(codeImageHead);
    }

    free(filenames);

    return 0;
}

static void printBinList(Node *listhead) {
    Node *curr = listhead;
    while (curr) {
        int i;
        int *bin = curr->data;
        for (i = 0; bin[i] != -1; i++) {
            printf("%d", bin[i]);
        }
        printf("\n");

        curr = curr->next;
    }
}

static void printSymbolTable(Node *head) {
    Node *curr = head;
    Symbol *sym;

    printf("\nSYMBOLS:\n");
    while (curr) {
        sym = curr->data;
        printf("%5d | %10s | %s", sym->address, sym->name, sym->external ? "extern" : "");
        printf("\n");

        curr = curr->next;
    }
}