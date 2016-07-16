#ifndef CALC_STR_H
#define CALC_STR_H

#include <calc_features.hpp>

/* priority types */
#define HIGH 10000
#define LOW  10

/* extract_math return values */
#define GOT_NUMBER    1
#define GOT_ANSWER    2
#define GOT_BRACKET   3
#define GOT_MATH_FUNC 4

#define SKIP_SPACE(s, i) s[i] == ' ' ? ++i : i

typedef unsigned long long str_hash;

enum class data_type
  {
    REAL,
    INT,
    UNSIGNED_INT,
    UNSIGNED_REAL
  };

extern unsigned long strMAX;


extern size_t strlen(const char *s);
extern int strcmp(const char *s1, const char *s2);
extern int strncmp(const char *s1, const char *s2, size_t l);
extern int strcasecmp(const char *s1, const char *s2);
extern int strncasecmp(const char *s1, const char *s2, size_t l);
extern char* strcpy(char *s1, const char *s2);
extern char* strncpy(char *s1, const char *s2, size_t l);
extern char* strcat(char *s1, const char *s2);
extern char* strncat(char *s1, const char *s2, size_t l);

extern str_hash generate_hash_key(const char *s, unsigned long start = 0, unsigned long end = 0);

extern bool ismath(const char *s);
extern bool isidentifier(const char *s);

extern signed char atof(const char *a, unsigned long &i, long double &x, data_type d = data_type::REAL);

#ifdef ANS_CMD
extern signed char separate_ans(const char *a, unsigned long &i, unsigned long &x);
#endif

/* Extract a substring from a string either on
 * the basis of ending character or position in
 * the given string.
 */
extern void extract(const char *a,              /* Source string */
		    char *b,                    /* Destination string */
		    unsigned long i,            /* Starting position of extraction */
		    unsigned long j = -1,       /* Stopping position of extraction
						 * -1 for not stopping at any
						 * numerical position */
		    char ch = '\0',             /* Stopping character of extraction */
		    unsigned long len = strMAX);/* Length of the source string */

#endif // CALC_STR_H
