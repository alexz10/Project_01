#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include "parser.h"
#include "extra_commands.h"

int main(int argc, char const *argv[]) {
    int flag = 1;
    while(flag){
        printf("$:");
        char * line = read_line();
        char ** commands = command_split(line);

        int i = 0;
        while(commands[i]){
            char ** args = parse_args(commands[i++]);
            if(!strcmp(args[0],"exit")) flag = 0; //still need to free memory
            //tmp block to test cd function
            if(!strcmp(args[0],"cd")) {
                cmd_cd(args);

                free(args); args = NULL;
                continue;
            }

            int parent = getpid();
            int child = fork();
            int status;

            if(getpid() != parent) execvp(args[0], args);
            else wait(&status);


            free(args);args = NULL;
        }

        free(line);line = NULL;
        free(commands);commands = NULL;
    }

    return 0;
}
