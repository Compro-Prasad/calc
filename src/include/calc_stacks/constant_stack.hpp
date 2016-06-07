#include <calc_features.hpp>

#ifdef CONST_CMDS
#ifndef CONSTANT_STACK_H
#define CONSTANT_STACK_H

#include <calc_colors.hpp>

/*
  structure made for storing real constants This is made so that the contents
  are stored in a file for storing many constants This would reduce the
  program and memory size to make the program run faster
*/

extern char precision[15];

#ifdef CALC_COLORS
extern calc_font input_font;
extern calc_font error_font;
extern calc_font output_font;
extern calc_font prompt_font;
#endif // CALC_COLORS

struct constant
{
  char name[21];
  long double value;
  constant();
  constant(const char*, long double);
  void display();
};

struct constnt:public constant
{
  constnt *next;
  constnt();
};

class const_list
{
  constnt *top;
public:
  const_list();
  bool check_const(const char *x);
  bool insert_const(const constant x);
  void delete_const(const char *x);
  void disp_const();
  bool get_const(const char *a, unsigned long &i, long double &x);
  void delete_all_const();
  ~const_list();
};

#ifdef CONST_CMDS
extern const_list cons;                /* Object for storing constants in stack */
#endif // CONST_CMDS

#include <str.hpp>

#endif
#endif // CONSTANT_STACK_H
