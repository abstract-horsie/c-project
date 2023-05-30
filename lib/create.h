/*! \file create.h
 *  \brief Contains functions for C-Project project creation.
 *
 *  This file(create.h) containes functions to create project with C-Project.
 *
 *  The main function for C-Project project creation is the "createProject" function.
 *
 *  But it uses couple "sub-functions" like:
 *    - createMakefile(char *cflags)
 *    - createVersion(char *option_create_version)
 *
 *  Macros inside of this file is:
 *    - C_PROJECT_MAKE_VERSION(major, minor, patch)
 *    - C_PROJECT_MAJOR(version)
 *    - C_PROJECT_MINOR(version)
 *    - C_PROJECT_PATCH(version)
 *
 *  C_PROJECT_MAKE_VERSION creates a encoded version with bitwise shifts.
 *  It also uses Semantic Versioning(SemVer), please learn SemVer and use it correctly.
 *
 *  The functions like C_PROJECT_MAJOR, MINOR or PATCH decode the version created with the "C_PROJECT_MAKE_VERSION".
 */

#ifndef C_PROJECT_CREATE_H
#define C_PROJECT_CREATE_H

#include <inttypes.h>

/*! \def C_PROJECT_MAKE_VERSION(major, minor, patch)
 *  \brief Create a encoded version with bitwise shifts.
 *
 *  C_PROJECT_MAKE_VERSION creates a encoded version with bitwise shifts.
 *  This function is also taken from the Vulkan API's VK_MAKE_VERSION, I liked the values that it generates.
 *  \param major Major version of the project.
 *  \param minor Minor version of the project.
 *  \param patch Patch version of the project.
 *
 *  It also follows the Semantic Versioning(SemVer), Learn it please.
 *
 *  \return The encoded version.
 */
#define \
  C_PROJECT_MAKE_VERSION(major, minor, patch) \
    ((((uint32_t)(major)) << 22) | (((uint32_t)(minor)) << 12) | ((uint32_t)(patch)))

/*! \def C_PROJECT_MAJOR(version)
 *  \brief Decodes C_PROJECT_MAKE_VERSION version.
 *
 *  \param version Version created with C_PROJECT_MAKE_VERSION.
 *
 *  \return Major version.
 */
#define \
  C_PROJECT_MAJOR(version) \
    ((uint32_t)(version) >> 22)

/*! \def C_PROJECT_MINOR(version)
 *  \brief Decodes C_PROJECT_MAKE_VERSION version.
 *
 *  \param version Version created with C_PROJECT_MAKE_VERSION.
 *
 *  \return Minor version.
 */
#define \
  C_PROJECT_MINOR(version) \
    (((uint32_t)(version) - (((uint32_t)(version) >> 22) << 22)) >> 12)

/*! \def C_PROJECT_PATCH(version)
 *  \brief Decodes C_PROJECT_MAKE_VERSION version.
 *
 *  \param version Version created with C_PROJECT_MAKE_VERSION.
 *
 *  \return Patch version.
 */
#define \
  C_PROJECT_PATCH(version) \
    ((uint32_t)(version) - (((uint32_t)(version) >> 22) << 22) - ((((uint32_t)(version) - (((uint32_t)(version) >> 22) << 22)) >> 12) << 12))

/*! \fn int createProject(bool option_no_makefile, char *std, char *option_create_version, char *option_name, char *option_description);
 *  \brief The main function that create the C-Project project.
 *
 *  \param option_no_makefile Option can be passed with "--no-makefile", if TRUE doesn't create the Makefile.
 *  \param std Option can be passed with "--std STANDARD" and creates a project with the specified STANDARD.
 *
 *  \return EXIT_SUCCESS if the creation was successful and EXIT_FAILURE if the creation failed.
 */
uint32_t createProject(bool opt_create, bool opt_no_makefile, char *std,
                      char *opt_version, char *opt_name, char *opt_desc,
                      char *opt_dir);

/*! \fn uint32_t createVersion(char *option_create_version)
 *  \brief The function responsible for creating the C-Project version.
 *
 *  \param option_create_version Option can be passed with "-c X.Y.Z" and creates a random number with C_PROJECT_MAKE_VERSION.
 *
 *  \return The encoded version.
 */
uint32_t createMakefile(char *dir, char *cflags);

/*! \fn int createMakefile(char *cflags)
 *  \brief The functions for creating the C-Project Makefile.
 *
 *  \param cflags What to use in the Makefile CFLAGS.
 *
 *  \return EXIT_SUCCESS if the creation successful and EXIT_FAILURE if the creation failed.
 */
uint32_t createVersion(char *option_create_version);

uint32_t createCProjectDirectory(char *dir, char *name, char *description, uint32_t version);
uint32_t createFullProject(char *dir);

#endif /* C_PROJECT_CREATE_H */
