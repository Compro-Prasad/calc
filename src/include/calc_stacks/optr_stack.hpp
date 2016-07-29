#include <calc_features.hpp>

#ifndef CALC_OPTR_STACK_H
#define CALC_OPTR_STACK_H

#include <str.hpp>

class operators_stack
{
  optr_hash *start;
  optr_hash *current;
  long unsigned size;
#if defined(SPEED_UP)
  long unsigned rate;
#elif defined(ACCELERATE_UP)
  long unsigned accelerate;
#endif
public:
  operators_stack();
  operators_stack(const operators_stack &);
  ~operators_stack();
  void operator=(const operators_stack &);
  optr_hash get();
  signed char push(const optr_hash x);
  signed char pop();
  signed char decrease_size();
  signed char increase_size();
  void reset();
  bool check_brac();
};

#ifdef OPTR_DETAILS
extern bool operator_detail;
#endif

#endif // CALC_OPTR_STACK_H
