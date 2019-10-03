#include <stdio.h>
#include <stdlib.h>
#include "../include/bsh.h"
#include "../include/shell/shell.h"

void version()
{
  printf("bsh version %d.%d.%d\n", BSH_VERSION_MAJOR, BSH_VERSION_MINOR, BSH_VERSION_PATCH);
}

int main(int argc, char* argv[])
{
  version();

  loop();

  return EXIT_SUCCESS;
}