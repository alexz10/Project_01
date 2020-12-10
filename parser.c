#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#define BUFFER 1024

//Takes one command splits into an array of the command and its arguments
char ** parse_args( char * command ){
    char * s = command;
    char ** args = malloc(BUFFER);
    int i = 0;

    while(s) args[i++] = strsep(&s, " ");

    args[i] = NULL;
    return args;
}

//Reads one line from stdin and returns it
char * read_line(){
    char * arr = malloc(BUFFER);
    fgets(arr,BUFFER,stdin);
    return arr;
}


//Takes a line and splits it up into commands to be executed
char ** command_split(char * line){
    char * s = line;
    char ** commands = malloc(BUFFER);
    int i = 0;

    while(s) {
        commands[i] = strsep(&s, ";\n");
        i++;
    }

    commands[--i] = NULL;
    return commands;
}
