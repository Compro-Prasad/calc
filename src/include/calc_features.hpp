#ifndef CALC_FEATURES_H
#define CALC_FEATURES_H
#include <stdio.h>
#define DIRECT_INPUT//-D
#define SHELL_INPUT//-S
#define PROMPT//-P
#define CALC_PROCESS_TIME//-T
#define SUM//-s
#define FACTORIZE//-f
#define CHANGE_ANGLE//-A
#define CONST_CMDS//-C
#define CLEAR_CMD//-c
#define HELP_CMD//-h
#define OPTR_DETAILS//-o
#define NUM_DETAILS//-n
#define STEPS_CMD//-e
#define ANS_CMD//-a
#define SHELL_CMD//-d
#define FILE_MANAGER//-f
#define CHANGE_PRECISION//-p
#define CALC_COLORS//-R
#ifndef HOME//--home
# define HOME "/home/compro/"
#endif
#define CALC_HISTORY
#define CALC_VARIABLES

#define MAX_LEN 1000

/* boolean values */
#define YES 1
#define NO  0
/* type of angles */
#define DEG  20
#define RAD  30
#define GRAD 40
/* possible outcomes of a function */
#define SUCCESS 1
#define FAILURE 0
#define ERROR  -1

#define PRINTFAST (stderr)
#endif // CALC_FEATURES_H
