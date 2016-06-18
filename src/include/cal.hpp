#include <str.hpp>

#ifndef CALC_CAL_H
#define CALC_CAL_H

#include <calc_stacks/ans_stack.hpp>
#include <calc_strings.hpp>
#include <calc_stacks/constant_stack.hpp>

#define Operator "!!Operator scarcity"
#define Number "!!Number scarcity"
#define PI 3.14159265358979323846264338327950288419716939937510

/* type of angles */
#define DEG  20
#define RAD  30
#define GRAD 40

/* boolean values */
#define YES 1
#define NO  0

#define swap(x, y, t) do {			\
  t T = x;					\
  x = y;					\
  y = T;					\
  }while (0);					\

#ifdef STEPS_CMD
extern bool steps;             /* Whether or not to show steps */
#endif

extern unsigned char angle_type;

extern long double factorial(long double x);  // factorial is undefined for x<0

extern signed char calculateit(const char *a, // operator
			       long double &ans, // Result to be stored into
			       const long double &x, // Argument 1
			       const long double y = 0 /* Argument 2 */);

extern signed char insert(const char *s);

extern signed char calculate(const char *a, // The input string to be worked on
			     long double &n, // End Result
			     unsigned long &i, // Position in string
			     const char ch = '\0', // Stopping character
			     const long double var = 0, // for variable in expr
			     const bool issum = 0 /* for variable */);

extern void factorize(unsigned long &i);

extern void sum(long double lower_limit,
		long double &upper_limit,
		long double &rate,
		const unsigned long &i);


#endif // CALC_CAL_H
