#ifndef OPERATORS_H
#define OPERATORS_H

#define H_plus            43
#define H_minus           45
#define H_multiply        42
#define H_divide          47
#define H_pow             94
#define H_mod             37
#define H_P               80
#define H_C               67
#define H_bit_and         38
#define H_bit_or          124
#define H_bit_shift_right 7936
#define H_bit_shift_left  7680
#define H_bit_not         126
#define H_open_bracket    40
#define H_close_bracket   41
#define H_not             33
#define H_and             4864
#define H_or              15872
#define H_great           62
#define H_less            60
#define H_great_equal     7935
#define H_less_equal      7681
#define H_equal           7808
#define H_not_equal       4252
#define H_sin             1868280
#define H_cos             1610983
#define H_tan             1883393
#define H_sec             1867761
#define H_cosec           25983557733
#define H_cot             1610984
#define H_asin            200561431
#define H_acos            200304134
#define H_atan            200576544
#define H_asec            200560912
#define H_acosec          3230705390212
#define H_acot            200304135
#define H_sinh            237271664
#define H_cosh            204594945
#define H_tanh            239191015
#define H_log             1756132
#define H_ln              13826
#define H_logten          3597232818457

#include <str.hpp>

extern unsigned long generate_hash_keys(const char *s, unsigned long start, unsigned long end, str_hash *keys);
extern void make_operator_hashes();

extern bool ismathchar(const char ch);
extern bool isbinary(const char *s);
extern bool isunary(const char *s);

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

#endif
