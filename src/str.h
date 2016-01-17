#ifndef CALC_STR_H
#define CALC_STR_H

#include <ctype.h>
#include <math.h>
#include <string.h>
#include "chatr.h"
#include "calc_constants.h"

extern const_list cons;

/* priority types */
#define HIGH 10000
#define LOW  10

enum data_type
  {
    REAL,
    INT,
    UNSIGNED_INT,
    UNSIGNED_REAL,
  };

bool ismathchar(const char ch);

bool isbinary(const char *s);

bool isunary(const char *s);

bool ismath(const char *s);

signed char atof(const char *a, unsigned long &i, long double &x, data_type d = REAL);

#ifdef ANS_CMD
signed char separate_ans(const char *a, unsigned long &i, long &x);
#endif

void reduce_space(char *a);

void extract(const char *a, char *b, unsigned long i, long j = -1, char ch = NUL, unsigned long len = strMAX);

unsigned char extract_math(const char *a, unsigned long &i, long double &x, char *b);

long check_priority(const char *s1, const char *s2);
#endif // CALC_STR_H
