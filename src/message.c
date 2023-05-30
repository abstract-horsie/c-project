#include <stdlib.h>
#include <stdio.h>

#include "../lib/message.h"

void helpOutput() {
  printf("c-project is a small C program to create minimalist project templates\n");

  printf("\nOPTIONS:\n");

  printf("\tINIT:\n");
  printf("\t\t--no-makefile               - Don't create a Makefile\n");
  printf("\t\t--std {standard}            - Which C/C++ standard to use\n");
  printf("\t\t-n, --name 'NAME'           - Name of the project\n");
  printf("\t\t-d, --desc 'DESC'           - Description of the project\n");
  printf("\t\t-c, --create-vesrion M.m.P  - Description of the project\n");
  printf("\t\t-h                          - This help output\n");

  printf("\tEDIT:\n");

  printf("\tSTATUS:\n");

  printf("\nUSAGE:\n");
  printf("\tc-project init -n name -d 'long desc' -c 1.0.0\n");
}

void projectInfo(FILE *fp_project) {
  fprintf(fp_project, "// This is the c-project reallocation file\n");
  fprintf(fp_project, "// Changes are not recommended to this file\n");
  fprintf(fp_project, "/* ---------------- START ---------------- */\n");
}
