#include <str.hpp>

#ifndef CALC_CAL_H
#define CALC_CAL_H

#include <calc_stacks/ans_stack.hpp>
#include <calc_strings.hpp>
#include <calc_stacks/constant_stack.hpp>

#define Err return ERROR
#define Operator "!!Operator scarcity"
#define Number "!!Number scarcity"
#define PI 3.14159265358979323846264338327950288419716939937510

extern bool steps;
extern unsigned char angle_type;
extern const_list cons;
extern link_ans l;

long double factorial(long double x);	// factorial is undefined for x<0

signed char calculateit(const char *a, long double &ans, long double x, long double y = 0);

signed char insert(const char *s);

signed char calculate(char *a, long double &n, unsigned long i, const char ch = '\0', const long var = 0);
#endif // CALC_CAL_H
