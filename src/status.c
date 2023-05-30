#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <stdbool.h>

#include "../lib/status.h"
#include "../lib/dir.h"
#include "../lib/scan.h"

void projectStatus(char *project_file, char *project_dir) {
  FILE *fp_project;
  fp_project = fopen(project_file, "r");

  if (fp_project == NULL) {
    perror("File Error: ");
  }

  char *buffer = malloc(256 * sizeof(char) + 1);
  char *folder = malloc(256 * sizeof(char) + 1);
  char *container = malloc(256 * sizeof(char) + 1);
  char **folders_to_check = malloc(128 * sizeof(char) + 1);

  bool at_folder_structure = false;
  char *test_value = malloc(256 * sizeof(char) + 1);
  uint32_t index = 0;
  while (!feof(fp_project)) {
    if (fgets(buffer, 256, fp_project) != NULL) {
      // TODO: PUT THE "at_folder_structure" CHECK HERE.
      if (sscanf(buffer, " %[>] %s", test_value, container) > 0) {
        if (strcmp(container, "FOLDER_STRUCTURE") == 0) {
          at_folder_structure = true;
          continue;
        }
      }

      if (at_folder_structure) {
        if (sscanf(buffer, " %[<]", test_value)) break;

        folders_to_check[index] = malloc(256 * sizeof(char) + 1);
        strcpy(folders_to_check[index], project_dir);
        sscanf(buffer, " %s", folder);
        strcat(folders_to_check[index], folder);
        strcat(folders_to_check[index], "*");

        ++index;
      }
    }
  }

  uint32_t *counts = malloc(256 * sizeof(uint32_t));
  char ***array_of_content = malloc(256 * sizeof(char **));

  for (uint32_t i = 0; i < index; ++i) {
    array_of_content[i] = malloc(512 * sizeof(char *));
    array_of_content[i] = getDirectoryContent(folders_to_check[i], &counts[i]);
  }

  for (uint32_t i = 0; i < index; ++i) {
    for (uint32_t j = 0; j < counts[i]; ++j) {
      printf("==> %s", array_of_content[i][j]);
      if (scanProjectForge(project_dir, project_file, (char *)array_of_content[i][j])) {
        printf(" \033[1;31mFORGED \033[0m\n");
      }
      else printf("\n");
    }
  }
}
