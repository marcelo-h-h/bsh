#include <stdio.h>
#include <stdlib.h>
#include "../include/bsh.h"
#include "../include/parser/parser.h"

void version()
{
  printf("bsh version %d.%d.%d\n", BSH_VERSION_MAJOR, BSH_VERSION_MINOR, BSH_VERSION_PATCH);
}

int main(int argc, char* argv[])
{
  printf("~ We have to start somewhere ~\n");
  version();

  string_t line = get_line();
  string_t* args = split_line(line);
  cmd_t* cmd = parse_args(args);

  printf("%d\n", cmd->type);

  return EXIT_SUCCESS;
}