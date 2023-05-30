#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>

#include "../lib/scan.h"

#ifndef RETURN_NAMES
  #define RETURN_NAMES  100
#endif
#ifndef RETURN_VALUES
  #define RETURN_VALUES 101
#endif

char **scanProjectFile(char *project_file, uint32_t *size, uint32_t what_to_return) {
  FILE *fp_project;
  fp_project = fopen(project_file, "r");
  printf("%s\n", project_file);

  char buffer[256];

  char **names;
  names = malloc(256 * sizeof(char *));

  char **values;
  values = malloc(256 * sizeof(char *));

  char container[256];
  int container_check = 0;

  char test_value[256];
  uint32_t index = 0;
  while (!feof(fp_project)) {
    if (fgets(buffer, 256, fp_project) != NULL) {
      if (sscanf(buffer, " %[/*]%*n", test_value) > 0) continue;

      if (sscanf(buffer, " %[>] %s", test_value, container) > 0) ++container_check;

      if (sscanf(buffer, " %[<]", test_value) > 0) --container_check;

      if (sscanf(buffer, " %[a-zA-Z_] = %[a-zA-Z0-9=/_. -]", test_value, test_value) > 1) {
        char *name = malloc(256 * sizeof(char) + 1);
        char *value = malloc(256 * sizeof(char) + 1);

        sscanf(buffer, " %[a-zA-Z_] = %[a-zA-Z0-9=/_. -]", name, value);
        names[index] = name;
        values[index] = value;
        ++index;
      }
      else continue;
    }
  }

  fclose(fp_project);

  if (container_check != 0)
    printf("Warning: Non-zero integer recevied for container closing");

  *size = index;

  if (what_to_return == RETURN_NAMES)
    return names;
  else if (what_to_return == RETURN_VALUES)
    return values;

  return NULL;
}

char **scanMakefile(char *makefile, uint32_t *size, uint32_t what_to_return) {
  FILE *fp_makefile;
  fp_makefile = fopen(makefile, "r");

  char buffer[256];

  char **names;
  names = malloc(256 * sizeof(char *));

  char **values;
  values = malloc(256 * sizeof(char *));

  char test_value[256];

  uint32_t index = 0;
  while (!feof(fp_makefile)) {
    if (fgets(buffer, 256, fp_makefile) != NULL) {
      if (sscanf(buffer, " %[a-zA-Z_] = %[a-zA-Z0-9=/_ -]", test_value, test_value) > 1) {
        char *name = malloc(256 * sizeof(char) + 1);
        char *value = malloc(256 * sizeof(char) + 1);

        sscanf(buffer, " %[a-zA-Z_] = %[a-zA-Z0-9=/_ -]", name, value);
        names[index] = name;
        values[index] = value;
        ++index;
      }
      else continue;
    }
  }

  fclose(fp_makefile);

  *size = index;

  if (what_to_return == RETURN_NAMES)
    return names;
  else if (what_to_return == RETURN_VALUES)
    return values;

  return NULL;
}

char **scanSourceDirectory(char **directory_content, uint32_t size) {
  char **content = directory_content;
  char **result = malloc(256 * sizeof(char *));

  char *tokenized_content;

  bool found_src;

  for (uint32_t i = 0; i < size; ++i) {
    found_src = false;

    tokenized_content = strtok(content[i], "/");
    while (tokenized_content != NULL) {
      tokenized_content = strtok(NULL, "/");

      if (found_src)
        break;

      if (strcmp(tokenized_content, "src") == 0)
        found_src = true;
    }

    if (found_src) {
      char *str;
      str = malloc((strlen("src/") + strlen(tokenized_content)) * sizeof(char) + 1);
      result[i] = malloc((strlen("src/") + strlen(tokenized_content)) * sizeof(char) + 1);

      strcpy(str, "src/");
      strcat(str, tokenized_content);
      strcpy(result[i], str);

      free(str);
    }

  }

  for (uint32_t i = 0; i < size; ++i) {
    printf("%d - %s\n", i, result[i]);
  }

  return result;
}

bool scanProjectForge(char *project_dir, char *project_file, char *file) {
  FILE *fp_project;
  fp_project = fopen(project_file, "r");

  if (fp_project == NULL)
    perror("File Error: ");

  char *buffer = (char *) malloc(256 * sizeof(char) + 1);
  char *container = (char *) malloc(256 * sizeof(char) + 1);

  char **array_of_forges = (char **) malloc(256 * sizeof(char) + 1);

  bool at_forge_container = false;

  char *test_value = (char *) malloc(256 * sizeof(char) + 1);
  uint32_t index = 0;
  while (!feof(fp_project)) {
    if (fgets(buffer, 256, fp_project) != NULL) {
      if (sscanf(buffer, " %[>] %s", test_value, container) > 1) {
        at_forge_container = true;
        continue;
      }

      if (at_forge_container) {
        if (sscanf(buffer, "%[<]", test_value) > 0) break;

        array_of_forges[index] = (char *) malloc(256 * sizeof(char) + 1);
        sscanf(buffer, " %s", test_value);
        strcpy(array_of_forges[index], project_dir);
        strcat(array_of_forges[index], test_value);

        ++index;
      }
    }
  }

  for (uint32_t i = 0; i < index; ++i)
    if (strcmp(array_of_forges[i], file) == 0)
      return true;

  return false;
}

void *pointerArrayTermination(char **pointer, uint32_t size) {
  for (uint32_t i = 0; i < size; ++i)
    free(pointer[i]);

  return pointer;
}

