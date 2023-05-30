/*! \file option.h
 *  \brief Contains functions for scanning options.
 *
 *  Functions included in the file are for scanning through the argv/options.
 *
 *  Functions included are:
 *    - getOptionArg(int, char *, char *)
 *    - scanOption(int, char *, char *)
 *
 *  The returns are either the argument of the option or a boolean.
 */

#ifndef C_PROJECT_OPTION_H
#define C_PROJECT_OPTION_H

#include <stdbool.h>

/*! \fn char *getOptionArg(int argc, char *argv[], char *option)
 *  \brief Scans the options and returns the argument of it.
 *
 *  \param argc Option count / Argument count.
 *  \param argv Options / Arguments.
 *  \param option Option to scan for.
 *
 *  \return Argument of the option.
 */
char * getOptionArg(int argc, char * argv[], char * option);

/*! \fn bool scanOption(int argc, char *argv[], char *option)
 *  \brief Scans the options if the option is passed.
 *
 *  \param argc Option count / Argument count.
 *  \param argv Options / Arguments.
 *  \param option Option to scan for.
 *
 *  \return TRUE if the option is passed and FALSE if the option isn't passed.
 */
bool scanOption(int argc, char * argv[], char * option);

#endif /* C_PROJECT_OPTION_H */
