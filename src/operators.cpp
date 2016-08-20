#include <operators.hpp>
#include <ctype.h>
#include <calc_stacks/constant_stack.hpp>

static const char bin_ops[22][4] =
  {
    "+", "-", "*", "/", "^", "|", "&", "P", "C", ">>", "<<",
    "<", ">", ">=", "<=", "==", "!=", "%", "log", "&&", "||", ""
  };

static const char un_ops[22][7] =
  {
    "~", "!", "ln", "abs", "cos", "sin", "tan", "acos", "asin", "atan",
    "sec", "cosec", "cot", "asec", "acosec", "acot", "logten", "floor",
    "sinh", "cosh", "tanh", "ceil"
  };

static optr_hash bin_ops_hash[22] = { 0 };
static optr_hash un_ops_hash[22] = { 0 };

static const unsigned long unify = 999999999;

unsigned long generate_hash_keys(const char *s,
				 unsigned long start,
				 unsigned long end,
				 optr_hash *keys)
{
  if (start < end)
    {
      register const char *x = s = s + start;
      register str_hash hash = 0;
      while (ismathchar(*x) && start < end)
	{
	  hash = 127 * hash + *x, ++start;
	  keys[x++ - s] = hash % unify;
	}
      return x - s;
    }
  return 0;
}

void make_operator_hashes()
{
  int i = 0, j;
  optr_hash t;

  /* Generating */
  for (; i < 22; ++i)
    {
      bin_ops_hash[i] = generate_hash_key(bin_ops[i]) % unify;
      un_ops_hash[i] = generate_hash_key(un_ops[i]) % unify;
    }

  /* Sorting */
  for (i = 0; i < 22; ++i)
    for (j = 0; j < 22 - i - 1; ++j)
      if (un_ops_hash[j] > un_ops_hash[j + 1])
	{
	  t = un_ops_hash[j];
	  un_ops_hash[j] = un_ops_hash[j + 1];
	  un_ops_hash[j + 1] = t;
	}
  for (i = 0; i < 21; ++i)
    for (j = 0; j < 21 - i - 1; ++j)
      if (bin_ops_hash[j] > bin_ops_hash[j + 1])
	{
	  t = bin_ops_hash[j];
	  bin_ops_hash[j] = bin_ops_hash[j + 1];
	  bin_ops_hash[j + 1] = t;
	}
}

bool ismathchar(const char ch)
{
  if (isalpha(ch) ||
      ch == '/' ||
      ch == '*' ||
      ch == '-' ||
      ch == '+' ||
      ch == '^' ||
      ch == '%' ||
      ch == '_' ||
      ch == '!' ||
      ch == '&' ||
      ch == '|' ||
      ch == '<' ||
      ch == '>' ||
      ch == '~' ||
      ch == '=')
    return SUCCESS;
  return FAILURE;
}

bool isbinary(const optr_hash s)
{
  if (s)
    {
      register unsigned char beg = 0, end = 20, mid;
      while (beg <= end)
	{
	  mid = (beg + end) / 2;
	  if (s == bin_ops_hash[mid] ||
	      s == bin_ops_hash[beg] ||
	      s == bin_ops_hash[end])
	    return SUCCESS;
	  else if (s < bin_ops_hash[mid])
	    end = mid - 1, ++beg;
	  else
	    beg = mid + 1, --end;
	}
    }
  return FAILURE;
}

bool isunary(const optr_hash s)
{
  if (s)
    {
      register unsigned char beg = 0, end = 21, mid;
      while (beg <= end)
	{
	  mid = (beg + end) / 2;
	  if (s == un_ops_hash[mid] ||
	      s == un_ops_hash[beg] ||
	      s == un_ops_hash[end])
	    return SUCCESS;
	  else if (s < un_ops_hash[mid])
	    end = mid - 1, ++beg;
	  else
	    beg = mid + 1, --end;
	}
    }
  return FAILURE;
}

const char *optr_from_hash(const optr_hash h)
{
  switch (h)
    {
    case H_plus:              return "+";
    case H_minus:             return "-";
    case H_multiply:          return "*";
    case H_divide:            return "/";
    case H_pow:               return "^";
    case H_mod:               return "%";
    case H_P:                 return "P";
    case H_C:                 return "C";
    case H_bit_and:           return "&";
    case H_bit_or:            return "|";
    case H_bit_shift_right:   return ">>";
    case H_bit_shift_left:    return "<<";
    case H_bit_not:           return "~";
    case H_open_bracket:      return "(";
    case H_close_bracket:     return ")";
    case H_not:               return "!";
    case H_and:               return "&&";
    case H_or:                return "||";
    case H_great:             return ">";
    case H_less:              return "<";
    case H_great_equal:       return ">=";
    case H_less_equal:        return "<=";
    case H_sin:               return "sin";
    case H_cos:               return "cos";
    case H_tan:               return "tan";
    case H_sec:               return "sec";
    case H_cosec:             return "cosec";
    case H_cot:               return "cot";
    case H_asin:              return "asin";
    case H_acos:              return "acos";
    case H_atan:              return "atan";
    case H_asec:              return "asec";
    case H_acosec:            return "acosec";
    case H_acot:              return "acot";
    case H_sinh:              return "sinh";
    case H_cosh:              return "cosh";
    case H_tanh:              return "tanh";
    case H_log:               return "log";
    case H_ln:                return "ln";
    case H_logten:            return "logten";
    case H_abs:               return "abs";
    case H_floor:             return "floor";
    case H_ceil:              return "ceil";
    case 0:                   return "(null)";
    default:                  return "";
    }
}
