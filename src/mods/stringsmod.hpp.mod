#include <calc_colors.hpp>
#ifndef string_H
#define string_H
#define strMAX 5000
	/***************/
#define cmp_length  ((strlen(x) > strMAX || !strlen(x)) ? strMAX : strlen(x))

struct character
{
  char c;
  character *next;
};

class strings
{
  character c;
  long length;
  long pos;
 public:
  strings()
    {
      c[0] = 1, c[1] = 0, length = 1;
    }
  strings(const char *x)
    {
      strncpy(c, x, strMAX);
      length = strlen(c);
    }
  void operator=(const char *x)
    {
      strncpy(c, x, strMAX);
      length = strlen(c);
    }
  void operator=(const strings x)
    {
      strncpy(c, x.c, strMAX);
      length = strlen(c);
    }
  char operator[](const long i)
  {
    return (i < len() ? c[i] : NUL);
  }
  bool operator==(const char *x)
  {
    return !strncasecmp(c, x, cmp_length);
  }
  bool operator==(const strings x)
  {
    return !strncasecmp(c, x.c, strMAX);
  }
  bool operator!=(const char *x)
  {
    return !(!strncasecmp(c, x, cmp_length));
  }
  bool operator!=(const strings x)
  {
    return !(!strncasecmp(c, x.c, strMAX));
  }
  bool operator<(const char *x)
  {
    return (strncmp(c, x, cmp_length) < 0);
  }
  bool operator<(const strings x)
  {
    return (strncmp(c, x.c, strMAX) < 0);
  }
  bool operator<=(const char *x)
  {
    return (strncmp(c, x, cmp_length) <= 0);
  }
  bool operator<=(const strings x)
  {
    return (strncmp(c, x.c, strMAX) <= 0);
  }
  bool operator>(const char *x)
  {
    return (strncmp(c, x, cmp_length) > 0);
  }
  bool operator>(const strings x)
  {
    return (strncmp(c, x.c, strMAX) > 0);
  }
  bool operator>=(const char *x)
  {
    return (strncmp(c, x, cmp_length) >= 0);
  }
  bool operator>=(const strings x)
  {
    return (strncmp(c, x.c, strMAX) >= 0);
  }
  void operator+=(const char *x)
  {
    strncat(c, x, strMAX);
    length = strlen(c);
  }
  void operator+=(const strings x)
  {
    strncat(c, x.c, strMAX);
    length = strlen(c);
  }
  strings operator+(const char *x)
  {
    strings y = *this;
    y += x;
    return y;
  }
  strings operator+(const strings x)
  {
    strings y = *this;
    y += x;
    return y;
  }
  bool write(const char x, const long i)
  {
    if ((i == (strMAX - 1) && !x) || i < (strMAX - 1))
      {
	c[i] = x;
	length = strlen(c);
	return true;
      }
    return false;
  }
  void shift_right(long i)
  {
    for (long j = length; j >= i; j--)
      c[j + 1] = c[j];
    length = strlen(c);
  }
  void del(long i)
  {
    if (i < 0)
      return;
    for (unsigned long j = i; j <= strlen(c); j++)
      c[j] = c[j + 1];
    length = strlen(c);
  }
  const long len()
  {
    return length;
  }
  char *str()
  {
    return c;
  }
  void print()
  {
    fprintf(PRINTFAST, "%s", c);
  }
};
#endif // strings_H
