#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include "extra_commands.h"
#include "parser.h"

#define MAX_PATH_LEN 4096
//will just do this as a define here instead of like a settings file right now
#define PROMPT_COLOR "\e[1;30m"
#define RESET "\e[0m"

//returns 1 on run and 0 if it encounters exit
int run_cmd(char *cmd) {

    //check for special characters first
    int symb_type = check_symbol (cmd);

    //if no special characters then default
    if (symb_type == 0) {
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

        //forking the parent
        int cld = fork();
        int status, check = 0;

        if(!cld) check = execvp(args[0], args);
        else wait(&status);

        if(check == -1){
            printf ("Error: %s\n", strerror(errno));
            return -1;
        }

        free(args); args = NULL;
        return 1;
    }

    //echo hi > out.txt; ls

    //redirect output
    else if (symb_type == 1) {

    	char ** args = parse_symbol (cmd, ">");

    	char ** call = parse_args (args[0]);
    	char * filename = malloc (MAX_PATH_LEN);
    	filename = args[1];
        while(*filename == ' ') filename++;
        trim_trailing(filename);

    	int fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
        if (fd == -1) {
            printf ("Error: %s\n", strerror(errno));
            return 1;
        }

        int backup_stdout = dup(STDOUT_FILENO);
        dup2 (fd, STDOUT_FILENO);

        int cld = fork();
        int status, check = 0;

        if(!cld) check = execvp(args[0], args);
        else wait(&status);

        if(check == -1){
            printf ("Error: %s\n", strerror(errno));
            return -1;
        }

        free(args); args = NULL;
        dup2 (backup_stdout, STDOUT_FILENO);
        close (fd);

        return 1;
    }

    //redirect input
    else if (symb_type == 2) {

    	char ** args = parse_symbol (cmd, "<");

    	char ** call = parse_args (args[0]);
    	char * filename = malloc (MAX_PATH_LEN);
    	filename = args[1];

        while(*filename == ' ') filename++;
        trim_trailing(filename);

    	int fd = open(filename, O_RDONLY);

        if (fd == -1) {
            printf ("Error: %s\n", strerror(errno));
            return 1;
        }

        int backup_stdin = dup(STDIN_FILENO);
        dup2 (fd, STDIN_FILENO);

        int cld = fork();
        int status, check = 0;

        if(!cld) check = execvp(args[0], args);
        else wait(&status);

        if(check == -1){
            printf ("Error: %s\n", strerror(errno));
            return -1;
        }

        free(args); args = NULL;

        dup2 (backup_stdin, STDIN_FILENO);
        close (fd);

        return 1;
    }

    //piping
    else if (symb_type == 3) {
    	//printf ("Piping\n");
    	return 1;
    }

    else if(symb_type == 4){
        char ** args = parse_append (cmd);

    	char ** call = parse_args (args[0]);
    	char * filename = malloc (MAX_PATH_LEN);
    	filename = args[1];

        while(*filename == ' ') filename++;
        trim_trailing(filename);

        int fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
        if (fd == -1) {
            printf ("Error: %s\n", strerror(errno));
            return 1;
        }

        int backup_stdout = dup(STDOUT_FILENO);
        dup2 (fd, STDOUT_FILENO);

        int cld = fork();
        int status, check = 0;

        if(!cld) check = execvp(args[0], args);
        else wait(&status);

        if(check == -1){
            printf ("Error: %s\n", strerror(errno));
            return -1;
        }

        free(args); args = NULL;
        dup2 (backup_stdout, STDOUT_FILENO);
        close (fd);

        return 1;

    }

    else return -1;
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
