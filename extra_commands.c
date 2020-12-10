#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

//returns 0 on sucess else -1, changes cwd
int cmd_cd(char **args) {
    if(!args[1]) {
        printf("No such file or directory\n");
        return -1;
    }

    int w = chdir(args[1]);
    if(w == -1) {
        printf("%s\n",strerror(errno));
    }
    return w;
}


