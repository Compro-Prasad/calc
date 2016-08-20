#ifndef OTHER_CALC_FUNC_H
#define OTHER_CALC_FUNC_H

#define swap(x, y, t) do {			\
  t T = x;					\
  x = y;					\
  y = T;					\
  }while (0);					\

extern long double factorial(long double x);

extern void factorize(unsigned long &i);

extern void sum(long double lower_limit,
		long double &upper_limit,
		long double &rate,
		const unsigned long &i);

#endif
