/*! \file dir.h
 *  \brief Contains functions for directory based operations
 *
 *  This file contains functions for directory based operations.
 *
 *  The included funtions are:
 *    - getDirectoryContent(char *, uint32_t *)
 *
 *  "getDirectoryContent" gets content of the specified directory.
 */

#ifndef C_PROJECT_DIR_H
#define C_PROJECT_DIR_H

#include <inttypes.h>
#include <stdbool.h>

/*! \fn char **getDirectoryContent(char *directory, uint32_t *count)
 *  \brief Gets the Content of the Directory and returns it
 *  
 *  \param directory The directory to get the content of.
 *  \param count Assignes the parameter to the size of the array
 */
char **getDirectoryContent(char *directory, uint32_t *size);

bool isDir(char *dir);

#endif /* C_PROJECT_DIR_H */
