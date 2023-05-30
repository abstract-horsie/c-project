/*! \file find.h
 *  \brief Contains functions for finding specific files/directories.
 *
 *  This file contains functions for finding files/directories like:
 *    - C-Project project directory
 *    - .c-project
 *    - Makefile
 *
 *  Each of them return the location/path to the files/directories.
 */

#ifndef C_PROJECT_FIND_H
#define C_PROJECT_FIND_H

/*! \fn char *findProjectDirectory()
 *  \brief Searches for the C-Project project directory.
 *
 *  \return Path to the directory.
 */
char * findProjectDirectory();

/*! \fn char *findProjectDirectory()
 *  \brief Searches for the C-Project project file.
 *
 *  \return Path to the C-Project project file.
 */
char * findProjectFile();

/*! \fn char *findMakefile()
 *  \brief Searches for the project Makefile.
 *
 *  \return Path to the project Makefile.
 */
char * findMakefile();

#endif /* C_PROJECT_FIND_H */
