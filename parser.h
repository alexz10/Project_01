#ifndef PARSER_H
#define PARSER_H

char ** parse_args(char * command);
char ** command_split(char * line);
char * read_line();

#endif
