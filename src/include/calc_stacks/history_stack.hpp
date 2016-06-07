#include <calc_features.hpp>
#ifdef CALC_HISTORY
#ifndef CALC_HISTORY_STACK_H
#define CALC_HISTORY_STACK_H
#include <calc_strings.hpp>
#define UNDEFINED_COMMANDS       1
#define EXPRESSION_COMMANDS      2
#define EXPRESSIONS_HAVING_ERROR 4
#define NORMAL_COMMANDS          8
extern unsigned short record;
struct command
{
  strings c;
  command *next;
  command *prev;
};

class history
{
  command *top, *current;
public:
  history();
  ~history();
  void reset();
  void push(strings cmd);
  void cmd_modify(const strings &cmd);
  command* get_prev_cmd();
  command* get_next_cmd();
  void pop();
  void display();
};
extern history h;             /* Object for inserting commands in stack for further retrieval */
extern unsigned short record; /* Switch for (not)storing specific types commands */
#endif // CALC_HISTORY_STACK_H
#endif // CALC_HISTORY
