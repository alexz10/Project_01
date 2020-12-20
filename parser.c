#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <ctype.h>

#define BUFFER 1024

//Reads one line from stdin and returns it
char * read_line() {
    char * arr = malloc(BUFFER);
    fgets(arr,BUFFER,stdin);

    return arr;
}

//Takes a line and splits it up into commands to be executed, the list is null terminated
char ** command_split(char * line) {
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

//Takes one command splits into an array of the command and its arguments
char ** parse_args( char * command ) {
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

//Checks what symbol is present in the command
int check_symbol (char * command) {

	if (strchr(command, '>')) return 1;
	if (strchr(command, '<')) return 2;
	if (strchr(command, '|')) return 3; //For piping

	return 0;
}

//Return a char ** for an array split on the symbol
char ** parse_symbol (char * command, char * symbol) {

    char * s = command;
    char ** args = malloc(BUFFER);
    int i = 0;

    while(*s == ' ') s++; //get rid of leading spaces
    while(s) {
        char * t = strsep(&s, symbol);
        if (*t) args[i++] = t; //in case of extra spaces in the command
    }

    args[i] = NULL;
    char *tp = strrchr(args[i-1], '\n'); //removes trailing newline
    if(tp) *tp = '\0';

    return args;
}

//Trims the trailing white spaces
void trim_trailing(char * str) {

    int index, i;
    
    index = -1;

    i = 0;
    while(str[i])
    {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            index= i;
        }

        i++;
    }

    str[index + 1] = '\0';
}
