#include <math.h>
#include <ctype.h>
#include <readline/history.h>

#include <cal.hpp>
#include <operators.hpp>
#include <calculate.hpp>
#include <calc_history.hpp>
#include <other_calc_func.hpp>

#include <calc_stacks/ans_stack.hpp>
#include <calc_stacks/num_stack.hpp>
#include <calc_stacks/optr_stack.hpp>
#include <calc_stacks/constant_stack.hpp>

#ifdef STEPS_CMD
bool steps = false;             /* Whether or not to show steps */
#endif

static int priority_group(const optr_hash s)//char *s)
{
  /*
    priority list:  
      const char operators[][5][4] = {
      { "&&", "||" },
      { ">", "<", ">=", "<=", "==", "!=" },
      { "+", "-" },
      { "*", "/" },
      { "%", "^" },
      { "P", "C", "log" },
      { "&", "|" },
      { ">>", "<<" }
      };
  */
  switch (s)
    {
    case H_and:
    case H_or:
      return 1;

    case H_great:
    case H_less:
    case H_equal:
    case H_not_equal:
    case H_great_equal:
    case H_less_equal:
      return 2;

    case H_plus:
    case H_minus:
      return 3;

    case H_multiply:
    case H_divide:
      return 4;

    case H_mod:
    case H_pow:
      return 5;

    case H_P:
    case H_C:
    case H_log:
      return 6;

    case H_bit_and:
    case H_bit_or:
      return 7;

    case H_bit_shift_right:
    case H_bit_shift_left:
      return 8;

    default:
      return 0;
    }
}

static long check_priority(const optr_hash s1, const optr_hash s2)
{
  /*
     s1 and s2 are hashes of valid mathematical functions
     This is already done by the extract_math function
     Don't use it unless s1 and s2 are valid functions
  */
  if (s1 && s2)
    {
      bool s1_bin = isbinary(s1);
      bool s2_bin = isbinary(s2);
      bool s1_open = s1 == H_open_bracket;
      bool s2_close = s2 == H_close_bracket;

      if (s1_open && s2_close)
	return HIGH;
      if (s2_close)
	return LOW;
      if (s1_open)
	return HIGH;

      if (s1_bin && not s2_bin)
	return HIGH;

      if (not s1_bin && s2_bin)
	return LOW;

      if (not s1_bin && not s2_bin)
	return HIGH;

      if (s1 == s2)
        {
	  if (s1_bin)
	    return LOW;
	  return HIGH;
        }

      unsigned char p1 = priority_group(s1), p2 = priority_group(s2);
      if (p1 && p2)
	return p1 < p2 ? HIGH : LOW;
    }
  else if (!s1 && s2)
    return HIGH;
  return ERROR;
}

static unsigned char extract_math(const char *a, unsigned long &i,
				  long double &x, optr_hash &b)
{
  /*
    This function is mainly called by parse_expr() in cal.cpp for extracting
    each symbol or operator or identifier from strings a from position i and
    placing it as required.

    For example, if its a number then it will be placed in x otherwise anything
    other than number will be placed in strings *b.

    It also checks if the identifier or symbol is known to the calculator or
    not. If its known then the function returns a specific value. For example,
    if its a constant or number the return value is 1. Same way, if answer(a)
    is found then return is 4, if mathematical function strings is found then
    3, if brackets are encountered then 2.
  */
  if (a[i] == '.' || isdigit(a[i]))
    if (atof(a, i, x = 0, data_type::UNSIGNED_REAL) == SUCCESS)
      return GOT_NUMBER;
    else
      return FAILURE;
#ifdef ANS_CMD
  else if (tolower(a[i + 0]) == 'a' && isdigit(a[i + 1]))
    return GOT_ANSWER;
#endif
  else if (a[i] == '(' || a[i] == ')')
    {
      b = a[i++] == '(' ? H_open_bracket : H_close_bracket;
      return GOT_BRACKET;
    }
  else if (ismathchar(a[i]))
    {
      optr_hash h[7] = { 0 };
      unsigned long chars_read = generate_hash_keys(a, i, i + 6, h + 1);
      while (chars_read)
	if (ismath(h[chars_read--]))
	  {
	    i += chars_read + 1;
	    b = h[chars_read + 1];
	    return GOT_MATH_FUNC;
	  }
      return cons.get_const(a, i, x);
    }
  return FAILURE;
}

static signed char insert_into_stack
(const optr_hash s /* operator to be pushed in operator stack */,
 operators_stack &optr,
 numbers_stack &num)
{
  long double x, y, z;
  optr_hash top_optr = optr.get();

  if (check_priority(top_optr, s) == LOW || s == H_close_bracket)
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
	      if (calculate(top_optr, z, x, y) != SUCCESS)
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
	      if (calculate(top_optr, z, x) != SUCCESS)
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

signed char parse_expr(const char *a, long double &n,
		       unsigned long &i, const char ch,
		       const long double var, const bool issum)
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
