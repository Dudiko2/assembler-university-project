#include <stdio.h>
#include "parser.h"

int main(int argc, char *argv[]) {
    int i;
    char **args = parseCommandLine(argc, argv);
    
    for (i=0; args[i]; i++) {
        printf("%s\n", args[i]);
    }

    return 0;
}