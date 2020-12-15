#ifndef PARSER_H
#define PARSER_H

char ** parse_args(char * command);
char ** command_split(char * line);
char *parse_io_symbol(char *command, char symb);
char * read_line();

#endif
