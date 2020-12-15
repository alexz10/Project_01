#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <ctype.h>

#define BUFFER 1024

//Takes one command splits into an array of the command and its arguments
char ** parse_args( char * command ){
    char * s = command;
    char ** args = malloc(BUFFER);
    int i = 0;

    while(*s == ' ') s++; //get rid of leading spaces
    while(s) {
        char * t = strsep(&s, " ");
        if (*t) args[i++] = t; //in case of extra spaces in the command
    }

    args[i] = NULL;
    char *tp = strrchr(args[i-1], '\n'); //removes trailing newline
    if(tp) *tp = '\0';

    return args;
}

//returns NMULL if symb not found, else returns pointer to first non-whitespace character following the given symbol
//UNTESTED
char *parse_io_symbol(char *command, char symb) {
    char *arrowp = strrchr(command, symb);
    if(!arrowp) {
        return NULL;
    }

    arrowp++; 
    while(isspace(*arrowp)) {
        arrowp++;
    }

    return arrowp;
}

//Reads one line from stdin and returns it
char * read_line(){
    char * arr = malloc(BUFFER);
    fgets(arr,BUFFER,stdin);

    return arr;
}


//Takes a line and splits it up into commands to be executed, the list is null terminated
char ** command_split(char * line){
    //note the possibole overflow here if the commands+1 are >= BUFFER
    char * s = line;
    char ** commands = malloc(BUFFER);
    char ** cmdp = commands;

    while(s) {
        *(cmdp++) = strsep(&s, ";");
    }

    *cmdp = NULL; //make the list null terminating

    return commands;
}
