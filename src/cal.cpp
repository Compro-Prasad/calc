#include <math.h>
#include <ctype.h>
#include <readline/history.h>

#include <cal.hpp>
#include <operators.hpp>
#include <calc_history.hpp>
#include <calc_strings.hpp>
#include <input_bindings.hpp>
#include <calc_cmd_action.hpp>

#include <calc_stacks/ans_stack.hpp>
#include <calc_stacks/num_stack.hpp>
#include <calc_stacks/optr_stack.hpp>
#include <calc_stacks/constant_stack.hpp>

unsigned char angle_type = DEG;

#ifdef STEPS_CMD
bool steps = false;             /* Whether or not to show steps */
#endif

static long double factorial(long double x)
{
  long double t = 1;
  for (long double i = 1; i <= x; i++)
    t *= i;
  return t;
}

void factorize(unsigned long &i)
{
  long double x = 0, y = 0;
  if (calculate(Input.str(), y, i) == SUCCESS)
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
      if (calculate(Input.str(), x, m, '\0', lower_limit, true) == SUCCESS)
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


static signed char calculateit(const optr_hash a,
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

static signed char insert_into_stack
(const optr_hash s /* operator to be pushed in operator stack */,
 operators_stack &optr,
 numbers_stack &num)
{
  long double x, y, z;
  optr_hash top_optr = optr.get();

  if (check_priority(top_optr, s) == LOW)
    {
#ifdef OPTR_DETAILS
      if (operator_detail == YES)
	fprintf(PRINTFAST, "\nPriority of %6s\tis higher than\t%6s", optr_from_hash(top_optr), optr_from_hash(s));
#endif
      /* Pop out other operators untill the priority returns low or if the
	 operator to be pushed is a ')' and also top_optr is '(' */
      while (check_priority(top_optr, s) == LOW)
	//&& (s != H_close_bracket || top_optr != H_open_bracket))
	{
	  /* if the top_optr is binary */
	  if (isbinary(top_optr))
	    {
	      /* pop out two numbers from number stack */
	      if (num.get(y) != SUCCESS || num.get(x) != SUCCESS)
		return (Error = "!!Number scarcity", ERROR);

	      /* calculate out the result */
	      if (calculateit(top_optr, z, x, y) != SUCCESS)
		return ERROR;
#ifdef STEPS_CMD
	      else if (steps == YES)
		fprintf(PRINTFAST, "\n-> %.3LG %s %.3LG = %.3LG",
			x, optr_from_hash(top_optr), y, z);
#endif
	    }

	  /* if the top_optr is unary */
	  else if (isunary(top_optr))
	    {
	      /* pop out a single number */
	      if (num.get(x) != SUCCESS)
		return (Error = "!!Number scarcity", ERROR);

	      /* calculate out the result */
	      if (calculateit(top_optr, z, x) != SUCCESS)
		return ERROR;
#ifdef STEPS_CMD
	      else if (steps == YES)
		fprintf(PRINTFAST, "\n-> %s(%.3LG) = %.3LG", optr_from_hash(top_optr), x, z);
#endif
	    }

	  /* popout the top operator from the operator stack */
	  optr.pop();

	  /* push the newly generated result */
	  if (num.push(z) == ERROR)
	    return ERROR;

	  /* Check out the next operator from the operator stack */
	  top_optr = optr.get();
	}

      /* if the operator was a ')' then pop out a single operator */
      if (s == H_close_bracket)
	optr.pop();

      /* else push the operator in the operator stack */
      else if (optr.push(s) == ERROR)
	return ERROR;
    }

  /* if the priority is low then it will be pushed in the operator stack */
  else if (check_priority(top_optr, s) == HIGH)
    {
#ifdef OPTR_DETAILS
      if (operator_detail == YES)
	fprintf(PRINTFAST, "\nPriority of %6s\tis lower than\t%6s", optr_from_hash(top_optr), optr_from_hash(s));
#endif
      if (optr.push(s) == ERROR)
	return ERROR;
    }
  else
    {
      Error = "!!Priority";
      return ERROR;
    }
  return SUCCESS;
}

signed char calculate(const char *a,
		      long double &n,
		      unsigned long &i,
		      const char ch,
		      const long double var,
		      const bool issum)
{
  unsigned char check_extract;
#ifdef ANS_CMD
  unsigned long ans_no;
#endif
  operators_stack optr;
  numbers_stack num;
  long double x, y;
  optr_hash c;
  unsigned long first = i;
  bool flag = ch != ' ';
  for (; a[i] != ch;)
    {
      flag ? SKIP_SPACE(a, i) : 0;

      if (a[i] == '+' || a[i] == '-')
        {
	  // condition to tackle continuous random + and/or -
	  int t = 1;
	  if (i == first)
	    num.push(0);
	  while (a[i] == '+' || a[i] == '-')
	    if (a[i++] == '-')
	      t = t * (-1);
	  if (insert_into_stack(t < 0 ? H_minus : H_plus, optr, num) == ERROR)
	    goto ERROR_LABEL;
	  flag ? SKIP_SPACE(a, i) : 0;
	  continue;
        }

      /* i represents the value during suming an expression */
      if (a[i] == 'i' && issum)
        {
	  i++;
	  num.push(var);
	  if (!a[i])
	    break;
        }

      /* **************************Factorial************************ */
      /* It is a special kind of unary operator which                */
      /* stands after the number whose factorial is to be calculated */

      if (i // factorial cannot be at the beginning of input
	  && a[i] == '!' // symbol for factorial notation
	  && a[i + 1] != '=' // operator may be '!='
	  && isalnum(a[i - 1]))
        {
	  if (num.get(x) == ERROR)
	    {
	      Error = "Number scarcity";
	      goto ERROR_LABEL;
	    }
	  if (x >= 0 && !(x - floorl(x)))
	    num.push(factorial(x));
	  else
	    {
	      Error = "!!Factorial";
	      goto ERROR_LABEL;
	    }
	  ++i;
	  flag ? SKIP_SPACE(a, i) : 0;
	  continue;
        }
      /* *********************************************************** */

      x = 0.0;

      /* extract a part of the expression */
      check_extract = extract_math(a, i, x, c);
      /* ******************************** */


      /* if the expression has invalid mathematical part */
      if (!check_extract)
	return FAILURE;
      /* *********************************************** */


      else if (check_extract == GOT_NUMBER)
        {
	  num.push(x);
	  x = 0.0;
	  flag ? SKIP_SPACE(a, i) : 0;

	  /* This part is the work of 'of' in BODMAS

	     For example if you have written sin3sin3 then it is actually
	     sin(3*sin(3)).

	     This is also valid for expressions like '3e' [where 'e' is a
	     constant] where it behaves like '3*e'.

	     So writting things like sin(3(pi+pi/2)) [where 'pi' is a constant]
	     becomes a breeze
	  */ 
#ifdef CONST_CMDS
	  unsigned long j = i;
#endif
	  if ((isalpha(a[i])
	       && (
#ifdef CONST_CMDS
		   cons.get_const(a, j, x) ||
#endif
		   (a[i] != 'P' && tolower(a[i]) != 'l' && a[i] != 'C')))
	      || a[i] == '(')
	    {
	      /* We just have to insert the '*' operator when the above
		 condition is satisfied*/
	      if (insert_into_stack(H_multiply, optr, num) == ERROR)
		goto ERROR_LABEL;
	    }
	  /* *************************************************************** */
        }
#ifdef ANS_CMD
      else if (check_extract == GOT_ANSWER)
        {
	  // extracting the answer location from an expression[13 from 3+A13]
	  if (separate_ans(a, i, ans_no) == ERROR)
            {
	      Error = "!!Answer";
	      goto ERROR_LABEL;
            }
	  // extracting from answer list
	  x = l.get_ans_x(ans_no);
	  if (x != 0.0 || Error == "")
	    {
	      // pushing answer to stack
	      if (num.push(x) == ERROR)
		{
		  Error = "!!Number linker";
		  goto ERROR_LABEL;
		}
	    }
	  else
	    goto ERROR_LABEL;
        }
#endif
      else if (check_extract == GOT_MATH_FUNC)
        {
	  if (insert_into_stack(c, optr, num) == ERROR)
	    goto ERROR_LABEL;
	  else
            {
	      flag ? SKIP_SPACE(a, i) : 0;
	      if ((a[i] == '-' || a[i] == '+') && isdigit(a[i + 1]))
                {
		  atof(a, i, x);
		  num.push(x);
                }
            }
        }
      else if (check_extract == GOT_BRACKET)
        {
	  if (c == H_open_bracket)
            {
	      if (optr.push(c) == ERROR)
		return ERROR;
	      if (a[i] == '-' || a[i] == '+')
		if (num.push(0) == ERROR)
		  return ERROR;
            }
	  else
            {
	      if (!optr.check_brac())
                {
		  Error = "!!Bracket";
		  goto ERROR_LABEL;
                }
	      if (insert_into_stack(c, optr, num) == ERROR)
		goto ERROR_LABEL;
	      flag ? SKIP_SPACE(a, i) : 0;
#ifdef CONST_CMDS
	      unsigned long j = i;
#endif
	      if ((isalpha(a[i])
		   && (
#ifdef CONST_CMDS
		       cons.get_const(a, j, x) ||
#endif
		       (a[i] != 'P' && tolower(a[i]) != 'l'
			&& a[i] != 'C'))) || a[i] == '('
		  || isdigit(a[i]))
		if (insert_into_stack(H_multiply, optr, num) == ERROR)
		  goto ERROR_LABEL;
            }
        }
    }
  while (optr.get())
    if (insert_into_stack(H_close_bracket, optr, num) == ERROR)
      goto ERROR_LABEL;
  if (num.get(n) != SUCCESS)
    return FAILURE;
  if (num.get(y) == SUCCESS)
    {
      Error = "!!Operator scarcity";
      goto ERROR_LABEL;
    }
  if (optr.get())
    {
      Error = "!!Number scarcity";
      goto ERROR_LABEL;
    }

  return SUCCESS;

 ERROR_LABEL:
  Error += " Error!!";
#ifdef CALC_HISTORY
  if (!(record & INVALID_EXPRESSIONS))
    remove_history(history_get_history_state()->length - 1);
#endif
  return ERROR;
}
