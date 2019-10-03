#include "../include/shell/shell.h"

const string_t builtin_str[] = {
  "cd",
  "exit",
  NULL
};

const void* builtin_func[] = {
  &cd,
  &exit_b
};

int check_children()
{
  int status;
  int ret;

  do {
    ret = waitpid(-1, &status, WNOHANG);

    if (ret > 0) {
      printf("[%d]+ Concluído\t%d\n", 1, ret);
    }
  } while (ret > 0);

  return status;
}

void loop()
{
  string_t line;
  string_t* args;
  string_t* tmp_arg;
  cmd_t* cmd;
  int status;

  for (;;) {
    status = check_children();
    printf("$ ");
    line = get_line();
    args = split_line(line);
    cmd = parse_args(args);

    status = run_cmd(cmd);

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
  int (*f)(string_t*);
  int i = check_builtins(cmd->argv[0]);

  if (i >= 0) {
    f = builtin_func[i];
    return f(cmd->argv);
  }

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

int check_builtins(string_t cmd)
{
  int i = 0;
  while (builtin_str[i] != NULL) {
    if (strcmp(cmd, builtin_str[i]) == 0) {
      return i;
    }

    i++;
  }

  return -1;
}

int cd(string_t* args)
{
  return chdir(args[1]);
}

int exit_b(string_t* args)
{
  exit(atoi(args[1]));
}
