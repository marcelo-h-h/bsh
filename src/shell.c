#include "../include/shell/shell.h"

void loop()
{
  string_t line;
  string_t* args;
  string_t* tmp_arg;
  cmd_t* cmd;
  for (;;) {
    printf("$ ");
    line = get_line();
    args = split_line(line);
    cmd = parse_args(args);

    run_cmd(cmd);

    free(line);
    free(args);
  }
}

int run_cmd(cmd_t* cmd)
{
  switch (cmd->type) {
    case EXEC:
      return run_exec_cmd((exec_cmd_t*) cmd);
    case FORK:
      return run_fork_cmd((fork_cmd_t*) cmd);
    default:
      return EXIT_FAILURE;
  }
}

int run_exec_cmd(exec_cmd_t* cmd)
{
  pid_t pid;
  int status;

  pid = fork();

  if (pid < 0) {
    return EXIT_FAILURE;
  } else if (pid == 0) {
    if (execvp(cmd->argv[0], cmd->argv) != 0) {
      return EXIT_FAILURE;
    }
  } else {
    do {
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));

    return status;
  }
}

int run_fork_cmd(fork_cmd_t* cmd)
{
  pid_t pid;
  int status;
  exec_cmd_t* ecmd = (exec_cmd_t*) cmd->left;

  pid = fork();

  if (pid < 0) {
    return EXIT_FAILURE;
  } else if (pid == 0) {
    if (execvp(ecmd->argv[0], ecmd->argv) != 0) {
      return EXIT_FAILURE;
    }
  } else {
    printf("[%d] %d\n", 1, pid);

    return EXIT_SUCCESS;
  }
}
