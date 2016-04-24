#ifndef string_H
#define string_H
#include <string.h>
#include <chatr.hpp>
#include <malloc.h>
#include <assert.h>
#define cmp_length  ((strlen(x) > (unsigned long)strMAX || !strlen(x)) ? (unsigned long)strMAX : strlen(x))

extern int getch();
extern long strMAX;

class strings
{
    char *c;
    short length;
public:
    /* strings:: */strings()
	{
	    c = 0;
	    while (!this->newsize(strMAX))
		  --strMAX;
	    assert(strMAX);
	    c[0] = 0;
	}

	/* strings:: */strings(const char *x)
	{
	    c = 0;
	    while (!this->newsize(strMAX))
		  --strMAX;
	    assert(strMAX - 1);
	    strncpy(c, x, strMAX - 1);
	    c[strMAX - 1] = 0;
	    length = strlen(c);

	}

	bool /* strings:: */newsize(long size)
	{
		char *z = (char *)realloc(c, size);
		if (z) c = z, length = size;
		return z ? true : false;
	}

	void /* strings:: */operator=(const strings x)
	{
	    strncpy(c, x.c, strMAX);
	    length = strlen(c);
	}

	char /* strings:: */operator[] (const long i)
	{
	    return (i < len()? c[i] : NUL);
	}

	bool /* strings:: */operator==(const char *x)
	{
	    return !strncasecmp(c, x, cmp_length);
	}

	bool /* strings:: */operator==(const strings x)
	{
	    return !strncasecmp(c, x.c, strMAX);
	}

	bool /* strings:: */operator!=(const char *x)
	{
	    return !(!strncasecmp(c, x, cmp_length));
	}

	bool /* strings:: */operator!=(const strings x)
	{
	    return !(!strncasecmp(c, x.c, strMAX));
	}

	bool /* strings:: */operator<(const char *x)
	{
	    return (strncmp(c, x, cmp_length) < 0);
	}

	bool /* strings:: */operator<(const strings x)
	{
	    return (strncmp(c, x.c, strMAX) < 0);
	}

	bool /* strings:: */operator<=(const char *x)
	{
	    return (strncmp(c, x, cmp_length) <= 0);
	}

	bool /* strings:: */operator<=(const strings x)
	{
	    return (strncmp(c, x.c, strMAX) <= 0);
	}

	bool /* strings:: */operator>(const char *x)
	{
	    return (strncmp(c, x, cmp_length) > 0);
	}

	bool /* strings:: */operator>(const strings x)
	{
	    return (strncmp(c, x.c, strMAX) > 0);
	}

	bool /* strings:: */operator>=(const char *x)
	{
	    return (strncmp(c, x, cmp_length) >= 0);
	}

	bool /* strings:: */operator>=(const strings x)
	{
	    return (strncmp(c, x.c, strMAX) >= 0);
	}

	void /* strings:: */operator+=(const char *x)
	{
	    strncat(c, x, strMAX);
	    length = strlen(c);
	}

	void /* strings:: */operator+=(const strings x)
	{
	    strncat(c, x.c, strMAX);
	    length = strlen(c);
	}

	strings /* strings:: */operator+(const char *x)
	{
	    strings y = *this;
	    y += x;
	    return y;
	}

	strings /* strings:: */operator+(const strings x)
	{
	    strings y = *this;
	    y += x;
	    return y;
	}

	bool /* strings:: */write(const char x, const long i)
	{
	    if ((i == (strMAX - 1) && !x) || i < (strMAX - 1))
	    {
		  c[i] = x;
		  length = strlen(c);
		  return true;
	    }
	    return false;
	}

	void /* strings:: */shift_right(long i)
	{
	    for (long j = length; j >= i; j--)
		  c[j + 1] = c[j];
	    length = strlen(c);
	}

	void /* strings:: */del(long i)
	{
	    if (i < 0)
		  return;
	    for (unsigned long j = i; j <= strlen(c); j++)
		  c[j] = c[j + 1];
	    length = strlen(c);
	}

	const long /* strings:: */len()
	{
	    return length;
	}

	char * /* strings:: */str()
	{
	    return c;
	}

	void /* strings:: */print()
	{
	    fprintf(PRINTFAST, "%s", c);
	}
};
extern strings Error;
#endif // strings_H
