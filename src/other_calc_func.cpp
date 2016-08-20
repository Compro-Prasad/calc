#include <math.h>

#include <parse_expr.hpp>
#include <calc_strings.hpp>
#include <calc_features.hpp>
#include <input_bindings.hpp>
#include <other_calc_func.hpp>

#include <calc_stacks/ans_stack.hpp>

long double factorial(long double x)
{
  long double t = 1;
  for (long double i = 1; i <= x; i++)
    t *= i;
  return t;
}

void factorize(unsigned long &i)
{
  long double x = 0, y = 0;
  if (parse_expr(Input.str(), y, i) == SUCCESS)
    {
      y < 0 ? y = -y : 0;
      modfl(y, &x);
      fprintf(PRINTFAST, "\nFactors of %.0Lf: ", x);
      for (long double g = 1; g <= x / 2; g++)
	if (!fmodl(x, g))
	  fprintf(PRINTFAST, "%.0Lf, ", g);
      fprintf(PRINTFAST, "%.0Lf", x);
    }
  else if (Error == "")
    sprintf(Error.str(), "\nUndefined symbols in '%s'", Input.str());
}

void sum(long double lower_limit,
	 long double &upper_limit,
	 long double &rate,
	 const unsigned long &i)
{
  bool flag = 0, f = 1;
  unsigned long m = i;
  long double sum = 0, x = 0;
  fprintf(PRINTFAST, "\nSuming expression \"");
  Input.print(m);
  fprintf(PRINTFAST,
	  "\" from i = %Lg to i = %Lg at the rate of %Lg per sum",
	  lower_limit, upper_limit, rate);
  if (lower_limit > upper_limit && rate < 0.0)
    {
      swap(lower_limit, upper_limit, long double);
      rate = -rate;
      flag = 1;
    }

  for (; lower_limit <= upper_limit; lower_limit += rate)
    {
      m = i;
      if (parse_expr(Input.str(), x, m, '\0', lower_limit, true) == SUCCESS)
	sum += x;
      else
	{
	  f = 0;
	  if (Error != "")
	    Error += " in expression";
	  else
	    sprintf(Error.str(), "Failure to recognise expression in '%s'", Input.str());
	  break;
	}
    }

  /* For printing the sum and storing in answer list */
  if (f)
    {
      fprintf(PRINTFAST, "\nSum = ");
      if (flag)
	sum = -sum;
      extern char precision[15];
      fprintf(PRINTFAST, precision, sum);
#ifdef ANS_CMD
      if (store == 1)
	l.add_ans(sum);
#endif
    }
  /***************************************************/
}
