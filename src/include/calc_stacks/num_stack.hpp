#include <calc_features.hpp>

#ifndef CALC_NUM_STACK_H
#define CALC_NUM_STACK_H

struct number
{
  long double x;
  number *next;
};

class link_numbers
{
  number *top;
public:
  link_numbers();
  signed char get(long double &y);
  signed char push(const long double y);
  void deallocate();
};

extern link_numbers num;
extern bool num_detail;

#endif // CALC_CAL_H
