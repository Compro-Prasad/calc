#ifndef CALC_INPUT_H
#define CALC_INPUT_H

class strings;

extern void change_input_flags(int);
extern void calc_input();
extern void print_prompt(const char *const s = "");

#ifdef PROMPT
extern char prompt[500];       /* String for storing prompt */
#endif // PROMPT

extern strings Input;

#ifdef SCREEN_MANIP
extern unsigned short cur_prompt_line;
extern unsigned long cur_pos;
#endif

#endif
