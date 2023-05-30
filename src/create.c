#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>
#include <sys/stat.h>

#include "../lib/create.h"
#include "../lib/message.h"
#include "../lib/check.h"

uint32_t createProject(bool opt_create, bool opt_no_makefile, char *opt_std,
                      char *opt_version, char *opt_name, char *opt_desc,
                      char *opt_dir) {
  if (opt_dir == NULL) opt_dir = "./";

  if (isProjectCreated(opt_dir) == true) {
    printf("%s\n", opt_dir);
    printf("\033[1;31mError: \033[0mProject already exists. Exiting...\n");
    exit(EXIT_FAILURE);
  }

  if (opt_std == NULL) opt_std = "c99";
  if (opt_name == NULL) opt_name = "name_template (replace)";
  if (opt_desc == NULL) opt_desc = "description_template (replace)";
  if (opt_version == NULL) opt_version = "1.0.0";

  char *project_file_loc = malloc(strlen(opt_dir) + 12);
  strcpy(project_file_loc, opt_dir);
  strcat(project_file_loc, "/.c-project");

  FILE *fp_project;
  fp_project = fopen(project_file_loc, "w");
  free(project_file_loc);

  uint32_t version = createVersion(opt_version);

  createCProjectDirectory(opt_dir, opt_name, opt_desc, version);

  projectInfo(fp_project);
  fprintf(fp_project, "> PROJECT\n");
  fprintf(fp_project, "\tLANGUAGE = %s\n", "C");

  if (!opt_no_makefile) {
    fprintf(fp_project, "\t>> MAKEFILE\n");
    char *cflags = malloc(sizeof(opt_std) + sizeof("CFLAGS = -std=") + 1);
    strcpy(cflags, "CFLAGS = -std=");
    strcat(cflags, opt_std);

    char *build_files = "src/main.c";
    char *executable = "bin/name";

    if (createMakefile(opt_dir, cflags) == EXIT_FAILURE) {
      fclose(fp_project);
      free(cflags);
      return EXIT_FAILURE;
    }

    fprintf(fp_project, "\t\t%s\n", cflags);
    fprintf(fp_project, "\t\tBUILD_FILES = %s\n", build_files);
    fprintf(fp_project, "\t\tEXECUTABLE = %s\n", executable);
    fprintf(fp_project, "\t<<\n");

    free(cflags);
  }

  fprintf(fp_project, "\t>> BACKUP\n");
  fprintf(fp_project, "\t<<\n");

  fprintf(fp_project, "\t%s\n", ">> FOLDER_STRUCTURE");
  fprintf(fp_project, "\t\t%s\n", "src/");
  fprintf(fp_project, "\t\t%s\n", "lib/");
  fprintf(fp_project, "\t<<\n");
  /* printf("%d\n", fscanf(fp_project, "%s", "> PROJECT")); */

  fprintf(fp_project, "<\n");
  fclose(fp_project);

  if (opt_create) createFullProject(opt_dir);

  return EXIT_SUCCESS;
}

uint32_t createMakefile(char *dir, char *cflags) {
  FILE *fp_makefile;

  char *makefile_loc = malloc(strlen(dir) + 10);
  strcpy(makefile_loc, dir);
  strcat(makefile_loc, "/Makefile");

  fp_makefile = fopen(makefile_loc, "w");
  free(makefile_loc);

  if (fp_makefile == NULL) {
    fclose(fp_makefile);
    return EXIT_FAILURE;
  }

  fprintf(fp_makefile, "# MAKEFILE \\\n");
  fprintf(fp_makefile, "\t# Changes to this file are not recommended. \\\n");
  fprintf(fp_makefile, "\t# As this file will get overriden if 'c-project edit' is ran.\\\n");
  fprintf(fp_makefile, "\t# If you decided to delete the `c-project` file and directory, then feel free to edit.\n\n");

  fprintf(fp_makefile, "%s\n", cflags);
  fprintf(fp_makefile, "BUILD_FILES = %s\n", "src/main.c");
  fprintf(fp_makefile, "EXECUTABLE = %s\n\n", "bin/name");
  fprintf(fp_makefile, "main: $(BUILD_FILES)\n");
  fprintf(fp_makefile, "\tclang $(CFLAGS) $(BUILD_FILES) -o $(EXECUTABLE)\n\n");
  fprintf(fp_makefile, ".PHONY: test clean\n\n");
  fprintf(fp_makefile, "clean: %s\n", "bin/name");
  fprintf(fp_makefile, "\trm -f %s\n\n", "bin/name");
  fprintf(fp_makefile, "test: %s\n", "bin/name");
  fprintf(fp_makefile, "\t./%s\n", "bin/name");

  fclose(fp_makefile);

  return EXIT_SUCCESS;
}

uint32_t createVersion(char *opt_version) {
  uint32_t major;
  uint32_t minor;
  uint32_t patch;

  if (sscanf(opt_version, "%u.%u.%u", &major, &minor, &patch) < 1) {
    printf("Option Error: -c should be specified by '.' devided version (Ex: 1.0.0)\n");
    exit(EXIT_FAILURE);
  }

  return C_PROJECT_MAKE_VERSION(major, minor, patch);
}

uint32_t createCProjectDirectory(char *dir, char *name, char *description, uint32_t version) {
  FILE * fp;

  char *project_dir = malloc(strlen(dir) + 14);
  strcpy(project_dir, dir);
  strcat(project_dir, "/.c-project.d/");

  if (mkdir(project_dir, 0700) != 0) {
    perror("Error: ");
    return EXIT_FAILURE;
  }

  char *name_loc = malloc(strlen(project_dir) + 6);
  strcpy(name_loc, project_dir);
  strcat(name_loc, "/name");

  if ((fp = fopen(name_loc, "w")) == NULL) {
    printf("File error: countn't open .c-project.d/name");
    return EXIT_FAILURE;
  }
  fprintf(fp, "%s\n", name);
  fclose(fp);

  free(name_loc);

  char *desc_loc = malloc(strlen(project_dir) + 13);
  strcpy(desc_loc, project_dir);
  strcat(desc_loc, "/description");

  if ((fp = fopen(desc_loc, "w")) == NULL) {
    printf("File error: countn't open .c-project.d/description");
    return EXIT_FAILURE;
  }
  fprintf(fp, "%s\n", description);
  fclose(fp);

  free(desc_loc);

  char *version_loc = malloc(strlen(project_dir) + 9);
  strcpy(version_loc, project_dir);
  strcat(version_loc, "/version");

  if ((fp = fopen(version_loc, "w")) == NULL) {
    printf("File error: countn't open .c-project.d/version");
    return EXIT_FAILURE;
  }
  fprintf(fp, "%u\n", version);
  fclose(fp);

  free(version_loc);
  free(project_dir);

  return EXIT_SUCCESS;
}

uint32_t createFullProject(char *dir) {
  char *dir_src = malloc(strlen(dir) + 6);
  strcpy(dir_src, dir);
  strcat(dir_src, "/src/");

  char *dir_lib = malloc(strlen(dir) + 6);
  strcpy(dir_lib, dir);
  strcat(dir_lib, "/lib/");

  char *dir_bin = malloc(strlen(dir) + 6);
  strcpy(dir_bin, dir);
  strcat(dir_bin, "/bin/");

  if (mkdir(dir_src, 0700) != 0) return EXIT_FAILURE;
  if (mkdir(dir_lib, 0700) != 0) return EXIT_FAILURE;
  if (mkdir(dir_bin, 0700) != 0) return EXIT_FAILURE;

  free(dir_lib);
  free(dir_bin);

  char *main_file = malloc(strlen(dir_src) + 8);
  strcpy(main_file, dir_src);
  strcat(main_file, "/main.c");
  FILE *fp;
  if ((fp = fopen(main_file, "w")) == NULL) return EXIT_FAILURE;

  fprintf(fp, "#include <stdlib.h>\n");
  fprintf(fp, "#include <stdio.h>\n\n");
  fprintf(fp, "int main(int argc, char *argv[]) {\n\n");
  fprintf(fp, "}\n");

  free(main_file);
  free(dir_src);

  fclose(fp);
  return EXIT_SUCCESS;
}
