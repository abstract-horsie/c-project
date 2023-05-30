#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>

#include "../lib/option.h"
#include "../lib/dir.h"

char *getOptionArg(int argc, char *argv[], char *option) {
  if (strcmp(option, "") == 0) {
    for (uint32_t i = 0; i < argc; ++i) {
      if (argv[i][0] == '-') {
        continue;
      }
      else {
        if (isDir(argv[i]) == true) return argv[i];
      }
    }
  }
  else {
    for (uint32_t i = 0; i < argc; ++i) {
      if (strcmp(argv[i], option) == 0) {
        return argv[i + 1];
      }
    }
  }

  return NULL;
}

bool scanOption(int argc, char *argv[], char *option) {
  for (uint32_t i = 0; i < argc; ++i) {
    if (strcmp(argv[i], option) == 0) {
      return true;
    }
  }
  
  return false;
}

