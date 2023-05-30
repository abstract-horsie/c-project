/*! \file message.h
 *  \brief Contains message functions.
 *
 *  Functions inside of this file prints out messages.
 *
 *  Functions included:
 *    - helpOutput()
 *    - projectInfo(FILE *)
 */

#ifndef C_PROJECT_MESSAGE_H
#define C_PROJECT_MESSAGE_H

#include <stdio.h>

/*! \fn void helpOutput()
 *  \brief Help output of C-Project.
 */
void helpOutput();

/*! \fn void projectInfo(FILE *fp_project)
 *  \brief Prints into the file the beginning of the .c-project file.
 *
 *  \param fp_project File to print the beginning to.
 */
void projectInfo(FILE *fp_project);

#endif /* C_PROJECT_MESSAGE_H */
