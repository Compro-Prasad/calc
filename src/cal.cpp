#include <cal.hpp>
#include <math.h>
#include <calc_stacks/optr_stack.hpp>
#include <calc_stacks/num_stack.hpp>
#include <calc_stacks/history_stack.hpp>
#include <calc_strings.hpp>

unsigned char angle_type = DEG;
#ifdef CONST_CMDS
extern const_list cons;
#endif

extern strings Input;

#ifdef ANS_CMD
extern link_ans l;
#endif

#ifdef STEPS_CMD
bool steps = false;             /* Whether or not to show steps */
#endif // STEPS_CMD

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
  if (calculate(Input.str(), y, i) == SUCCESS)
    {
      y < 0 ? y = -y : 0;
      modfl(y, &x);
      fprintf(PRINTFAST, "\nFactors of %.0Lf: ", x);
      for (long double g = 1; g <= x / 2; g++)
	if (!fmodl(x, g))
	  fprintf(PRINTFAST, "%.0Lf, ", g);
      fprintf(PRINTFAST, "%.0Lf", x);
#ifdef CALC_HISTORY
      if (!(record & EXPRESSION_COMMANDS))
	h.pop();
#endif
    }
  else
#ifdef CALC_HISTORY
    {
#endif
      if (Error != "")
	Error += " Error!!";
      else
	sprintf(Error.str(), "\nUndefined symbols in \'%s\'", Input.str());
#ifdef CALC_HISTORY
      if (!(record & EXPRESSIONS_HAVING_ERROR))
	h.pop();
    }
#endif
  num.reset();
  optr.reset();
}

void sum(long double lower_limit, long double &upper_limit, long double &rate, const unsigned long &i)
{
  fprintf(PRINTFAST, "Suming expression \"");
  bool flag = 0, f = 1;
  unsigned long m = i;
  long double sum = 0, x = 0;
  Input.print(m);
  fprintf(PRINTFAST, "\" from i = %Lg to i = %Lg at the rate of %Lg per sum\n", lower_limit, upper_limit, rate);
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
	    Error += " Error!! in expression";
	  else
	    sprintf(Error.str(), "Failure to recognise expression in \"%s\"", Input.str());
#ifdef CALC_HISTORY
	  if (!(record & EXPRESSIONS_HAVING_ERROR))
	    h.pop();
#endif
	  break;
	}
    }

  /* For printing the sum and storing in answer list */
  if (f)
    {
      fprintf(PRINTFAST, "Sum = ");
      if (flag)
	sum = -sum;
      fprintf(PRINTFAST, precision, sum);
#ifdef ANS_CMD
      if (store == 1)
	l.add_ans(sum);
#endif
    }
  /***************************************************/

  num.reset();
  optr.reset();
}


signed char calculateit(const char *a, long double &ans, long double x, long double y)
{
  long double z = angle_type == DEG ? (x * PI / 180) : (angle_type == RAD ? x : (x * PI / 200));
  if (!strcmp(a, "+"))
    ans = x + y;
  else if (!strcmp(a, "-"))
    ans = x - y;
  else if (!strcmp(a, "*"))
    ans = x * y;
  else if (!strcmp(a, "/"))
    {
      if (y)
	ans = x / y;
      else
        {
	  Error = "!!Divide";
	  return ERROR;
        }
    }
  else if (!strcmp(a, "!"))
    {
      if (x >= 0 && !(x - floorl(x)))
	ans = factorial(x);
      else
        {
	  Error = "!!Factorial";
	  return ERROR;
        }
    }
  else if (!strcmp(a, "p"))
    {
      if (x >= 0 && y >= 0 && x >= y && !(x - floorl(x)) && !(y - floorl(y)))
	ans = factorial(x) / factorial(x - y);
      else
        {
	  Error = "!!Factorial";
	  return ERROR;
        }
    }
  else if (!strcmp(a, "c"))
    {
      if (x >= 0 && y >= 0 && x >= y && !(x - floorl(x)) && !(y - floorl(y)))
	ans = factorial(x) / (factorial(y) * factorial(x - y));
      else
        {
	  Error = "!!Factorial";
	  return ERROR;
        }
    }
  else if (!strcmp(a, ">>"))
    ans = (unsigned long)x >> (unsigned long)y;
  else if (!strcmp(a, "<<"))
    ans = (unsigned long)x << (unsigned long)y;
  else if (!strcmp(a, "~"))
    ans = ~(unsigned long)x;
  else if (!strcmp(a, "|"))
    ans = (unsigned long)x | (unsigned long)y;
  else if (!strcmp(a, "&"))
    ans = (unsigned long)x & (unsigned long)y;
  else if (!strcmp(a, "%"))
    ans = fmodl(x, y);
  else if (!strcmp(a, "log"))
    {
      if (y > 0 && x >= 0)
	ans = logl(y) / logl(x);
      else
        {
	  Error = "!!log";
	  return ERROR;
        }
    }
  else if (!strcmp(a, "abs"))
    ans = fabsl(x);
  else if (!strcmp(a, "ceil"))
    ans = ceill(x);
  else if (!strcmp(a, "floor"))
    ans = floorl(x);
  else if (!strcmp(a, "ln"))
    {
      if (x > 0)
	ans = logl(x);
      else
        {
	  Error = "!!log";
	  return ERROR;
        }
    }
  else if (!strcmp(a, "logten"))
    {
      if (x > 0)
	ans = log10l(x);
      else
        {
	  Error = "!!log";
	  return ERROR;
        }
    }
  else if (!strcmp(a, "sinh"))
    ans = sinhl(z);
  else if (!strcmp(a, "cosh"))
    ans = coshl(z);
  else if (!strcmp(a, "tanh"))
    ans = tanhl(z);
  else if (!strcmp(a, "sin"))
    ans = sinl(z);
  else if (!strcmp(a, "cos"))
    ans = cosl(z);
  else if (!strcmp(a, "tan"))
    {
      if (cosl(z))
	ans = tanl(z);
      else
        {
	  Error = "!!tan Undefined";
	  return ERROR;
        }
    }
  else if (!strcmp(a, "cosec"))
    {
      if (sinl(z))
	ans = 1 / sinl(z);
      else
        {
	  Error = "!!cosec undefined";
	  return ERROR;
        }
    }
  else if (!strcmp(a, "sec"))
    {
      if (cosl(z))
	ans = 1 / cosl(z);
      else
        {
	  Error = "!!sec undefined";
	  return ERROR;
        }
    }
  else if (!strcmp(a, "cot"))
    {
      if (sinl(z))
	ans = 1 / tanl(z);
      else
        {
	  Error = "!!cot undefined";
	  return ERROR;
        }
    }
  else if (!strcmp(a, "asin"))
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
  else if (!strcmp(a, "acos"))
    {
      if (x <= 1 && x >= -1)
	ans = angle_type == DEG ? (acosl(x) * 180 / PI) :
	  angle_type == GRAD ? (acosl(x) * 200 / PI) : (acosl(x));
      else
        {
	  Error = "!!acos(x) domain";
	  return ERROR;
        }
    }
  else if (!strcmp(a, "atan"))
    ans = angle_type == DEG ? (atanl(x) * 180 / PI) :
      angle_type == GRAD ? (atanl(x) * 200 / PI) : (atanl(x));
  else if (!strcmp(a, "acosec"))
    {
      if (x <= -1 && x >= 1)
	ans = angle_type == DEG ? (asinl(1 / x) * 180 / PI) :
	  angle_type == GRAD ? (asinl(1 / x) * 200 / PI) : (asinl(1 / x));
      else
        {
	  Error = "!!acosec(x) domain";
	  return ERROR;
        }
    }
  else if (!strcmp(a, "asec"))
    {
      if (x <= -1 && x >= 1)
	ans = angle_type == DEG ? (acosl(1 / x) * 180 / PI) :
	  angle_type == GRAD ? (acosl(1 / x) * 200 / PI) : (acosl(1 / x));
      else
        {
	  Error = "!!asec(x) domain";
	  return ERROR;
        }
    }
  else if (!strcmp(a, "acot"))
    ans = angle_type == DEG ? (atanl(1 / x) * 180 / PI) :
      angle_type == GRAD ? (atanl(1 / x) * 200 / PI) : (atanl(1 / x));
  else if (!strcmp(a, "^"))
    ans = powl(x, y);
  else
    {
      Error = "!!Calculateit";
      return FAILURE;
    }
  return SUCCESS;
}

signed char insert(const char *s)
{
  if (s)
    {
      long double x, y, z;
      char *top_optr = optr.get();
      if (check_priority(top_optr, s) == HIGH)
        {
#ifdef OPTR_DETAILS
	  if (operator_detail == YES)
	    fprintf(PRINTFAST, "\nPriority of %6s\tis higher than\t%6s", top_optr, s);
#endif
	  while (check_priority(top_optr, s) == HIGH
		 && (strcmp(s, ")") || strcmp(top_optr, "(")))
            {
	      if (!top_optr)
                {
		  Error = Operator;
		  return ERROR;
                }
	      if (isbinary(top_optr))
                {
		  if (num.get(y) != SUCCESS || num.get(x) != SUCCESS)
                    {
		      Error = Number;
		      return ERROR;
                    }
		  if (calculateit(top_optr, z, x, y) != SUCCESS)
		    return ERROR;
#ifdef STEPS_CMD
		  else if (steps == YES)
		    fprintf(PRINTFAST, "\n-> %.3LG %s %.3LG = %.3LG", x, top_optr, y, z);
#endif
                }
	      else if (isunary(top_optr))
                {
		  if (num.get(x) != SUCCESS)
                    {
		      Error = Number;
		      return ERROR;
                    }
		  if (calculateit(top_optr, z, x) != SUCCESS)
		    return ERROR;
#ifdef STEPS_CMD
		  else if (steps == YES)
		    fprintf(PRINTFAST, "\n-> %s(%.3LG) = %.3LG", top_optr, x, z);
#endif
                }
	      if (optr.pop() != SUCCESS)
                {
		  Error = "!!Operator pop";
		  return ERROR;
                }
	      if (num.push(z) != SUCCESS)
                {
		  Error = "!!Number push";
		  return ERROR;
                }
	      top_optr = optr.get();
            }
	  if (strcmp(s, ")"))
            {
	      if (optr.push(s) == ERROR)
		return 5;
            }
	  else
	    optr.pop();
        }
      else if (!top_optr || check_priority(top_optr, s) == LOW)
        {
#ifdef OPTR_DETAILS
	  if (operator_detail == YES)
	    fprintf(PRINTFAST, "\nPriority of %6s\tis lower than\t%6s", top_optr, s);
#endif
	  if (optr.push(s) == ERROR)
	    return 5;
        }
      else
        {
	  Error = "!!Priority";
	  return ERROR;
        }
      return SUCCESS;
    }
  return ERROR;
}

signed char calculate(const char *a, long double &n, unsigned long &i, const char ch, const long double var, bool issum)
{
  unsigned char check_extract;
#ifdef ANS_CMD
  unsigned long ans_no;
#endif
  long double x, y;
  char c[10];
  unsigned long first = i;
  bool flag = ch != ' ';
  for (; a[i] != ch;)
    {
      flag ? SKIP_SPACE(a, i) : 0;

      /* *********************************Factorial***************** */
      /* It is a special kind of unary operator which                */
      /* stands after the number whose factorial is to be calculated */
      if (a[i] == '!')
        {
	  num.get(x);
	  if (calculateit("!", y, x) != SUCCESS)
	    return ERROR;
	  num.push(y);
	  i++;
	  flag ? SKIP_SPACE(a, i) : 0;
	  continue;
        }
      /* *********************************************************** */

      if (a[i] == '+' || a[i] == '-')
        {
	  // condition to tackle continuous random + and/or -
	  int t = 1;
	  if (i == first)
	    num.push(0);
	  while (a[i] == '+' || a[i] == '-')
	    if (a[i++] == '-')
	      t = t * (-1);
	  if (insert(t < 0 ? "-" : "+") == ERROR)
	    return ERROR;
	  flag ? SKIP_SPACE(a, i) : 0;
        }

      /* i represents the value during suming an expresseion */
      if (a[i] == 'i' && issum)
        {
	  i++;
	  num.push(var);
	  if (!a[i])
	    break;
        }

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
	      if (insert("*") == ERROR)
		return ERROR;
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
	      return ERROR;
            }
	  // pushing the answer after extracting it from answer list
	  if (num.push(l.get_ans_x(ans_no).num) == ERROR)
            {
	      Error = "!!Number linker";
	      return ERROR;
            }
        }
#endif
      else if (check_extract == GOT_MATH_FUNC)
        {
	  if (insert(c) == ERROR)
	    return ERROR;
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
	  if (!strcmp(c, "("))
            {
	      if (optr.push(c) == ERROR)
		return 5;
	      if (a[i] == '-' || a[i] == '+')
		num.push(0);
            }
	  else
            {
	      if (!optr.check_brac())
                {
		  Error = "!!Bracket";
		  return ERROR;
                }
	      if (insert(c) == ERROR)
		return ERROR;
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
		if (insert("*") == ERROR)
		  return ERROR;
            }
        }
    }							// loop ends
  while (optr.get())
    if (insert(")") == ERROR)
      return ERROR;
  if (num.get(n) != SUCCESS)
    return FAILURE;
  if (num.get(y) == SUCCESS)
    {
      Error = Operator;
      return ERROR;
    }
  if (optr.get())
    {
      Error = Number;
      return ERROR;
    }
#if defined(STEPS_CMD) || defined(OPTR_DETAILS) || defined(NUM_DETAILS)
  if (
#ifdef STEPS_CMD
      steps == YES
#else
      0
#endif
#ifdef OPTR_DETAILS
      || operator_detail == YES
#endif
#ifdef NUM_DETAILS
      || num_detail == YES
#endif
      )
    fprintf(PRINTFAST, "\n");
#endif
  return SUCCESS;
}
