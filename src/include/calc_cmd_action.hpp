#include <calc_features.hpp>
#include <cal.hpp>
#include <calc_stacks/constant_stack.hpp>
#include <calc_stacks/history_stack.hpp>
#include <calc_stacks/num_stack.hpp>
#include <calc_stacks/optr_stack.hpp>
#include <calc_file.hpp>
#include <calc_help.hpp>
#include <time.h>

#ifdef CALC_HISTORY
extern history h;                      /* Object for inserting commands in stack for further retrieval */
#endif

extern strings Error;                  /* String for storing errors generated after each command */
extern link_oprators optr;             /* Object for storing operators in the stack for calculation */
extern link_numbers num;               /* Object for storing numbers in the stack for calculation */

#ifdef CALC_COLORS
extern calc_font input_font;
extern calc_font error_font;
extern calc_font output_font;
extern calc_font prompt_font;
#endif // CALC_COLORS

extern unsigned short record; /* Switch for (not)storing specific types commands */

#ifdef ANS_CMD
extern bool store;              /* Whether or not to store answers */
extern link_ans l;                     /* Object for storing answers in stack */
#endif // ANS_CMD

#ifdef CONST_CMDS
extern const_list cons;                /* Object for storing constants in stack */
#endif // CONST_CMDS

#ifdef STEPS_CMD
extern bool steps;             /* Whether or not to show steps */
#endif // STEPS_CMD

#ifdef FILE_MANAGER
extern bool line_no;           /* Whether or not to show line numbers */
extern bool printpwd;          /* Whether or not to show pwd */
extern char pwd[MAX_LEN];       /* String for storing pwd */
#endif // FILE_MANAGER

#ifdef CALC_PROCESS_TIME
extern bool calc_time;         /* Whether or not to show processing time for each calculation */
extern bool calc_avg_time;     /* Whether or not to show average processing time for a set of sequential calculations */
#endif // CALC_PROCESS_TIME

#ifdef OPTR_DETAILS
extern bool oprator_detail;    /* Whether or not to show status of operators stack */
#endif // OPTR_DETAILS

#ifdef NUM_DETAILS
extern bool num_detail;        /* Whether or not to show status of numbers stack */
#endif // NUM_DETAILS

#ifdef PROMPT
extern char prompt[500];       /* String for storing prompt */
#endif // PROMPT

extern unsigned char angle_type;/* Type of angle to be taken input and shown output */
extern char precision[15];  /* String for storing precision */
extern char e[3];              /* String for showing or not showing exponential */

extern void clrscr();
void cmd_action(strings a);
