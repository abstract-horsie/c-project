/*! \file status.h
 *  \brief Contains functions used by C-Project "status" option.
 *
 *  Functions included in the file are for the "status" option and they are:
 *    - projectStatus(char *, char *, uint32_t *)
 */

#ifndef C_PROJECT_STATUS_H
#define C_PROJECT_STATUS_H

#include <inttypes.h>

/*! \fn void projectStatus(char *project_file, char *project_dir, uint32_t *size)
 *  \brief Prints out the status of the project.
 *
 *  \param project_file Path to the C-Project project file.
 *  \param project_dir Path to the C-Project project directory.
 *  \param size The size of the array.
 */
void projectStatus(char * project_file, char * project_dir);

#endif /* C_PROJECT_STATUS_H */
