#include "calc_features.h"
#ifdef CALC_HISTORY
#ifndef CALC_HISTORY_H
#define CALC_HISTORY_H
#include "calc_strings.h"
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
  void cmd_modify(strings cmd);
  command* get_prev_cmd();
  command* get_next_cmd();
  void pop();
  void display();
};
extern history h;
#endif // CALC_HISTORY_H
#endif // CALC_HISTORY
