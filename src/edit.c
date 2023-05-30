#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "../lib/edit.h"

#ifndef APPEND_SUCCESSFUL
  #define APPEND_SUCCESSFUL   200
#endif
#ifndef APPEND_UNSUCCESSFUL
  #define APPEND_UNSUCCESSFUL 500
#endif

uint32_t appendOption(char *project_file, char *makefile, char **what_to_append, uint32_t count) {
  FILE *fp_project;
  FILE *fp_temp;
  fp_project = fopen(project_file, "r");
  fp_temp = fopen(".temp-project-file", "w");

  if (fp_project == NULL || fp_temp == NULL) {
    fclose(fp_project);
    fclose(fp_temp);

    return APPEND_UNSUCCESSFUL;
  }

  char *buffer;
  buffer = malloc(256 * sizeof(char) + 1);

  char *append_content;
  append_content = malloc(512 * sizeof(char) + 1);
  strcpy(append_content, "");
  for (uint32_t i = 0; i < count; ++i) {
    strcat(append_content, what_to_append[i]);
    strcat(append_content, ";");
  }

  /* printf("|> %s\n", append_content); */

  char test_value[256];
  while (!feof(fp_project)) {
    if (fgets(buffer, 256, fp_project) != NULL) {
      if (sscanf(buffer, " %[a-zA-Z_] = %[a-zA-Z0-9=/_;-]", test_value, test_value) > 1) {
        char *name = malloc(256 * sizeof(char) + 1);
        char *value = malloc(256 * sizeof(char) + 1);

        sscanf(buffer, " %[a-zA-Z_] = %[a-zA-Z0-9=/_;-]", name, value);
        if (strcmp(name, "BUILD_FILES") == 0) {
          fprintf(fp_temp, "\t\tBUILD_FILES = %s\n", append_content);
          free(name);
          free(value);
          continue;
        }
      }

      fprintf(fp_temp, "%s", buffer);
    }
  }

  remove(project_file);
  rename(".temp-project-file", project_file);

  fclose(fp_project);
  fclose(fp_temp);

  // Appending to Makefile.
  FILE *fp_makefile;
  fp_makefile = fopen(makefile, "r");
  fp_temp = fopen(".temp-makefile", "w");

  strcpy(append_content, "");
  for (uint32_t i = 0; i < count; ++i) {
    strcat(append_content, what_to_append[i]);
    strcat(append_content, " ");
  }

  while (!feof(fp_makefile)) {
    if (fgets(buffer, 256, fp_makefile) != NULL) {
      if (sscanf(buffer, " %[a-zA-Z_] = %[a-zA-Z0-9=/_ -]", test_value, test_value) > 1) {
        char *name = malloc(256 * sizeof(char) + 1);
        char *value = malloc(256 * sizeof(char) + 1);

        sscanf(buffer, " %[a-zA-Z_] = %[a-zA-Z0-9=/_ -]", name, value);
        if (strcmp(name, "BUILD_FILES") == 0) {
          fprintf(fp_temp, "BUILD_FILES = %s\n", append_content);
          free(name);
          free(value);
          continue;
        }
      }

      fprintf(fp_temp, "%s", buffer);
    }
  }

  return APPEND_SUCCESSFUL;
}
