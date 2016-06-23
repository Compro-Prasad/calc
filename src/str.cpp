#include <math.h>
#include <str.hpp>
#include <calc_stacks/constant_stack.hpp>

#ifdef CONST_CMDS
extern const_list cons;
#endif

unsigned int strlen(const char *s)
{
  register int l = 0;
  for (; s[l]; l++);
  return l;
}

signed char strcmp(const char *s1, const char *s2)
{
  while ((*s1 || *s2) && *s1 == *s2)
    *s1 ? s1++ : 0, *s2 ? s2++ : 0;
  return (*s1 - *s2);
}

signed char strncmp(const char *s1, const char *s2, unsigned int l)
{
  for (register unsigned int i = 1;
       i < l && (*s1 || *s2) && *s1 == *s2;
       i++, *s1 ? s1++ : 0, s2 ? s2++ : 0);
  return (*s1 - *s2);
}

signed char strcasecmp(const char *s1, const char *s2)
{
  while ((*s1 || *s2) && tolower(*s1) == tolower(*s2))
    *s1 ? s1++ : 0, *s2 ? s2++ : 0;
  return (tolower(*s1) - tolower(*s2));
}

signed char strncasecmp(const char *s1, const char *s2, unsigned int l)
{
  register unsigned int i = 1;
  for (; i < l && (*s1 || *s2) && tolower(*s1) == tolower(*s2);
       i++, *s1 ? s1++ : 0, s2 ? s2++ : 0);
  return (tolower(*s1) - tolower(*s2));
}

void strcpy(char *s1, const char *s2)
{
  while (*s2)
    *(s1++) = *(s2++);
  *s1 = 0;
}

void strncpy(char *s1, const char *s2, unsigned int l)
{
  register unsigned int i = 1;
  for (; i < l && *s2; i++, *(s1++) = *(s2++));
  if (i < l)
    *s1 = 0;
}

void strcat(char *s1, const char *s2)
{
  register char *s = strlen(s1) + s1;
  while (*s2)
    *(s++) = *(s2++);
  *s = 0;
}

void strncat(char *s1, const char *s2, unsigned int l)
{
  register unsigned int i = strlen(s1);
  while (*s2 && i < l)
    s1[i++] = *(s2++);
  if (i < l)
    s1[i] = 0;
}

bool ismathchar(const char ch)
{
  if (isalpha(ch) || ch == '/' || ch == '*' || ch == '-' || ch == '+' || ch == '^' || ch == '%'
      || ch == '_' || ch == '!' || ch == '&' || ch == '|' || ch == '<' || ch == '>' || ch == '~')
    return SUCCESS;
  return FAILURE;
}

bool isbinary(const char *s)
{
  if (s)
    {
      if (!strcmp(s, "/") ||
	  !strcmp(s, "*") ||
	  !strcmp(s, "-") ||
	  !strcmp(s, "+") ||
	  !strcmp(s, "^") ||
	  !strcmp(s, "C") ||
	  !strcmp(s, "P") ||
	  !strcmp(s, "%") ||
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

bool isidentifier(const char *s)
{
  while (isalpha(*s) || *s == '_') ++s;
  return *s ? 0 : 1;
}

signed char atof(const char *a, unsigned long &i, long double &x, data_type d)
{
  bool f = 0, s = 0;
  unsigned long p = i;
  signed char j = -1;
  if (a[i] == '-')
    {
      if (d == REAL || d == INT)
	s = 1;
      else
	return ERROR;
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
		  if (f)
		    return ERROR;
		  if (d == REAL || d == UNSIGNED_REAL)
		    f = 1;
		  else
		    return ERROR;
		  i++;
                }
            }
        }
      else if (p == i)
	return ERROR;
      else
	break;
    }
  if (s == 1)
    x = -x;
  return SUCCESS;
}

#ifdef ANS_CMD
signed char separate_ans(const char *a, unsigned long &i, unsigned long &ans_no)
{
  if (tolower(a[i]) != 'a')
    return ERROR;
  i++;
  long double p = 0.0;
  if (atof(a, i, p, UNSIGNED_INT) != SUCCESS)
    return ERROR;
  ans_no = p;
  return SUCCESS;
}
#endif

void extract(const char *a, char *b, unsigned long i, unsigned long j, char ch, unsigned long len)
{
  unsigned long x = j;
  if (j >> sizeof(unsigned long) || strlen(a) <= x)
    x = strlen(a) - 1;
  unsigned long k = 0;
  for (; i <= x && a[i] != ch && k < len; b[k++] = a[i++]);
  b[k] = 0;
}

unsigned char extract_math(const char *a, unsigned long &i, long double &x, char *b)
{
  /*
    This function is mainly called by calculate() in cal.cpp for extracting
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
  unsigned long k = 0;
  b[0] = 0;
  if (a[i] == '.' || isdigit(a[i]))
    {
      atof(a, i, x = 0, UNSIGNED_REAL);
      return GOT_NUMBER;
    }
#ifdef ANS_CMD
  else if (tolower(a[i + 0]) == 'a' && isdigit(a[i + 1]))
    return GOT_ANSWER;
#endif
  else if (a[i] == '(' || a[i] == ')')
    {
      b[k++] = a[i++], b[k] = 0;
      return GOT_BRACKET;
    }
  else if (ismathchar(a[i]))
    {
#ifdef CONST_CMDS
      long unsigned j = i;
#endif
      while (k < 8 && ismathchar(a[i]) &&
	     (!ismath(b) || (!strcasecmp(b, "c") && a[i] == 'o')
	      || (!strcasecmp(b, "cos") && (a[i] == 'e' || a[i] == 'h'))
	      || (!strcasecmp(b, "sin") && a[i] == 'h')
	      || (!strcasecmp(b, "tan") && a[i] == 'h')
	      || (!strcasecmp(b, "log") && a[i] == 't')))
	b[k++] = a[i++], b[k] = 0;
      if (ismath(b))
	return GOT_MATH_FUNC;
#ifdef CONST_CMDS
      else
        {
	  i = j;
	  return cons.get_const(a, i, x);
        }
#endif
    }
  return FAILURE;
}

long check_priority(const char *s1, const char *s2)
{
  /*
    This is the main function of the calculator. But is placed here because of
    it deals only with strings and nothing else. Its for checking priority of
    symbols/operators. Start seeing from ans.h for understanding this function.
    Or start from cal.cpp

    Here 2 operators are taken as argument. One of them is from the
    link_oprators stack and the other operator is from broken strings of the
    input.

    It only checks the 2 operators provided by the insert() function in cal.cpp
    and returns HIGH when the operator's priority is higher than that of the
    latest inserted operator in the link_oprators stack. And returns LOW when
    the operator's priority is lower than that of the latest inserted operator
    in the link_oprators stack.

    When both operators are same then there comes the decision of binary
    operator and unary operator. When it is a binary operator then HIGH is
    returned and when its unary operator LOW is returned.

    Example(binary operator):-
    2+2+5
    Since + is a binary operator (2+2)+5 is same as 2+(2+5). In the latter case
    there would be high chances of overflow of link_operators stack without any
    need of storing both + operators in the stack. But in the 1st case the
    first + can be removed from the stack before inserting the second +. So the
    stack will have to take less pressure.

    Example(unary operator):-
    sinsin2
    Since sin is a unary operator sin(sin(2)) is the only way we can write it.
    So there is no way of removing the first sin and then adding up the new one
    because it will create problems.

    Note:
    HIGH priority means that operator s2 has the capability to pop the
    latest operator in link_oprators stack without getting any
    calculation errors. For example, if the most recently added operator
    in the link_oprators stack is '/' and now value of s2 is '+' then '+'
    will pop out the '/' from the stack to calculate it at first which is
    done by the insert function after HIGH is returned by this function.

    On the other hand if '+' is the most recent operator in the
    link_oprators stack and '/' is the value of s2 then it should not pop
    out '+' at first because it will cause calculation mistakes. So,
    instead it should itself be added on top of '+' which is done by the
    insert function after it gets the value LOW from this function.
  */
  if (s1 && s2)
    {
      if (!strcmp(s2, ")"))	// highest priority
	return HIGH;
      if (!strcmp(s1, "("))	// lowest priority
	return LOW;
      if (isbinary(s1) && isunary(s2))	// 2+sin3; where s1=+ && s2=sin
	return LOW;			// s1 < s2
      if (isunary(s1) && isbinary(s2))	// sin2+3; where s1=sin && s2=+
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
  else if (!s1 && s2)
    return LOW;
  return ERROR;
}
