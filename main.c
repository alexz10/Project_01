#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "parser.h"

int main(int argc, char const *argv[]) {
    int flag = 1;
    while(flag){
        printf("$:");
        char * line = read_line();
        char ** commands = command_split(line);

        int i = 0;
        while(commands[i]){
            char ** args = parse_args(commands[i++]);
            if(strcmp(args[0],"exit")==0) flag = 0;

            int parent = getpid();
            int child = fork();
            int status;

            if(getpid() != parent) execvp(args[0], args);
            else wait(&status);


            free(args);
            args = NULL;
        }

        free(line);free(commands);
        line = NULL; commands = NULL;
    }
    return 0;
}
