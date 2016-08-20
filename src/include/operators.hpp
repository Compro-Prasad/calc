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
#define H_cosec           983557758
#define H_cot             1610984
#define H_asin            200561431
#define H_acos            200304134
#define H_atan            200576544
#define H_asec            200560912
#define H_acosec          705393442
#define H_acot            200304135
#define H_sinh            237271664
#define H_cosh            204594945
#define H_tanh            239191015
#define H_log             1756132
#define H_ln              13826
#define H_logten          232822054
#define H_abs             1577074
#define H_floor           757783302
#define H_ceil            204432389

#include <str.hpp>

extern unsigned long generate_hash_keys(const char *s, unsigned long start, unsigned long end, optr_hash *keys);
extern void make_operator_hashes();

extern bool ismathchar(const char ch);
extern bool isbinary(const optr_hash s);
extern bool isunary(const optr_hash s);

extern const char *optr_from_hash(const optr_hash h);

#endif
