#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>

#include "../lib/edit.h"
#include "../lib/find.h"

char *findProjectDirectory() {
  FILE *fp_project;
  bool project_file_found = false;

  char *directory;
  directory = malloc(256 * sizeof(char) + 1);

  char *searcher;

  uint32_t index = 0;
  while (!project_file_found) {
    searcher = malloc(256 * sizeof(char) + 1);
    strcpy(searcher, "");

    for (uint32_t i = 0; i < index; ++i) {
      strcat(searcher, "../");
    }
    if (strcmp(searcher, "") != 0) {
      sscanf(searcher, " %[./]", directory);
    }
    else {
      strcpy(directory, "./");
    }


    strcat(searcher, ".c-project");
    if ((fp_project = fopen(searcher, "r")) != NULL) {
      project_file_found = true;

      free(searcher);
      break;
    }

    if (index > 10) {
      free(searcher);
      break;
    }

    free(searcher);
    ++index;
  }

  if (project_file_found)
    printf("Found project directory\n");
  else
    printf("Couldn't find the project directory\n");

  return directory;
}

char *findProjectFile() {
  char *directory = findProjectDirectory();
  char *project_file = malloc(strlen(directory) + strlen(".c-project") * sizeof(char) + 1);
  strcpy(project_file, directory);
  strcat(project_file, ".c-project");

  FILE *fp_project_file = fopen(project_file, "r");
  if (fp_project_file == NULL) {
    printf("The project file couldn't be open\n");
    return NULL;
  }

  free(directory);
  return project_file;
}

char *findMakefile() {
  char *directory = findProjectDirectory();
  char *makefile = malloc((strlen(directory) + strlen("Makefile")) * sizeof(char) + 1);
  strcpy(makefile, directory);
  strcat(makefile, "Makefile");

  FILE *fp_makefile = fopen(makefile, "r");
  if (fp_makefile == NULL) {
    fclose(fp_makefile);
    free(makefile);

    makefile = (char *) malloc(strlen(directory) + strlen("makefile") * sizeof(char) + 1);
    strcpy(makefile, directory);
    strcat(makefile, "makefile");

    fp_makefile = fopen(makefile, "r");
    if (fp_makefile == NULL) {
      fclose(fp_makefile);
      free(makefile);

      printf("Couldn't open the makefile.\n");
      free(directory);
      return NULL;
    }
  }

  free(directory);
  return makefile;
}

