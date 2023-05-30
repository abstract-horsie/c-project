#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include <dirent.h>

#include "../lib/dir.h"

bool isProjectCreated(char *directory) {
  uint32_t size;
  char **content = malloc(512 * sizeof(char));

  DIR *dir;
  struct dirent *ent;

  if ((dir = opendir(directory)) != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      if (strcmp(ent->d_name, ".c-project") == 0
          || strcmp(ent->d_name, ".c-project.d") == 0) {
        return true;
      }
    }
  }
  else {
    perror("Directory Error: ");
    return true;
  }

  return false;
}
