#include <calc_features.hpp>

#ifndef CALC_NUM_STACK_H
#define CALC_NUM_STACK_H

class numbers_stack
{
  long double *start;
  long double *current;
  long unsigned size;
#if defined(SPEED_UP)
  long unsigned rate;
#elif defined(ACCELERATE_UP)
  long unsigned accelerate;
#endif
public:
  numbers_stack();
  numbers_stack(const numbers_stack &);
  ~numbers_stack();
  void operator=(const numbers_stack &);
  signed char increase_size();
  signed char decrease_size();
  signed char get(long double &y);
  signed char push(const long double y);
  void reset();
};

extern numbers_stack num;
#ifdef NUM_DETAILS
extern bool num_detail;
#endif

#endif // CALC_CAL_H
