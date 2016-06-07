#ifndef CALC_FEATURES_H
#define CALC_FEATURES_H

#define DIRECT_INPUT
#define SHELL_INPUT

#if !defined(SHELL_INPUT) && !defined(DIRECT_INPUT)
# error "Define at least one or both of SHELL_INPUT and/or DIRECT_INPUT macro(s)"
#endif

#define PROMPT
#define CALC_PROCESS_TIME
#define SUM
#define FACTORIZE
#define CHANGE_ANGLE
#define HELP_CMD
#define CONST_CMDS
#define STEPS_CMD
#define OPTR_DETAILS
#define NUM_DETAILS
#define ANS_CMD
#define SHELL_CMD
#define CHANGE_PRECISION

#define SPEED_UP

#ifdef DIRECT_INPUT
# define SCREEN_MANIP
# define CALC_HISTORY
# if defined(SCREEN_MANIP) || defined(SHELL_INPUT)
#  define CALC_COLORS
# endif
#endif

#define CALC_VARIABLES // under development

/* possible outcomes of a function */
#define SUCCESS 1
#define FAILURE 0
#define ERROR  -1

#include <stdio.h>
#define PRINTFAST (stderr)

#endif // CALC_FEATURES_H
