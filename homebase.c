#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "extra_commands.h"
#include "parser.h"
#include <string.h>
#include <sys/wait.h>

//returns 1 on run and 0 if it encounters exit 
int run_cmd(char *cmd) {
    char **args = parse_args(cmd);
    //special case functions
    if(!strcmp(args[0], "exit")) {
        free(args); args = NULL;
        return 0;
    }

    if(!strcmp(args[0],"cd")) {
        cmd_cd(args);

        free(args); args = NULL;
        return 1;
    }
    //messing with stdin/out for pipes and redirection

    //forking the parent
    int cld = fork();
    int status;

    if(!cld) execvp(args[0], args);
    else wait(&status);

    free(args); args = NULL;
    return 1;
}
