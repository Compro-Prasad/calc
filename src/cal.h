#include "str.h"

#ifndef CALC_CAL_H
#define CALC_CAL_H

#include "calc_colors.h"
#include "calc_ans.h"
#include "calc_strings.h"
#include "calc_constants.h"

#define Err return ERROR
#define Operator "!!Operator scarcity"
#define Number "!!Number scarcity"
#define PI 3.14159265358979323846264338327950288419716939937510

extern bool steps;
extern bool oprator_detail;
extern bool num_detail;
extern unsigned char angle_type;
extern const_list cons;
extern link_ans l;

long double factorial(long double x);	// factorial is undefined for x<0

signed char calculateit(const char *a, long double &ans, long double x, long double y = 0);

struct oprator
{
  char c[7];
  oprator *next;
};

struct number
{
  long double x;
  number *next;
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

signed char insert(const char *s);

signed char calculate(char *a, long double &n, unsigned long i, const char ch = '\0', const long var = 0);
#endif // CALC_CAL_H
