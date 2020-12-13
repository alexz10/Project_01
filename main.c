#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "parser.h"
#include "homebase.h"

int main(int argc, char const *argv[]) {
    char ndone = 1;
    while(ndone) {
        printf("$:");
        char * line = read_line();
        char ** commands = command_split(line);
        char ** cmdp = commands;

        while(ndone && *cmdp){
            ndone = run_cmd(*cmdp), cmdp++;
        }

        free(line);line = NULL;
        free(commands);commands = NULL;
    }

    return 0;
}
