#ifndef CALC_STR_H
#define CALC_STR_H

#include <chatr.hpp>

/* priority types */
#define HIGH 10000
#define LOW  10

/* extract_math return values */
#define GOT_NUMBER    1
#define GOT_ANSWER    2
#define GOT_BRACKET   3
#define GOT_MATH_FUNC 4

#define SKIP_SPACE(s, i) s[i] == ' ' ? ++i : i

#define isupper(c) ((c) > 64 && (c) < 91  ? 1 : 0)
#define islower(c) ((c) > 96 && (c) < 123 ? 1 : 0)
#define isdigit(c) ((c) > 47 && (c) < 58  ? 1 : 0)
#define isalpha(c) (islower(c) || isupper(c))
#define isalnum(c) (isalpha(c) || isdigit(c))
#define tolower(c) (isupper(c) ? (c) + 32 : c)
#define toupper(c) (islower(c) ? (c) - 32 : c)

enum data_type
  {
    REAL,
    INT,
    UNSIGNED_INT,
    UNSIGNED_REAL
  };

extern unsigned long strMAX;

extern unsigned int strlen(const char *s);
extern signed char strcmp(const char *s1, const char *s2);
extern signed char strncmp(const char *s1, const char *s2, unsigned int l);
extern signed char strcasecmp(const char *s1, const char *s2);
extern signed char strncasecmp(const char *s1, const char *s2, unsigned int l);
extern void strcpy(char *s1, const char *s2);
extern void strncpy(char *s1, const char *s2, unsigned int l);
extern void strcat(char *s1, const char *s2);
extern void strncat(char *s1, const char *s2, unsigned int l);

extern bool ismathchar(const char ch);
extern bool isbinary(const char *s);
extern bool isunary(const char *s);
extern bool ismath(const char *s);
extern bool isidentifier(const char *s);

extern signed char atof(const char *a, unsigned long &i, long double &x, data_type d = REAL);

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
		    char ch = NUL,              /* Stopping character of extraction */
		    unsigned long len = strMAX);/* Length of the source string */

/* Extract a number/answer/operator/constant from
 * a given string and return a specific integer
 * to inform about the type of thing extracted
 */
extern unsigned char extract_math(const char *a,   /* The source string */
			   unsigned long &i,/* Starting point of extraction */
			   long double &x,  /* Number stored here if got */
			   char *b);        /* Things other than numbers are
					     * stored in this string */

/* Check priority of two operators contained in string s1 and s2
 * The function returns HIGH for higher priority of s1 than s2
 * and LOW for s1's priority is less than s2. Full documentation
 * is given inthe function's defination in str.cpp
 */
extern long check_priority(const char *s1, const char *s2);

#endif // CALC_STR_H
