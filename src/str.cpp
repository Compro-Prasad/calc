#include "str.h"
#ifdef CALC_STR_H

bool ismathchar(const char ch)
{
  if (isalpha(ch) || ch == '+' || ch == '%' || ch == '-' || ch == '/' || ch == '*' || ch == '^'
      || ch == '_' || ch == '~' || ch == '&' || ch == '|' || ch == '<' || ch == '>' || ch == '!')
    return SUCCESS;
  return FAILURE;
}

bool isbinary(const char *s)
{
  if (s)
    {
      if (!strcmp(s, "+") ||
	  !strcmp(s, "%") ||
	  !strcmp(s, "-") ||
	  !strcmp(s, "*") ||
	  !strcmp(s, "/") ||
	  !strcmp(s, "^") ||
	  !strcmp(s, "C") ||
	  !strcmp(s, "P") ||
	  !strcasecmp(s, "log") ||
	  !strcmp(s, "|") ||
	  !strcmp(s, "&") ||
	  !strcmp(s, ">>") ||
	  !strcmp(s, "<<"))
	return SUCCESS;
    }
  return FAILURE;
}

bool isunary(const char *s)
{
  if (s)
    {
      if (!strcasecmp(s, "ln") ||
	  !strcmp(s, "~") ||
	  !strcmp(s, "!") ||
	  !strcasecmp(s, "abs") ||
	  !strcasecmp(s, "ceil") ||
	  !strcasecmp(s, "floor") ||
	  !strcasecmp(s, "sin") ||
	  !strcasecmp(s, "cos") ||
	  !strcasecmp(s, "tan") ||
	  !strcasecmp(s, "cot") ||
	  !strcasecmp(s, "cosec") ||
	  !strcasecmp(s, "sec") ||
	  !strcasecmp(s, "asin") ||
	  !strcasecmp(s, "acos") ||
	  !strcasecmp(s, "atan") ||
	  !strcasecmp(s, "acot") ||
	  !strcasecmp(s, "asec") ||
	  !strcasecmp(s, "acosec") ||
	  !strcasecmp(s, "sinh") ||
	  !strcasecmp(s, "cosh") ||
	  !strcasecmp(s, "tanh") ||
	  !strcasecmp(s, "logten"))
	return SUCCESS;
    }
  return FAILURE;
}

bool ismath(const char *s)
{
  if (s)
    {
      if (isbinary(s) || isunary(s))
	return SUCCESS;
      return FAILURE;
    }
  return ERROR;
}

signed char atof(const char *a, unsigned long &i, long double &x, data_type d)
{
  bool f = 0, s = 0;
  unsigned long p = i;
  signed char j = -1, t = SUCCESS;
  if (a[i] == '-')
    {
      if (d == REAL || d == INT)
	s = 1;
      else
	t = ERROR;
      i++;
    }
  if (a[i] == '.')
    {
      if (d == REAL || d == UNSIGNED_REAL)
	f = 1;
      else
	return ERROR;
      i++;
    }
  for (; a[i]; i++)
    {
      if (isdigit(a[i]))
	{
	  if (f == 1 && (d == REAL || d == UNSIGNED_REAL))
	    x = x + pow(10, j--) * (a[i] - 48);
	  else
	    {
	      x = x * 10 + a[i] - 48;
	      if (a[i + 1] == '.')
		{
		  if (d == REAL || d == UNSIGNED_REAL)
		    f = 1;
		  else
		    {
		      t = ERROR;
		      break;
		    }
		  i++;
		}
	    }
	}
      else if (p == i)
	t = ERROR;
      else
	break;
    }
  if (s == 1)
    x = -x;
  if (t != ERROR)
    t = SUCCESS;
  return t;
}

#ifdef ANS_CMD
signed char separate_ans(const char *a, unsigned long &i, long &x)
{
  char c[] = "a";
  unsigned int k = i;
  for (; i < k + 1; i++)
    if (tolower(a[i]) != c[i - k])
      return ERROR;
  long double p = 0.0;
  if (atof(a, i, p, UNSIGNED_INT) != SUCCESS)
    return ERROR;
  x = p;
  return SUCCESS;
}
#endif

void reduce_space(char *a)
{
  if (a)
    {
      for (unsigned long i = 0; a[i]; i++)
	{
	  unsigned long k = 0;
	  while (a[k + i] == ' ')
	    k++;
	  if (k > 1 || (!i && a[i] == ' '))
	    for (unsigned long j = i; a[j]; j++)
	      a[j] = a[j + k - 1 + (i ? 0 : 1)];
	}
    }
}

void extract(const char *a, char *b, unsigned long i, long j, char ch, unsigned long len)
{
  unsigned long x = j;
  if (j < 0 || strlen(a) <= x)
    x = strlen(a) - 1;
  unsigned long k = 0;
  for (; i <= x && a[i] != ch && k < len; b[k++] = a[i++]);
  b[k] = 0;
}

unsigned char extract_math(const char *a, unsigned long &i, long double &x, char *b)
{								
  /* 
     This function is mainly called by
     calculate() in cal.cpp for extracting each
     symbol or operator or identifier from
     strings *a from position i and placing it as 
     required.
     
     For example, if its a number then it will
     be placed in x otherwise anything other
     than number will be placed in strings *b.
     
     It also checks if the identifier or symbol
     is known to the calculator or not. If its
     known then the function returns a specific
     value. For example, if its a constant or
     number the return value is 1. Same way, if
     answer(a) is found then return is 4, if
     mathematical function strings is found then 3,
     if brackets are encountered then 2.
  */
  unsigned long k = 0, j = i;
  b[0] = 0;
  if (a[i] == '.' || isdigit(a[i]))
    {
      atof(a, i, x = 0, UNSIGNED_REAL);
      return 1;
    }
#ifdef ANS_CMD
  else if (tolower(a[i + 0]) == 'a' && isdigit(a[i + 1]))
    return 4;
#endif
  else if (ismathchar(a[i])
#ifdef CONST_CMDS
	   && !cons.get_const(a, j)
#endif
	  )
    {
      while ((!ismath(b) || (!strcasecmp(b, "c") && a[i] == 'o')
	      || (!strcasecmp(b, "cos") && (a[i] == 'e' || a[i] == 'h'))
	      || (!strcasecmp(b, "sin") && a[i] == 'h')
	      || (!strcasecmp(b, "tan") && a[i] == 'h')
	      || (!strcasecmp(b, "log") && a[i] == 't')) && ismathchar(a[i]))
	b[k++] = a[i++], b[k] = 0;
      if (ismath(b))
	return 3;
    }
#ifdef CONST_CMDS
  else if ((x = cons.get_const(a, i)) != 0.0)
    return 1;
#endif
  else if (a[i] == '(' || a[i] == ')')
    {
      b[k++] = a[i++], b[k] = 0;
      return 2;
    }
  return FAILURE;
}

long check_priority(const char *s1, const char *s2)
{								
  /* 
     This is the main function of the
     calculator. But is placed here because of
     it deals only with strings and nothing
     else. Its for checking priority of
     symbols/operators. Start seeing from
     ans.h for understanding this function. or 
     start from cal.cpp
     
     Here 2 operators are taken as argument. One 
     of them is from the link_oprators stack and 
     the other operator is from broken strings of
     the from input.
     
     It only checks the 2 operators provided by
     the insert() function in cal.cpp and
     returns HIGH when the operator's priority
     is higher than that of the latest inserted
     operator in the link_oprators stack. And
     returns LOW when the operator's priority is 
     lower than that of the latest inserted
     operator in the link_oprators stack.
     
     When both operators are same then there
     comes the decision of binary operator and
     unary operator. When it is a binary operator
     then HIGH is returned and when its unary
     operator LOW is returned.
     
     Example(binary operator):-
     2+2+5
     Since + is a binary operator (2+2)+5 is same
     as 2+(2+5). In the latter case there would be
     high chances of overflow of link_operators
     stack without any need of storing both +
     operators in the stack. But in the 1st case
     the first + can be removed from the stack
     before inserting the second +. So the stack
     will have to take less pressure.
     
     Example(unary operator):-
     sinsin2
     Since sin is a unary operator sin(sin(2)) is
     the only way we can write it. So there is no
     way of removing the first sin and then adding
     up the new one because it will create problems.
  */
  if (s1 && s2)
    {
      if (!strcmp(s2, ")"))	// highest priority
	return HIGH;
      if (!strcmp(s1, "("))	// lowest priority
	return LOW;
      if (isbinary(s1) && isunary(s2))	// 2+sin3; where s1=+ && s2=sin
	return LOW;			// s1 < s2
      if (isunary(s1) && isbinary(s2))	// sin2+3; wher s1=sin && s2=+
	return HIGH;		// s1 > s2
      if (ismath(s1) && ismath(s2) && !strcasecmp(s1, s2))	// 2+3+2
	{
	  if (isunary(s1))
	    return LOW;
	  else
	    return HIGH;
	}
      if (isunary(s1) && isunary(s2))
	return LOW;
      char a[][7] = { "+", "-", "*", "/", "^", "p", "c", "log", "%", "|", "&", ">>", "<<" };
      for (int i = 0; i < 13; i++)
	if (!strcasecmp(s1, a[i]))
	  for (int j = 0; j < 13; j++)
	    if (!strcasecmp(s2, a[j]))
	      {
		if (i < j)	// 2+3*5
		  return LOW;	// s1 < s2
		else	// 2*3+5 or 2*3*5
		  return HIGH;	// s1 >= s2
	      }
    }
  return ERROR;
}
#endif // CALC_STR_H
