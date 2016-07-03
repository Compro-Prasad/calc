#include <math.h>
#include <ctype.h>

#include <str.hpp>
#include <calc_stacks/constant_stack.hpp>

size_t strlen(const char *s)
{
  register int l = 0;
  for (; s[l]; l++);
  return l;
}

int strcmp(const char *s1, const char *s2)
{
  while ((*s1 || *s2) && *s1 == *s2)
    *s1 ? s1++ : 0, *s2 ? s2++ : 0;
  return (*s1 - *s2);
}

int strncmp(const char *s1, const char *s2, size_t l)
{
  for (register unsigned int i = 1;
       i < l && (*s1 || *s2) && *s1 == *s2;
       i++, *s1 ? s1++ : 0, s2 ? s2++ : 0);
  return (*s1 - *s2);
}

int strcasecmp(const char *s1, const char *s2)
{
  while ((*s1 || *s2) && tolower(*s1) == tolower(*s2))
    *s1 ? s1++ : 0, *s2 ? s2++ : 0;
  return (tolower(*s1) - tolower(*s2));
}

int strncasecmp(const char *s1, const char *s2, size_t l)
{
  register unsigned int i = 1;
  for (; i < l && (*s1 || *s2) && tolower(*s1) == tolower(*s2);
       i++, *s1 ? s1++ : 0, s2 ? s2++ : 0);
  return (tolower(*s1) - tolower(*s2));
}

char* strcpy(char *s1, const char *s2)
{
  char *ret_val = s1;
  while (*s2)
    *(s1++) = *(s2++);
  *s1 = 0;
  return ret_val;
}

char* strncpy(char *s1, const char *s2, size_t l)
{
  char *ret_val = s1;
  register unsigned int i = 1;
  for (; i < l && *s2; i++, *(s1++) = *(s2++));
  if (i < l)
    *s1 = 0;
  return ret_val;
}

char* strcat(char *s1, const char *s2)
{
  register char *s = strlen(s1) + s1;
  while (*s2)
    *(s++) = *(s2++);
  *s = 0;
  return s1;
}

char* strncat(char *s1, const char *s2, size_t l)
{
  register unsigned int i = strlen(s1);
  while (*s2 && i < l)
    s1[i++] = *(s2++);
  if (i < l)
    s1[i] = 0;
  return s1;
}

bool ismathchar(const char ch)
{
  if (isalpha(ch) || ch == '/' || ch == '*' || ch == '-' || ch == '+' || ch == '^' || ch == '%'
      || ch == '_' || ch == '!' || ch == '&' || ch == '|' || ch == '<' || ch == '>' || ch == '~'
      || ch == '=')
    return SUCCESS;
  return FAILURE;
}

bool isbinary(const char *s)
{
  if (s)
    {
      if (!*(s + 1))
	switch (*s)
	  {
	  case '>':
	  case '<':
	  case '/':
	  case '*':
	  case '-':
	  case '+':
	  case '^':
	  case 'C':
	  case 'P':
	  case '%':
	  case '|':
	  case '&':
	    return SUCCESS;
	  }
      else if (!*(s + 2))
	{
	  if ((*s == '>' && (*(s + 1) == '=' || *(s + 1) == '>')) ||
	      (*s == '<' && (*(s + 1) == '=' || *(s + 1) == '<')) ||
	      ((*s == '=' || *s == '!') && *(s + 1) == '=') ||
	      (*s == '|' && *(s + 1) == '|') ||
	      (*s == '&' && *(s + 1) == '&'))
	    return SUCCESS;
	}
      else if (!strcmp(s, "log"))
	return SUCCESS;
    }
  return FAILURE;
}

bool isunary(const char *s)
{
  if (s)
    {
      if (*s == '~' || *s == '!' ||
	  !strcmp(s, "ln") ||
	  !strcmp(s, "abs") ||
	  !strcmp(s, "ceil") ||
	  !strcmp(s, "floor") ||
	  !strcmp(s, "sin") ||
	  !strcmp(s, "cos") ||
	  !strcmp(s, "tan") ||
	  !strcmp(s, "cot") ||
	  !strcmp(s, "cosec") ||
	  !strcmp(s, "sec") ||
	  !strcmp(s, "asin") ||
	  !strcmp(s, "acos") ||
	  !strcmp(s, "atan") ||
	  !strcmp(s, "acot") ||
	  !strcmp(s, "asec") ||
	  !strcmp(s, "acosec") ||
	  !strcmp(s, "sinh") ||
	  !strcmp(s, "cosh") ||
	  !strcmp(s, "tanh") ||
	  !strcmp(s, "logten"))
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
  bool s = 0;
  register const char *c = a + i;
  if (*c == '-')
    {
      if (d == REAL || d == INT)
	s = 1;
      else
	return ERROR;
      ++c;
    }
  while (isdigit(*c))
    x = x * 10 + *(c++) - 48;
  if (*c == '.')
    {
      if (d != REAL && d != UNSIGNED_REAL)
	return ERROR;
      register signed long j = 0;
      while (*(++c) > 47 && *c < 58) // isdigit
	x = x + powl(10, --j) * (*c - 48);
    }
  if (s == 1)
    x = -x;
  i = c - a;
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
	     (!ismath(b)
	      || (*b == '&' && a[i] == '&')
	      || (*b == '|' && a[i] == '|')
	      || (*b == 'c' && a[i] == 'o')
	      || (*b == '!' && a[i] == '=')
	      || (!strcmp(b, "cos") && (a[i] == 'e' || a[i] == 'h'))
	      || (!strcmp(b, "sin") && a[i] == 'h')
	      || (!strcmp(b, "tan") && a[i] == 'h')
	      || (!strcmp(b, "log") && a[i] == 't')))
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

int priority_group(const char *s)
{
  /*
      const char operators[][5][4] = {
      { "&&", "||" },
      { ">", "<", ">=", "<=", "==", "!=" },
      { "+", "-" },
      { "*", "/", "%", "^" },
      { "P", "C", "log" },
      { "&", "|" },
      { ">>", "<<" }
      };
  */
  if (*s == *(s + 1))
    switch (*s)
      {
      case '&':
      case '|': return 1;
      case '>':
      case '<': return 7;
      case '=': return 2;
      default : return 0;
      }
  else if (*(s + 1) == '=')
    switch (*s)
      {
      case '>':
      case '<':
      case '!': return 2;
      default : return 0;
      }
  else
    switch (*s)
      {
      case '>':
      case '<': return 2;
      case '+':
      case '-': return 3;
      case '*':
      case '/':
      case '%':
      case '^': return 4;
      case 'P':
      case 'C': return 5;
      case '&':
      case '|': return 6;
      default : return strcmp(s, "log") ? 0 : 5;
      }
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
      if (*s2 == ')')	// highest priority
	return HIGH;
      if (*s1 == '(')	// lowest priority
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

      unsigned char p1 = priority_group(s1), p2 = priority_group(s2);
      if (p1 && p2)
	return p1 < p2 ? LOW : HIGH;
      else
	return ERROR;
    }
  else if (!s1 && s2)
    return LOW;
  return ERROR;
}
