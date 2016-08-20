#include <math.h>

#include <cal.hpp>
#include <operators.hpp>
#include <calc_strings.hpp>
#include <other_calc_func.hpp>

unsigned char angle_type = DEG;

signed char calculate(const optr_hash a,
			       long double &ans,
			       const long double &x,
			       const long double y = 0)
{
  long double z = angle_type == DEG ? (x * PI / 180) : (angle_type == RAD ? x : (x * PI / 200));

  /* Basic arithmatic operators */
  if (a == H_plus)
    ans = x + y;
  else if (a == H_minus)
    ans = x - y;
  else if (a == H_multiply)
    ans = x * y;
  else if (a == H_divide)
    {
      if (y)
	ans = x / y;
      else
        {
	  Error = "!!Divide";
	  return ERROR;
        }
    }
  else if (a == H_pow)
    ans = powl(x, y);

  /* Factorials */
  else if (a == H_P)
    {
      if (x >= 0 && y >= 0 && x >= y && !(x - floorl(x)) && !(y - floorl(y)))
	ans = factorial(x) / factorial(x - y);
      else
        {
	  Error = "!!Factorial";
	  return ERROR;
        }
    }
  else if (a == H_C)
    {
      if (x >= 0 && y >= 0 && x >= y && !(x - floorl(x)) && !(y - floorl(y)))
	ans = factorial(x) / (factorial(y) * factorial(x - y));
      else
        {
	  Error = "!!Factorial";
	  return ERROR;
        }
    }

  /* Computer related basic operators */
  else if (a == H_bit_not)
    ans = ~(unsigned long)x;
  else if (a == H_bit_or)
    ans = (unsigned long)x | (unsigned long)y;
  else if (a == H_bit_and)
    ans = (unsigned long)x & (unsigned long)y;
  else if (a == H_mod)
    ans = fmodl(x, y);
  else if (a == H_bit_shift_right)
    ans = (unsigned long)x >> (unsigned long)y;
  else if (a == H_bit_shift_left)
    ans = (unsigned long)x << (unsigned long)y;

  /* Relational operators */
  else if (a == H_great)  ans = x > y;
  else if (a == H_less)  ans = x < y;
  else if (a == H_great_equal) ans = x >= y;
  else if (a == H_less_equal)  ans = x <= y;
  else if (a == H_not_equal)   ans = x != y;
  else if (a == H_equal)       ans = x == y;

  /* Other mathematical functions */
  else if (a == H_log)
    {
      if (y > 0 && x >= 0)
	ans = logl(y) / logl(x);
      else
        {
	  Error = "!!log";
	  return ERROR;
        }
    }
  else if (a == H_abs)
    ans = fabsl(x);
  else if (a == H_ceil)
    ans = ceill(x);
  else if (a == H_floor)
    ans = floorl(x);
  else if (a == H_ln)
    {
      if (x > 0)
	ans = logl(x);
      else
        {
	  Error = "!!log";
	  return ERROR;
        }
    }
  else if (a == H_logten)
    {
      if (x > 0)
	ans = log10l(x);
      else
        {
	  Error = "!!log";
	  return ERROR;
        }
    }
  else if (a == H_sinh)
    ans = sinhl(z);
  else if (a == H_cosh)
    ans = coshl(z);
  else if (a == H_tanh)
    ans = tanhl(z);
  else if (a == H_sin)
    ans = sinl(z);
  else if (a == H_cos)
    ans = cosl(z);
  else if (a == H_tan)
    {
      if (cosl(z))
	ans = tanl(z);
      else
        {
	  Error = "!!tan undefined";
	  return ERROR;
        }
    }
  else if (a == H_cosec)
    {
      if (sinl(z))
	ans = 1 / sinl(z);
      else
        {
	  Error = "!!cosec undefined";
	  return ERROR;
        }
    }
  else if (a == H_sec)
    {
      if (cosl(z))
	ans = 1 / cosl(z);
      else
        {
	  Error = "!!sec undefined";
	  return ERROR;
        }
    }
  else if (a == H_cot)
    {
      if (sinl(z))
	ans = 1 / tanl(z);
      else
        {
	  Error = "!!cot undefined";
	  return ERROR;
        }
    }
  else if (a == H_asin)
    {
      if (x <= 1 && x >= -1)
	ans = angle_type == DEG ? (asinl(x) * 180 / PI) :
	  angle_type == GRAD ? (asinl(x) * 200 / PI) : (asinl(x));
      else
        {
	  Error = "!!asin(x) domain";
	  return ERROR;
        }
    }
  else if (a == H_acos)
    {
      if (x <= 1.0 && x >= -1.0)
	ans = angle_type == DEG ? (acosl(x) * 180 / PI) :
	  angle_type == GRAD ? (acosl(x) * 200 / PI) : (acosl(x));
      else
        {
	  Error = "!!acos(x) domain";
	  return ERROR;
        }
    }
  else if (a == H_atan)
    ans = angle_type == DEG ? (atanl(x) * 180 / PI) :
      angle_type == GRAD ? (atanl(x) * 200 / PI) : (atanl(x));
  else if (a == H_acosec)
    {
      if (x <= -1.0 || x >= 1.0)
	ans = angle_type == DEG ? (asinl(1 / x) * 180 / PI) :
	  angle_type == GRAD ? (asinl(1 / x) * 200 / PI) : (asinl(1 / x));
      else
        {
	  Error = "!!acosec(x) domain";
	  return ERROR;
        }
    }
  else if (a == H_asec)
    {
      if (x <= -1 || x >= 1)
	ans = angle_type == DEG ? (acosl(1 / x) * 180 / PI) :
	  angle_type == GRAD ? (acosl(1 / x) * 200 / PI) : (acosl(1 / x));
      else
        {
	  Error = "!!asec(x) domain";
	  return ERROR;
        }
    }
  else if (a == H_acot)
    ans = angle_type == DEG ? (atanl(1 / x) * 180 / PI) :
      angle_type == GRAD ? (atanl(1 / x) * 200 / PI) : (atanl(1 / x));

  /* Logical operators */
  else if ((x == 1 || !x) && (y == 1 || !y))
    {
      if (a == H_not)       ans = !x;
      else if (a == H_or)   ans = x || y;
      else if (a == H_and)  ans = x && y;
      else                  goto Operator_Invalid;
    }

  else
    {
    Operator_Invalid:
      return Error = "!!Invalid Operator", FAILURE;
    }
  return SUCCESS;
}
