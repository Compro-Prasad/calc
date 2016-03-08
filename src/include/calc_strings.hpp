#ifndef string_H
#define string_H
#include <string.h>
#include <chatr.hpp>
#define cmp_length  ((strlen(x) > (unsigned long)strMAX || !strlen(x)) ? (unsigned long)strMAX : strlen(x))

extern int getch();

class strings
{
#ifdef DYNAMIC_ALLOCATION
    char *c;
#else
    char c[strMAX];
#endif
    short length;
public:
    strings();
    strings(const char *x);
#ifdef DYNAMIC_ALLOCATION
    ~strings();
    bool assign();
    bool reassign();
#endif
    void operator=(const char *x);
    void operator=(const strings x);
    char operator[] (const long i);
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
    void operator+=(const char *x);
    void operator+=(const strings x);
    strings operator+(const char *x);
    strings operator+(const strings x);
    bool write(const char x, const long i);
    void shift_right(long i);
    void del(long i);
    const long len();
    char *str();
    void print();
};
extern strings Error;
#endif // strings_H
