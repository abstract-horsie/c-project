/*! \file edit.h
 *  \brief Contains functions for editing files and directories.
 *
 *  This file has funtions for editing/appending to files and directories these files are:
 *    - .c-project
 *    - Makefile
 *    - .c-project.d
 *
 *  Macros defined are:
 *    - APPEND_SUCCESSFUL
 *    - APPEND_UNSUCCESSFUL
 *
 *  The macros are returned by functions inside of this file for the result of the operation.
 *
 *  Functions defined are:
 *    - appendOption(char *, char *, char **, uint32_t)
 *
 *  The functions return either APPEND_SUCCESSFUL or APPEND_UNSUCCESSFUL and are used for editing/appending strings into files.
 *
 */

#ifndef C_PROJECT_EDIT_H
#define C_PROJECT_EDIT_H

#include <inttypes.h>

/*! \def APPEND_SUCCESSFUL
 *  \brief returned value for a successful appending.
 *
 *  This macro is used by functions inside of edit.(c/h)(This file)
 */
#ifndef APPEND_SUCCESSFUL
  #define APPEND_SUCCESSFUL   200
#endif

/*! \def APPEND_UNSUCCESSFUL
 *  \brief returned value for a unsuccessful appending.
 *
 *  This macro is used by functions inside of edit.(c/h)(This file)
 */
#ifndef APPEND_UNSUCCESSFUL
  #define APPEND_UNSUCCESSFUL 500
#endif

/*! \fn appendOption(char *project_file, char *makefile, char **what_to_append, uint32_t size)
 *  \brief Appends options/variables to the project file and the makefile.
 *
 *  \param project_file Path to the project file.
 *  \param makefile Path to the project Makefile.
 *  \param what_to_append The array of items to append.
 *  \param size Size of the append array.
 *
 *  \return if successful APPEND_SUCCESSFUL and APPEND_UNSUCCESSFUL if unsuccessful.
 */
uint32_t appendOption(char *project_file, char *makefile, char **what_to_append, uint32_t size);

#endif
