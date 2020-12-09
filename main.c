#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "parser.h"

int main(int argc, char const *argv[]) {
    printf("Start\n");

    while(1){
        char * line = read_line();
        char ** commands = command_split(line);
        
        int i = 0;
        while(commands[i]){

            char ** args = parse_args(commands[i++]);
            execvp(args[0], args);

            free(args);
            args = NULL;
        }

        free(line);free(commands);
        line = NULL; commands = NULL;
    }
    return 0;
}
