#ifndef PARSER_H
#define PARSER_H

char * read_line();
char ** command_split(char * line);
char ** parse_args(char * command);
int check_symbol (char * command);
char ** parse_symbol (char * command, char * symbol);
void trim_trailing(char * str);

#endif
