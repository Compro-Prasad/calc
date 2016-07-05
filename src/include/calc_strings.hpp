#ifndef string_H
#define string_H

#include <str.hpp>

#define cmp_length  ((strlen(x) > (unsigned long)strMAX || !strlen(x)) ? (unsigned long)strMAX : strlen(x))

class strings
{
  char *c;
  unsigned long length;
public:
  strings();
  strings(const char *x);

  bool newsize(unsigned long size);

  void operator=(const strings x);
  void operator=(const char *x);
  void operator=(char **x);

  char operator[] (const unsigned long i);

  bool operator==(const char *x);
  bool operator==(const strings x);

  bool operator!=(const char *x);
  bool operator!=(const strings x);

  bool operator<(const char *x);
  bool operator<(const strings x);

  bool operator<=(const char *x);
  bool operator<=(const strings x);

  bool operator>(const char *x);
  bool operator>(const strings x);

  bool operator>=(const char *x);
  bool operator>=(const strings x);

  void operator+=(const char x);
  void operator+=(const char *x);
  void operator+=(const strings x);

  strings operator+(const char *x);
  strings operator+(const strings x);

  bool write(const char x, const unsigned long i);

  void shift_right(unsigned long i);

  void del(unsigned long i);

  unsigned long len();

  void update_len();

  char * str();

  void print(unsigned long start, unsigned long end = strMAX);

};

extern strings Error; /* String for storing errors generated after each command */

#endif // strings_H
