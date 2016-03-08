#include <calc_features.hpp>

#ifndef CALC_OPTR_STACK_H
#define CALC_OPTR_STACK_H
#include <string.h>

struct oprator
{
  char c[7];
  oprator *next;
};

class link_oprators
{
  oprator *top;
public:
  link_oprators();
  char *get();
  signed char push(const char *x);
  signed char pop();
  void deallocate();
  bool check_brac();
};

extern link_oprators optr;
extern bool oprator_detail;

#endif // CALC_OPTR_STACK_H
