 /*****************************************************************************
 *        Do not edit this file manually. Instead, execute install.sh         *
 *****************************************************************************/
#ifndef CALC_FEATURES_H
#define CALC_FEATURES_H

#define CALC_INPUT
#define CALC_STABLE
#define CALC_UNSTABLE

#ifdef CALC_INPUT
# define DIRECT_INPUT
# define SHELL_INPUT
#endif

#if !defined(SHELL_INPUT) && !defined(DIRECT_INPUT)
# error "Define at least one or both of SHELL_INPUT and/or DIRECT_INPUT macro(s)"
#endif

#ifdef CALC_STABLE
# define PROMPT
# define CALC_PROCESS_TIME
# define SUM
# define FACTORIZE
# define CHANGE_ANGLE
# define HELP_CMD
# define CONST_CMDS
# define STEPS_CMD
# define OPTR_DETAILS
# define NUM_DETAILS
# define ANS_CMD
# define SHELL_CMD
# define CHANGE_PRECISION
# define CALC_HISTORY
#endif // CALC_STABLE

# define SPEED_UP

#ifdef CALC_UNSTABLE
# ifdef DIRECT_INPUT
#  define SCREEN_MANIP
# endif
# if defined(SCREEN_MANIP) || defined(SHELL_INPUT)
#  define CALC_COLORS
# endif
#endif // CALC_UNSTABLE

/* possible outcomes of a function */
#define SUCCESS 1
#define FAILURE 0
#define ERROR  -1

#include <stdlib.h>
#define PACKUP_AND_LEAVE(s) do {		\
    fprintf(PRINTFAST, "%s", s);		\
    exit(0);					\
  } while (0)

#include <stdio.h>
#define PRINTFAST stdout

#endif // CALC_FEATURES_H
