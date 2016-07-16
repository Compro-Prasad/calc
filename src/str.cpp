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

str_hash generate_hash_key(const char *s,
			   unsigned long start,
			   unsigned long end)
{
  register const char *x = s = s + start;
  register str_hash hash = 0;
  if (start == end)
    while (*x)
      hash = 127 * hash + *(x++);
  else if (start < end)
    while (start < end)
      hash = 127 * hash + *(x++), ++start;
  else
    return 0;
  return hash;
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
      if (d == data_type::REAL || d == data_type::INT)
	s = 1;
      else
	return ERROR;
      ++c;
    }
  while (isdigit(*c))
    x = x * 10 + *(c++) - 48;
  if (*c == '.' && isdigit(c[1]))
    {
      if (d != data_type::REAL && d != data_type::UNSIGNED_REAL)
	return ERROR;
      register signed long j = 0;
      while (*(++c) > 47 && *c < 58) // isdigit
	x = x + powl(10, --j) * (*c - 48);
    }
  if (*c == '.' && !isdigit(c[1]))
	return ERROR;
  if (a + i == c)
	return ERROR;
  i = c - a;
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
  if (atof(a, i, p, data_type::UNSIGNED_INT) != SUCCESS)
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
