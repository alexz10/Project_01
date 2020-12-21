#ifndef HOMEBASE_H
#define HOMEBASE_H
int run_cmd(char *cmd);
void print_prompt();
int norm_cmd(char *cmd);
int redirect_file_descriptor(int original_fd, int new_fd);
int redirected_out_cmd(char *cmd, char append);
int redirected_in_cmd(char *cmd);
int exec_piped_commands(char *cmd);
#endif
