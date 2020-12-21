## YES
by Jeremy Ku-benjet, Lucas Lee, Alex Zhang\
TNPG: Team Yes

## Features:

+ Reads commands found in the PATH and in the current directory with arguments
+ Chain multiple commands on one line with ;
+ Supports stdout (> and >>) stdin (<) redirection with one command and one file on command
+ Piping between two commands


## Attempted:
+ Chained piping


## Bugs:


## Files & Function Headers:

#### main.c
* Handles running the command prompt
```
/*======== int main() ==========
Inputs: Command line arguments
Returns: 0 on exit
Continuously runs the command prompt and calls helper functions until exit reached
====================*/
```

#### homebase.c
* Handles all the helper functions used for running the command prompt
```
/*======== int run_cmd() ==========
Inputs: char *cmd
Returns: 1 on successful execution, 0 on exit, -1 on failed execution
Takes a single command, scans for special redirection or piping symbols and
delegates it to helper functions accordingly
====================*/

/*======== void print_prompt() ==========
Inputs: None
Returns: None
Prints out the prompt for the shell including the working directory
====================*/

/*======== int redirect_file_descriptor() ==========
Inputs: int orignial_fd
        int new_fd
Returns: The placeholder file descriptor for the one that was overridden
Overrrides the original file descriptor with the inputted file descriptor
====================*/

/*======== int redirected_out_cmd() ==========
Input: char *cmd
       char append
Returns: 1 on success, -1 if the command fails or the file cannot be written to

[Description needed]
====================*/

/*======== int redirected_in_cmd() ==========
Input: char *cmd
Returns: 1 on success, -1 if the command fails or the file cannot be read from

[Description needed]
====================*/

/*======== int norm_cmd() ==========
+ int norm_cmd(char *cmd);
Input: char *cmd
Returns: Returns 1 on successful execution and 0 on exit
Handles the execution of commands with no pipes or redirections
====================*/
```

#### parser.c
* Handles all line parsing functions
```
/*======== char * read_line() ==========
Inputs: None
Returns: Line read from stdin
Reads a single line from stdin
====================*/

/*======== char ** command_split() ==========
Inputs: char * line
Returns: An array of commands to run
Splits the line into commands on semicolons
====================*/

/*======== char ** parse_args() ==========
Inputs: char * command
Returns: An array of the command and its arguments
Splits the command into an array of the executable and the arguments
====================*/

/*======== int check_symbol() ==========
+ int check_symbol (char * command);
Inputs: char * command
Returns: 1 if > is found
         2 if < is found
         3 if | is found,
         4 if >> is found
         0 if none are found
Detects special redirection and piping symbols
====================*/

/*======== char ** parse_symbol() ==========
[Check if accurate]

Inputs: char * command
        char * symbol
Returns: An array containing the executable with its arguments and the filename to be redirected
Searches the command for the symbol specified and returns an array of the executable with its
arguments and the filename to be redirected
====================*/

/*======== char ** parse_append() ==========
[Check if accurate]

Inputs: char * command
Returns: A pointer to the start of the file to redirect from or to
Searches the command for >> specified and returns the pointer to the filename that corresponds
to the one needed for redirection
====================*/

/*======== void trim_trailing() ==========
Inputs: char * str
Returns: None
Removes the trailing whitespace at the end of the string, if there is any
====================*
```

### extra_commands.c
* Handles any extra commands
```
/*======== int cmd_cd() ==========
Inputs: char ** args
Returns: 0 on success, otherwise -1
Changes the working directory of the shell
====================*
```
