#include <str.hpp>

#ifndef CALC_CAL_H
#define CALC_CAL_H

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

extern signed char parse_expr(const char *a, // The input string
			      long double &n, // End Result
			      unsigned long &i, // Position in string
			      const char ch = '\0', // Stopping character
			      const long double var = 0, // variable{i} in expr
			      const bool issum = 0 /* for variable */);

extern void factorize(unsigned long &i);

extern void sum(long double lower_limit,
		long double &upper_limit,
		long double &rate,
		const unsigned long &i);


#endif // CALC_CAL_H
