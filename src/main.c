#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>

#include "../lib/option.h"
#include "../lib/message.h"
#include "../lib/create.h"
#include "../lib/find.h"
#include "../lib/scan.h"
#include "../lib/dir.h"
#include "../lib/edit.h"
#include "../lib/status.h"
#include "../lib/check.h"

int main(int argc, char *argv[]) {
  char *opt_std         = getOptionArg(argc, argv, "--std");
  char *opt_version     = getOptionArg(argc, argv, "-c");
  char *opt_name        = getOptionArg(argc, argv, "-n");
  char *opt_desc        = getOptionArg(argc, argv, "-d");
  char *opt_dir         = getOptionArg(argc, argv, "");

  bool opt_no_makefile  = scanOption(argc, argv, "--no-makefile");
  bool opt_help         = scanOption(argc, argv, "-h");

  bool cmd_init         = scanOption(argc, argv, "init");
  bool cmd_scan         = scanOption(argc, argv, "scan");
  bool cmd_edit         = scanOption(argc, argv, "edit");
  bool cmd_create       = scanOption(argc, argv, "create");
  bool cmd_status       = scanOption(argc, argv, "status");

  // If -c is not specified check if --create-version was specified
  if (opt_version == NULL) opt_version = getOptionArg(argc, argv, "--create-version");
  if (opt_name == NULL) opt_name = getOptionArg(argc, argv, "--name");
  if (opt_desc == NULL) opt_desc = getOptionArg(argc, argv, "--desc");

  // If -h was not specified check if --help was specified
  if (!opt_help) opt_help = scanOption(argc, argv, "--help");

  // If -h or --help was passed in trigger the help output.
  if (opt_help) {
    helpOutput();
    return EXIT_SUCCESS;
  }

  // For initializing the c-project with .c-project file, .c-project.d folder and optionally Makefile.
  if (cmd_init) {
    createProject(false, opt_no_makefile, opt_std, opt_version, opt_name, opt_desc, opt_dir);
  }
  // For creating a C/C++ Project
  else if (cmd_create) {
    createProject(true, opt_no_makefile, opt_std, opt_version, opt_name, opt_desc, opt_dir);
  }
  // For editing the .c-project file and Makefile.
  else if (cmd_edit) {
    char *project_file = findProjectFile();
    char *makefile = findMakefile();

    char *project_directory = findProjectDirectory();
    char *search_pattern = malloc((strlen(project_directory) + strlen("src/*.c")) * sizeof(char) + 1);
    strcpy(search_pattern, project_directory);
    strcat(search_pattern, "src/*.c");

    uint32_t directory_count;
    char **directory_content = getDirectoryContent(search_pattern, &directory_count);

    char **source_content = scanSourceDirectory(directory_content, directory_count);
    appendOption(project_file, makefile, source_content, directory_count);
    pointerArrayTermination(source_content, directory_count);
  }
  // For telling the user what files/folders are getting backed up.
  else if (cmd_status) {
    char *project_file = findProjectFile();
    char *project_directory = findProjectDirectory();

    projectStatus(project_file, project_directory);
  }

  /* RANDOM SHIT [ START ] */
  /* RANDOM SHIT [ END ] */

  isProjectCreated(".");

  printf("\n");
  printf("MAKEFILE >> %d\n", opt_no_makefile);
  printf("CXX_STD  >> %s\n", opt_std);

  return EXIT_SUCCESS;
}
