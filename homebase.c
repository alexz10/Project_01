#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "extra_commands.h"
#include "parser.h"
#include <string.h>
#include <sys/wait.h>
#define MAX_PATH_LEN 4096
//will just do this as a define here instead of like a settings file right now
#define PROMPT_COLOR "\e[1;30m"
#define RESET "\e[0m"

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

//prints the prompt
//possibly change so it stores the prompt when it doesn't update but won't do now
void print_prompt() {
    char buf[MAX_PATH_LEN];
    //buffer might be too small or another issue so just default to this
    if(!getcwd(buf,sizeof(buf)-1)) {
        printf("$: ");
        return;
    }
    char *home_name = getenv("HOME");
    //the variable didn't exist
    if(!home_name) {
        printf("$: ");
        return;
    }
    int hnlen = strlen(home_name);
    int blen = strlen(buf);
    if(hnlen < blen) {
        printf(PROMPT_COLOR "~/%s" RESET "$: ", buf + strlen(home_name) + 1);
    } else if(hnlen == blen) { //I don't know why I need this case but it works
        printf(PROMPT_COLOR "~" RESET "$: ");

    } else {
        printf(PROMPT_COLOR "%s" RESET "$: ", buf);
    }
    return;
}
