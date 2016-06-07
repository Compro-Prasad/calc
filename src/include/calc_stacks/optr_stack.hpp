#include <calc_features.hpp>

#ifndef CALC_OPTR_STACK_H
#define CALC_OPTR_STACK_H

class operators_stack
{
  char (*start)[7];
  char (*current)[7];
  long unsigned size;
#if defined(SPEED_UP)
  long unsigned rate;
#elif defined(ACCELERATE_UP)
  long unsigned accelerator;
#endif
public:
  operators_stack();
  ~operators_stack();
  char *get();
  signed char push(const char *x);
  signed char pop();
  signed char decrease_size();
  signed char increase_size();
  void reset();
  bool check_brac();
};

extern operators_stack optr;
#ifdef OPTR_DETAILS
extern bool operator_detail;
#endif

#endif // CALC_OPTR_STACK_H
