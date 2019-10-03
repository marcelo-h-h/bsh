#ifndef SHELL_PUBLIC
#define SHELL_PUBLIC

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../parser/parser.h"

void  loop();
int   run_cmd(cmd_t*);
int   run_exec_cmd(exec_cmd_t*);
int   run_fork_cmd(fork_cmd_t*);
int   check_builtins(string_t);
int   cd(string_t*);
int   exit_b(string_t*);

#endif