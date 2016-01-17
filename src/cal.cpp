#include "cal.h"
#ifdef CALC_CAL_H
long double factorial(long double x)
{
  long double t = 1;
  for (long double i = 1; i <= x; i++)
    t *= i;
  return t;
}

signed char calculateit(const char *a, long double &ans, long double x, long double y)
{
  long double z;
  z = angle_type == DEG ? (x * PI / 180) : (angle_type == RAD ? x : (x * PI / 200));
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
	  Err;
	}
    }
  else if (!strcmp(a, "!"))
    {
      if (x >= 0 && !(x - (long)x))
	ans = factorial(x);
      else
	{
	  Error = "!!Factorial";
	  Err;
	}
    }
  else if (!strcasecmp(a, "p"))
    {
	  if (x >= 0 && y >= 0 && x >= y && !(x - floorl(x)) && !(y - floorl(y)))
	ans = factorial(x) / factorial(x - y);
      else
	{
	  Error = "!!Factorial";
	  Err;
	}
    }
  else if (!strcasecmp(a, "c"))
    {
      if (x >= 0 && y >= 0 && x >= y && !(x - floorl(x)) && !(y - floorl(y)))
	ans = factorial(x) / (factorial(y) * factorial(x - y));
      else
	{
	  Error = "!!Factorial";
	  Err;
	}
    }
  else if (!strcmp(a, ">>"))
    ans = (long)x >> (long)y;
  else if (!strcmp(a, "<<"))
    ans = (long)x << (long)y;
  else if (!strcmp(a, "~"))
    ans = ~(long)x;
  else if (!strcmp(a, "|"))
    ans = (long)x | (long)y;
  else if (!strcmp(a, "&"))
    ans = (long)x & (long)y;
  else if (!strcmp(a, "%"))
    ans = (long)x % (long)y;
  else if (!strcasecmp(a, "log"))
    {
      if (y > 0 && x >= 0)
	ans = logl(y) / logl(x);
      else
	{
	  if (!y)
	      Error = "!!log Undefined";
	  else
	      Error = "!!log";
	  Err;
	}
    }
  else if (!strcasecmp(a, "abs"))
    ans = fabsl(x);
  else if (!strcasecmp(a, "ceil"))
    ans = ceill(x);
  else if (!strcasecmp(a, "floor"))
    ans = floorl(x);
  else if (!strcasecmp(a, "ln"))
    {
      if (x > 0)
	ans = logl(x);
      else
	{
	  if (!x)
	      Error = "!!ln Undefined";
	  else
	      Error = "!!ln";
	  Err;
	}
    }
  else if (!strcasecmp(a, "logten"))
    {
      if (x > 0)
	ans = log10l(x);
      else
	{
	  if (!x)
	      Error = "!!logten Undefined";
	  else
	      Error = "!!log10";
	  Err;
	}
    }
  else if (!strcasecmp(a, "sinh"))
    ans = sinhl(z);
  else if (!strcasecmp(a, "cosh"))
    ans = coshl(z);
  else if (!strcasecmp(a, "tanh"))
    ans = tanhl(z);
  else if (!strcasecmp(a, "sin"))
    ans = sinl(z);
  else if (!strcasecmp(a, "cos"))
    ans = cosl(z);
  else if (!strcasecmp(a, "tan"))
    {
      if (cosl(z))
	ans = tanl(z);
      else
	{
	  Error = "!!tan Undefined";
	  Err;
	}
    }
  else if (!strcasecmp(a, "cosec"))
    {
      if (sinl(z))
	ans = 1 / sinl(z);
      else
	{
	  Error = "!!cosec undefined";
	  Err;
	}
    }
  else if (!strcasecmp(a, "sec"))
    {
      if (cosl(z))
	ans = 1 / cosl(z);
      else
	{
	  Error = "!!sec undefined";
	  Err;
	}
    }
  else if (!strcasecmp(a, "cot"))
    {
      if (sinl(z))
	ans = 1 / tanl(z);
      else
	{
	  Error = "!!cot undefined";
	  Err;
	}
    }
  else if (!strcasecmp(a, "asin"))
    {
      if (x <= 1 && x >= -1)
	ans = angle_type == DEG ? (asinl(x) * 180 / PI) :
	  angle_type == GRAD ? (asinl(x) * 200 / PI) : (asinl(x));
      else
	{
	  Error = "!!asin(x) domain";
	  Err;
	}
    }
  else if (!strcasecmp(a, "acos"))
    {
      if (x <= 1 && x >= -1)
	ans = angle_type == DEG ? (acosl(x) * 180 / PI) :
	  angle_type == GRAD ? (acosl(x) * 200 / PI) : (acosl(x));
      else
	{
	  Error = "!!acos(x) domain";
	  Err;
	}
    }
  else if (!strcasecmp(a, "atan"))
    ans = angle_type == DEG ? (atanl(x) * 180 / PI) :
      angle_type == GRAD ? (atanl(x) * 200 / PI) : (atanl(x));
  else if (!strcasecmp(a, "acosec"))
    {
      if (x <= -1 && x >= 1)
	ans = angle_type == DEG ? (asinl(1 / x) * 180 / PI) :
	  angle_type == GRAD ? (asinl(1 / x) * 200 / PI) : (asinl(1 / x));
      else
	{
	  Error = "!!acosec(x) domain";
	  Err;
	}
    }
  else if (!strcasecmp(a, "asec"))
    {
      if (x <= -1 && x >= 1)
	ans = angle_type == DEG ? (acosl(1 / x) * 180 / PI) :
	  angle_type == GRAD ? (acosl(1 / x) * 200 / PI) : (acosl(1 / x));
      else
	{
	  Error = "!!asec(x) domain";
	  Err;
	}
    }
  else if (!strcasecmp(a, "acot"))
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

link_oprators::link_oprators()
{
  top = 0;
}

char* link_oprators::get()
{
  if (top)
    return top->c;
  return 0;
}

signed char link_oprators::push(const char *x)
{
  oprator *o = new oprator;
  if (o)
    {
#ifdef OPTR_DETAILS
      if (oprator_detail == YES)
	fprintf(PRINTFAST, "\nPushing \'%s\' in operator stack having location at %ld", x, (long)o);
#endif
      strcpy(o->c, x);
      o->next = top, top = o;
      return SUCCESS;
    }
#ifdef OPTR_DETAILS
  if (oprator_detail == YES)
    fprintf(PRINTFAST, "\nDynamic memory allocation is full");
#endif
  return ERROR;
}

signed char link_oprators::pop()
{
  if (top)
    {
#ifdef OPTR_DETAILS
      if (oprator_detail == YES)
	fprintf(PRINTFAST, "\nPoping \'%s\' operator from stack having location at %ld", top->c, (long)top);
#endif
      oprator *t = top;
      top = top->next;
      delete t;
      return SUCCESS;
    }
  return ERROR;
}

void link_oprators::deallocate()
{
  if (top)
    {
#ifdef OPTR_DETAILS
      if (oprator_detail == YES)
	fprintf(PRINTFAST, "\nLeft out operators in stack due to some error");
#endif
      while (top)
	{
#ifdef OPTR_DETAILS
	  if (oprator_detail == YES)
	    fprintf(PRINTFAST, "\n\t\'%s\' having location at %ld", top->c, (long)top);
#endif
	  oprator *t = top;
	  top = top->next;
	  delete t;
	}
    }
}

bool link_oprators::check_brac()
{
  for (oprator * t = top; t; t = t->next)
    if (!strcmp(t->c, "("))
      return 1;
  return 0;
}

link_numbers::link_numbers()
{
  top = 0;
}

signed char link_numbers::get(long double &y)
{
  if (top)
    {
#ifdef NUM_DETAILS
      if (num_detail == YES)
	fprintf(PRINTFAST, "\nPoping %Lf from number stack having location at %ld", top->x, (long)top);
#endif
      number *t = top;
      y = top->x;
      top = top->next;
      delete t;
      return SUCCESS;
    }
  return ERROR;
}

signed char link_numbers::push(const long double y)
{
  number *n = new number;
  if (n)
    {
#ifdef NUM_DETAILS
      if (num_detail == YES)
	fprintf(PRINTFAST, "\nPushing %Lf in number stack having location at %ld", y, (long)n);
#endif
      n->x = y;
      n->next = top, top = n;
      return SUCCESS;
    }
#ifdef NUM_DETAILS
  if (num_detail == YES)
    fprintf(PRINTFAST, "\nDynamic memory allocation is full");
#endif
  return ERROR;
}

void link_numbers::deallocate()
{
  if (top)
    {
#ifdef NUM_DETAILS
      if (num_detail == YES)
	fprintf(PRINTFAST, "\nLeft out numbers in stack due to some error");
#endif
      while (top)
	{
#ifdef NUM_DETAILS
	  if (num_detail == YES)
	    fprintf(PRINTFAST, "\n\t\'%Lf\' having location at %ld", top->x, (long)top);
#endif
	  number *t = top;
	  top = top->next;
	  delete t;
	}
    }
}

signed char insert(const char *s)
{
  if (s)
    {
      long double x, y, z;
      if (check_priority(optr.get(), s) == HIGH)
	{
#ifdef OPTR_DETAILS
	  if (oprator_detail == YES)
	    fprintf(PRINTFAST, "\nPriority of \'%s\' is higher than \'%s\'", optr.get(), s);
#endif
	  while (check_priority(optr.get(), s) == HIGH
		 && (strcmp(s, ")") || strcmp(optr.get(), "(")))
	    {
	      if (!optr.get())
		{
		  Error = Operator;
		  Err;
		}
	      if (isbinary(optr.get()))
		{
		  if (num.get(y) != SUCCESS || num.get(x) != SUCCESS)
		    {
		      Error = Number;
		      Err;
		    }
		  if (calculateit(optr.get(), z, x, y) != SUCCESS)
		    Err;
#ifdef STEPS_CMD
		  else if (steps == YES)
		    fprintf(PRINTFAST, "\n-> %.3LG %s %.3LG = %.3LG", x, optr.get(), y, z);
#endif
		}
	      else if (isunary(optr.get()))
		{
		  if (num.get(x) != SUCCESS)
		    {
		      Error = Number;
		      Err;
		    }
		  if (calculateit(optr.get(), z, x) != SUCCESS)
		    Err;
#ifdef STEPS_CMD
		  else if (steps == YES)
		    fprintf(PRINTFAST, "\n-> %s(%.3LG) = %.3LG", optr.get(), x, z);
#endif
		}
	      if (optr.pop() != SUCCESS)
		{
		  Error = "!!Operator pop";
		  Err;
		}
	      if (num.push(z) != SUCCESS)
		{
		  Error = "!!Number push";
		  Err;
		}
	    }
	  if (strcmp(s, ")"))
	    {
	      if (optr.push(s) == ERROR)
		return 5;
	    }
	  else
	    optr.pop();
	}
      else if (check_priority(optr.get(), s) == LOW || !optr.get())
	{
#ifdef OPTR_DETAILS
	  if (oprator_detail == YES)
	    fprintf(PRINTFAST, "\nPriority of \'%s\' is lower than \'%s\'", optr.get(), s);
#endif
	  if (optr.push(s) == ERROR)
	    return 5;
	}
      else
	{
	  Error = "!!Priority";
	  Err;
	}
      return SUCCESS;
    }
  Err;
}

signed char calculate(char *a, long double &n, unsigned long i, const char ch, const long var)
{
  unsigned char check_extract;	/* for checking what has been extracted by 
				   extract_math() function */
  long ans_no;
  long double x, y;
  char c[10];
  for (; a[i] != ch;)
    {
      while (a[i] == ' ')
	i++;		/* unwanted spaces are already removed in main()
			   but its better to keep away from exceptions */

      if (a[i] == '!')
	{
	  num.get(x);
	  if (calculateit("!", y, x) != SUCCESS)
	    Err;
	  num.push(y);
	  i++;
	  continue;
	}
      if (a[i] == '+' || a[i] == '-')
	{
	  // condition to tackle continuous random + and/or -
	  int t = 1;
	  if (i == 0)
	    num.push(0);
	  while (a[i] == '+' || a[i] == '-')
	    if (a[i++] == '-')
	      t = t * (-1);
#ifdef OPTR_DETAILS
	  if (oprator_detail == YES)
	    fprintf(PRINTFAST, "\nPushing \'%c\' from special area", t < 0 ? '-' : '+');
#endif
	  if (t < 0)
	    {
	      if (insert("-") == ERROR)
		Err;
	    }
	  else if (insert("+") == ERROR)
	    Err;
	}
      if (a[i] == 'i')
	{
	  i++;
	  num.push(var);
	  while (a[i] == ' ')
	    i++;
	  if (!a[i])
	    break;
	}
      x = 0.0;
      check_extract = extract_math(a, i, x, c);
      if (!check_extract)
	return FAILURE;
      if (check_extract == 1)
	{
	  num.push(x);
	  x = 0.0;
	  while (a[i] == ' ')
	    i++;
	  unsigned long j = i;
	  if ((isalpha(a[i])
	       && (
#ifdef CONST_CMDS
		   cons.get_const(a, j) ||
#endif
				 (a[i] != 'P' && tolower(a[i]) != 'l' && a[i] != 'C')))
	      || a[i] == '(')
	    if (insert("*") == ERROR)
	      Err;
	}
#ifdef ANS_CMD
      if (check_extract == 4)
	{
	  if (separate_ans(a, i, ans_no) == ERROR)
	    {
	      Error = "!!Answer";
	      Err;
	    }
	  if (num.push(l.get_ans_x(ans_no).n) == ERROR)
	    {
	      Error = "!!Number linker";
	      Err;
	    }
	}
#endif
      if (check_extract == 3)
	{
	  if (insert(c) == ERROR)
	    Err;
	  else
	    {
	      while (a[i] == ' ')
		i++;
	      if ((a[i] == '-' || a[i] == '+') && isdigit(a[i + 1]))
		{
		  atof(a, i, x);
		  num.push(x);
		}
	    }
	}
      if (check_extract == 2)
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
		  Err;
		}
	      if (insert(c) == ERROR)
		Err;
	      while (a[i] == ' ')
		i++;
#ifdef CONST_CMDS
	      unsigned long j = i;
#endif
	      if ((isalpha(a[i])
		   && (
#ifdef CONST_CMDS
		       cons.get_const(a, j) || 
#endif
		       (a[i] != 'P' && tolower(a[i]) != 'l'
			&& a[i] != 'C'))) || a[i] == '('
		  || isdigit(a[i]))
		if (insert("*") == ERROR)
		  Err;
	    }
	}
    }							// loop ends
  while (optr.get())
    if (insert(")") == ERROR)
      Err;
  if (num.get(n) != SUCCESS)
    return FAILURE;
  if (num.get(y) == SUCCESS)
    {
      Error = Operator;
      Err;
    }
  if (optr.get())
    {
      Error = Number;
      Err;
    }
#if defined(STEPS_CMD) || defined(OPTR_DETAILS) || defined(NUM_DETAILS)
  if (
#ifdef STEPS_CMD
      steps == YES
#else
      0
#endif
#ifdef OPTR_DETAILS
      || oprator_detail == YES
#endif
#ifdef NUM_DETAILS
      || num_detail == YES
#endif
      )
    fprintf(PRINTFAST, "\n");
#endif
  return SUCCESS;
}
#endif // CALC_CAL_H
