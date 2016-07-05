#include <assert.h>
#include <malloc.h>

#include <calc_strings.hpp>

strings::strings()
{
  c = 0;
  while (!this->newsize(strMAX))
    --strMAX;
  assert(strMAX);
  c[0] = 0;
}

strings::strings(const char *x)
{
  c = 0;
  while (!this->newsize(strMAX))
    --strMAX;
  assert(strMAX - 1);
  strncpy(c, x, strMAX - 1);
  c[strMAX - 1] = 0;
  length = strlen(c);

}

bool strings::newsize(unsigned long size)
{
  char *z = (char *)realloc(c, size);
  if (z) c = z, length = size;
  return z ? true : false;
}

void strings::operator=(const strings x)
{
  strncpy(c, x.c, strMAX);
  length = strlen(c);
}

void strings::operator=(const char *x)
{
  if (x == NULL)
    {
      fprintf(PRINTFAST, "exit");
      PACKUP_AND_LEAVE("\n");
    }
  strncpy(c, x, strMAX);
  length = strlen(c);
}

void strings::operator=(char **x)
{
  if (c)
    free(c);
  c = *x;
  length = strlen(c);
}

char strings::operator[] (const unsigned long i)
{
  return (i < length ? c[i] : '\0');
}

bool strings::operator==(const char *x)
{
  return !strncasecmp(c, x, cmp_length);
}

bool strings::operator==(const strings x)
{
  return !strncasecmp(c, x.c, strMAX);
}

bool strings::operator!=(const char *x)
{
  return !(!strncasecmp(c, x, cmp_length));
}

bool strings::operator!=(const strings x)
{
  return !(!strncasecmp(c, x.c, strMAX));
}

bool strings::operator<(const char *x)
{
  return (strncmp(c, x, cmp_length) < 0);
}

bool strings::operator<(const strings x)
{
  return (strncmp(c, x.c, strMAX) < 0);
}

bool strings::operator<=(const char *x)
{
  return (strncmp(c, x, cmp_length) <= 0);
}

bool strings::operator<=(const strings x)
{
  return (strncmp(c, x.c, strMAX) <= 0);
}

bool strings::operator>(const char *x)
{
  return (strncmp(c, x, cmp_length) > 0);
}

bool strings::operator>(const strings x)
{
  return (strncmp(c, x.c, strMAX) > 0);
}

bool strings::operator>=(const char *x)
{
  return (strncmp(c, x, cmp_length) >= 0);
}

bool strings::operator>=(const strings x)
{
  return (strncmp(c, x.c, strMAX) >= 0);
}

void strings::operator+=(const char x)
{
  if (length < strMAX - 1)
    this->c[length++] = x,
      this->c[length] = 0;
}

void strings::operator+=(const char *x)
{
  --strMAX;
  while (*x && length < strMAX)
    c[length++] = *(x++);
  c[length] = 0;
  ++strMAX;
}

void strings::operator+=(const strings x)
{
  --strMAX;
  register char *temp = x.c;
  while (*temp && this->length < strMAX)
    c[this->length++] = *(temp++);
  c[this->length] = 0;
  ++strMAX;
}

strings strings::operator+(const char *x)
{
  strings y = *this;
  y += x;
  return y;
}

strings strings::operator+(const strings x)
{
  strings y = *this;
  y += x;
  return y;
}

bool strings::write(const char x, const unsigned long i)
{
  if (x > 31 && x < 127 &&
      ((i == (strMAX - 1) && !x) || i < (strMAX - 1)))
    {
      c[i]   = x;
      i == length ? c[i+1] = 0 : 0;
      length = strlen(c);
      return true;
    }
  return false;
}

void strings::shift_right(unsigned long i)
{
  for (register unsigned long j = length; (signed long)j > (signed long)i; --j)
    c[j + 1] = c[j];
  length = strlen(c);
}

void strings::del(unsigned long i)
{
  for (register unsigned long j = i; j <= strlen(c); ++j)
    c[j] = c[j + 1];
  length = strlen(c);
}

unsigned long strings::len()
{
  return length;
}

void strings::update_len()
{
  this->length = strlen(this->c);
}

char * strings::str()
{
  return c;
}

void strings::print(unsigned long start, unsigned long end)
{
  end == strMAX ? end = length : 0;
  for (register char *ch = c + start;
	 *ch && start < end; ++ch, ++start)
    fprintf(PRINTFAST, "%c", *ch);
}
