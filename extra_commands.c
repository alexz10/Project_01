#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "parser.h"

//returns 0 on sucess else -1, changes cwd, a wrapper function for chdir
int cmd_cd(char **args) {
    char *new_path;
    if(!args[1]) {
        new_path = getenv("HOME");
        if(!new_path) {
            printf("No such file or directory\n");
            return -1;
        }
    } else {
        new_path = args[1];
    }

    int w = chdir(new_path);
    if(w == -1) {
        printf("%s\n",strerror(errno));
    }
    return w;
}

void cmd_redirect_output (char * cmd) {

}

void cmd_redirect_input (char * filename) {

}


