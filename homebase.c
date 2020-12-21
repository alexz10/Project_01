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

int norm_cmd(char *cmd);
int redirected_out_cmd(char *cmd, char append);
int redirected_in_cmd(char *cmd);

//returns 1 on run and 0 if it encounters exit
int run_cmd(char *cmd) {

    //check for special characters first
    int symb_type = check_symbol (cmd);

    //if no special characters then default stdin/stdout
    if (symb_type == 0) {
        return norm_cmd(cmd);
    }

    //echo hi > out.txt; ls

    //redirect output
    else if (symb_type == 1) {
        redirected_out_cmd(cmd,0);
    }

    //redirect input
    else if (symb_type == 2) {
        redirected_in_cmd(cmd);
    }

    //piping
    else if (symb_type == 3) {
    	//printf ("Piping\n");
    	return 1;
    }
    //appending redirected output ">>"
    else if(symb_type == 4){
        redirected_out_cmd(cmd,1);
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
//A normal function, returns 1 on sucessful run and 0 on exit
int norm_cmd(char *cmd) {
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

    if(!cld) {
        //child run command
        check = execvp(args[0], args);
        exit(check);
    }
    else {
        wait(&status);

        if(check == -1){
            printf ("Error: command not found\n");
            return -1;
        }

        free(args); args = NULL;
        return 1;
    }
}

//returns a dupped original file descriptor so it isn't lost
int redirect_file_descriptor(int orignial_fd, int new_fd) {
    int backup_fd = dup(orignial_fd);
    dup2 (new_fd, orignial_fd);
    return backup_fd;
}

//honestly I don't know what this returns
int redirected_out_cmd(char *cmd, char append) {
    char **args;
    if(append) {
        args = parse_append (cmd);
    } else {
        args = parse_symbol (cmd, ">");
    }

    char ** call = parse_args (args[0]);
    char * filename = malloc (MAX_PATH_LEN);
    filename = args[1];
    while(*filename == ' ') filename++;
    trim_trailing(filename);

    //open file descriptor and redirect stdin
    int fd;
    if(append) {
        fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
    } else {
        fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    }
    if (fd == -1) {
        printf ("Error: %s\n", strerror(errno));
        return 1;
    }

    int backup_stdout = redirect_file_descriptor(STDOUT_FILENO, fd);

    //forking parent and child
    int cld = fork();
    int status, check = 0;

    if(!cld) {
        check = execvp(call[0], call);
        exit(check);
    } else {
        wait(&status);
        //resets stdout to normal
        free(args); args = NULL;
        dup2 (backup_stdout, STDOUT_FILENO);
        close (fd);

        if(check == -1){
            printf ("Error: command not found\n");
            return -1;
        }

        return 1;
    }
}

//please write something nicer next time Alex, I can't figure out what you want this to return on error and on success. Maybe I am just too tired to think right now.
int redirected_in_cmd(char *cmd) {
    //more parsing nonsense
    char ** args = parse_symbol (cmd, "<");

    char ** call = parse_args (args[0]);
    char * filename = malloc (MAX_PATH_LEN);
    filename = args[1];

    while(*filename == ' ') filename++;
    trim_trailing(filename);

    //open file descriptor for input file
    int fd = open(filename, O_RDONLY);

    if (fd == -1) {
        printf ("Error: %s\n", strerror(errno));
        return 1;
    }

    int backup_stdin = redirect_file_descriptor(STDIN_FILENO, fd);

    int cld = fork();
    int status, check = 0;

    if(!cld) {
        check = execvp(call[0], call);
        exit(check);
    } else {
        wait(&status);

        free(args); args = NULL;

        dup2 (backup_stdin, STDIN_FILENO);
        close (fd);

        if(check == -1){
            printf ("Error: command not found\n");
            return -1;
        }

        return 1;
    }
}
