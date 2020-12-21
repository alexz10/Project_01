## YES
by Jeremy Ku-benjet, Lucas Lee, Alex Zhang\
TNPG: Team Yes

## Features:

+ Reads commands found in the PATH and in the current directory with arguments
+ Chain multiple commands on one line with ;
+ Supports stdout (> and >>) stdin (<) redirection with one command and one file on command


## Attempted:
+ Piping between programs


## Bugs:


## Files & Function Headers:

#### main.c
+ int main(int argc, char const *argv[]);
```
Inputs: Command line arguments, not used
Returns: 0 on exit
Continuously runs the command prompt and calls helper functions until exit reached
```

#### homebase.c
+ int run_cmd(char *cmd);
```
Inputs: A single command to run with no semicolons
Output: 1 on successful execution, 0 on exit, -1 on failed execution
Takes a single command, scans for special redirection or piping symbols and executes accordingly
```
+ void print_prompt();
```
Inputs: None
Outputs: None
Prints out the prompt for the shell including the working directory
```

#### parser.c
+ char * read_line();
```
Inputs: None
Output: Line read from stdin
Reads a single line from stdin
```
+ char ** command_split(char * line);
```
Inputs: A line read from stdin
Outputs: An array of commands to run
Splits the line into commands on semicolons
```
+ char ** parse_args(char * command);
```
Inputs: A single command with no semicolons
Outputs: An array of the command and its arguments
Splits the command into an array of the executable and the arguments
```
+ int check_symbol (char * command);
```
Inputs: A single command with no semicolons
Outputs: 1 if > is found, 2 if < is found, 3 if | is found, 4 if >> is found, 0 if none are found
Detects special redirection and piping symbols
```
+ char ** parse_symbol (char * command, char * symbol);
```
Inputs: A command containing < or >, and a string containing the one to look for
Output: A pointer to the start of the file to redirect from or to
Searches the command for the symbol specified and returns the pointer to the filename that corresponds to the one needed for redirection
```
+ char ** parse_append(char * command);
```
Inputs: A single command containing >>
Outputs:  A pointer to the start of the file to redirect from or to
Searches the command for >> specified and returns the pointer to the filename that corresponds to the one needed for redirection
```
+ void trim_trailing(char * str);
```
Inputs: A pointer to a filename
Outputs: None
Removes the trailing whitespace at the end of the filename, if there is any

```

### extra_commands.c
+ int cmd_cd(char **args);
```
Inputs: The arguments used for the cd command
Ouputs: 0 on success, otherwise -1
Changes the working director of the shell
```
