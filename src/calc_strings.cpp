#include <calc_strings.hpp>
strings::strings()
{
#ifdef DYNAMIC_ALLOCATION
    fprintf(stderr, "\nGoing to initialize a block of memory");
    getch();
    c = new char[strMAX];
    fprintf(stderr, "\nMemory base address is at %d", c);
    getch();
    if (c)
#endif
        c[0] = 0, length = 0;
}

strings::strings(const char *x)
{
#ifdef DYNAMIC_ALLOCATION
    c = new char[strMAX];
#endif
    strncpy(c, x, strMAX);
    length = strlen(c);
}

#ifdef DYNAMIC_ALLOCATION
strings::~strings()
{
    delete c;
}

bool strings::assign()
{
    strMAX = MAX_LEN;
    free(c);
    c = new char[strMAX];
    return c ? true : false;
}
bool strings::reassign()
{
    if (length > strMAX - 10)
    {
        strMAX += 100;
        char *ch = new char[strMAX];
        if (!ch)
            return FAILURE;
        delete c;
        c = ch;
    }
    return SUCCESS;
}
#endif

void strings::operator=(const char *x)
{
    strncpy(c, x, strMAX);
    length = strlen(c);
}

void strings::operator=(const strings x)
{
    strncpy(c, x.c, strMAX);
    length = strlen(c);
}

char strings::operator[] (const long i)
{
    return (i < len()? c[i] : NUL);
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

void strings::operator+=(const char *x)
{
    strncat(c, x, strMAX);
    length = strlen(c);
}

void strings::operator+=(const strings x)
{
    strncat(c, x.c, strMAX);
    length = strlen(c);
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

bool strings::write(const char x, const long i)
{
    if ((i == (strMAX - 1) && !x) || i < (strMAX - 1))
    {
        c[i] = x;
        length = strlen(c);
        return true;
    }
    return false;
}

void strings::shift_right(long i)
{
    for (long j = length; j >= i; j--)
        c[j + 1] = c[j];
    length = strlen(c);
}

void strings::del(long i)
{
    if (i < 0)
        return;
    for (unsigned long j = i; j <= strlen(c); j++)
        c[j] = c[j + 1];
    length = strlen(c);
}

const long strings::len()
{
    return length;
}

char *strings::str()
{
    return c;
}

void strings::print()
{
    fprintf(PRINTFAST, "%s", c);
}
