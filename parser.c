#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

//Takes one command splits into an array of the command and its arguments
char ** parse_args( char * command ){
    char * s = command;
    char ** args = malloc(256 * sizeof(char *));
    int i = 0;

    while(s) {
        args[i] = strsep(&s, " ");
        i++;
    }

    args[i] = NULL;
    return args;
}

//Reads one line from stdin and returns it
char * read_line(){
    char * arr = malloc(256 * sizeof(char));
    fgets(arr,sizeof(arr),stdin);
    return arr;
}


//Takes a line and splits it up into commands to be executed
char ** command_split(char * line){
    char * s = line;
    char ** commands = malloc(256 * sizeof(char *));
    int i = 0;

    while(s) {
        commands[i] = strsep(&s, ";");
        strcat(commands[i++], "\0");
    }

    commands[i] = NULL;
    return commands;
}
