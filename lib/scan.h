/*! \file scan.h
 *  \brief Contains functions to scan C-Project files.
 *
 *  This header file is for scanning through files and directories:
 *    - .c-project
 *    - Makefile
 *    - .c-project.d/
 *
 *  Also has two macros:
 *    - C_PROJECT_RETURN_NAMES
 *    - C_PROJECT_RETURN_VALUES
 *  They are for functions with "uint32_t return" to return arrays of names or values.
 *
 *  The NAMES and VALUES arrays are like JSON files:
 *    {
 *      "name1": "value1",
 *      "name2": "value2",
 *      "name3": "value3"
 *    }
 *  
 *  As the NAMES and VALUES array would be:
 *    NAMES[0] == "name1";
 *    NAMES[1] == "name2";
 *    NAMES[2] == "name3";
 *
 *    VALUES[0] == "value1";
 *    VALUES[1] == "value2";
 *    VALUES[2] == "value3";
 */

#ifndef C_PROJECT_SCAN_H
#define C_PROJECT_SCAN_H

#include <inttypes.h>

/*! \def C_PROJECT_RETURN_NAMES
 *  \brief Macro for C-Project scan functions to return name array.
 *
 *  C_PROJECT_RETURN_NAMES macro is used for functions like:
 *    - scanProjectFile()
 *    - scanMakefile()
 *
 *  It tells the functions to return NAMES array.
 */
#ifndef C_PROJECT_RETURN_NAMES
  #define C_PROJECT_RETURN_NAMES 100
#endif

/*! \def C_PROJECT_RETURN_VALUES
 *  \brief Macro for C-Project scan functions to return value array.
 *
 *  C_PROJECT_RETURN_VALUES macro is used for functions like:
 *    - scanProjectFile()
 *    - scanMakefile()
 *
 *  It tells the functions to return VALUES array.
 */
#ifndef C_PROJECT_RETURN_VALUES
  #define C_PROJECT_RETURN_VALUES 101
#endif

/*! \fn char **scanProjectFile(char *project_file, uint32_t *size, uint32_t return);
 *  \brief Scans the Project File for variables.
 *
 *  \param project_file The path to the project file.
 *  \param size The size of the returned array.
 *  \param return What the function should return.
 *
 *  \return Array of either names or values.
 */
char **scanProjectFile(char *project_file, uint32_t *size, uint32_t what_to_return);

/*! \fn char **scanMakefile(char *makefile, uint32_t *size, uint32_t return);
 *  \brief Scans the Project File for variables.
 *
 *  \param makefile The path to the 'PROJECT' Makefile.
 *  \param size The size of the returned array.
 *  \param return What the function should return.
 *
 *  \return Array of either names or values.
 */
char **scanMakefile(char *makefile, uint32_t *size, uint32_t what_to_return);

/*! \fn char **scanSourceDirectory(char ** directory_content, uint32_t size)
 *  \brief Scans src/ directory for CXX files.
 *  Gets all the CXX files from the src/ directory and tokenizes them to src/CXX_FILE.
 *
 *  \param directory_content The content of src/.
 *  \param size The size of the returned array.
 *
 *  \return The tokenized array.
 */
char **scanSourceDirectory(char **directory_content, uint32_t size);

/*! \fn bool scanProjectForge(char *project_dir, char *project_file, char *file)
 *  \brief Check if the file is forged (backed up).
 *
 *  \param project_dir The directory of the project.
 *  \param project_file The c-project file.
 *  \param file The file to check.
 *
 *  \return False if file is NOT forged, True if file IS forged.
 */
bool scanProjectForge(char *project_dir, char *project_file, char *file);

/*! \fn void *pointerArrayTermination(char **pointer, uint32_t size)
 *  \brief Free's allocated array element memory.
 *
 *  \param pointer The allocated array.
 *  \param size The size of the array.
 *
 *  \return The pointer of the array.
 */
void *pointerArrayTermination(char **pointer, uint32_t size);

#endif
