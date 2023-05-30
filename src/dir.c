#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>
#include <unistd.h>
#include <sys/stat.h>
#include <glob.h>

#include "../lib/dir.h"

char **getDirectoryContent(char *directory, uint32_t *count) {
  glob_t glob_r;
  int glob_return = glob(directory, GLOB_NOSORT | GLOB_ERR, NULL, &glob_r);
  printf("dir.c - %d\n", glob_return);

  switch (glob_return) {
    case GLOB_NOSPACE:
      perror("\033[1;31m==> Error\033[0m");
      exit(EXIT_FAILURE);
      break;
    case GLOB_ABORTED:
      perror("\033[1;31m==> Error\033[0m");
      exit(EXIT_FAILURE);
      break;
    case -1:
      perror("\033[1;31m==> Error\033[0m");
      exit(EXIT_FAILURE);
      break;

    default:
      ;
  }

  *count = glob_r.gl_pathc;

  return glob_r.gl_pathv;
}

bool isDir(char *dir) {
  struct stat stats;

  if (stat(dir, &stats) == 0) {
    return true;
  }

  return false;
}
