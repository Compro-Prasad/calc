#include <calc_features.hpp>

#ifdef CALC_HISTORY

#ifndef CALC_HISTORY_STACK_H
#define CALC_HISTORY_STACK_H

#include <calc_strings.hpp>

#define VALID_COMMANDS         1
#define VALID_EXPRESSIONS      2
#define INVALID_EXPRESSIONS    4
#define INVALID_COMMANDS       8

#define ALL_COMMANDS           9 // VALID_COMMANDS | INVALID_COMMANDS
#define ALL_EXPRESSIONS        6 // VALID_EXPRESSIONS | INVALID_EXPRESSIONS
#define ALL_VALID              3 // VALID_COMMANDS | VALID_EXPRESSIONS
#define ALL_INVALID           12 // INVALID_COMMANDS | INVALID_EXPRESSIONS

#define ALL_                  15

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
extern history h; /* Object for inserting commands in stack for further retrieval */
extern short record; /* Switch for (not)storing specific types commands */
#endif // CALC_HISTORY_STACK_H
#endif // CALC_HISTORY
