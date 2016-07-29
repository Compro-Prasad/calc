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
      register optr_hash hash = 0;
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
  int i = 0;
  for (; i < 22; ++i)
    {
      bin_ops_hash[i] = generate_hash_key(bin_ops[i]) % unify;
      un_ops_hash[i] = generate_hash_key(un_ops[i]) % unify;
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
    for (register unsigned char i = 0; i < 21; ++i)
      if (s == bin_ops_hash[i])
	return SUCCESS;
  return FAILURE;
}

bool isunary(const optr_hash s)
{
  if (s)
    for (register unsigned char i = 0; i < 22; ++i)
      if (s == un_ops_hash[i])
	return SUCCESS;
  return FAILURE;
}

unsigned char extract_math(const char *a, unsigned long &i, long double &x, optr_hash &b)
{
  /*
    This function is mainly called by calculate() in cal.cpp for extracting
    each symbol or operator or identifier from strings a from position i and
    placing it as required.

    For example, if its a number then it will be placed in x otherwise anything
    other than number will be placed in strings *b.

    It also checks if the identifier or symbol is known to the calculator or
    not. If its known then the function returns a specific value. For example,
    if its a constant or number the return value is 1. Same way, if answer(a)
    is found then return is 4, if mathematical function strings is found then
    3, if brackets are encountered then 2.
  */
  if (a[i] == '.' || isdigit(a[i]))
    return atof(a, i, x = 0, data_type::UNSIGNED_REAL) == SUCCESS ? GOT_NUMBER : FAILURE;
#ifdef ANS_CMD
  else if (tolower(a[i + 0]) == 'a' && isdigit(a[i + 1]))
    return GOT_ANSWER;
#endif
  else if (a[i] == '(' || a[i] == ')')
    {
      b = a[i++] == '(' ? H_open_bracket : H_close_bracket;
      return GOT_BRACKET;
    }
  else if (ismathchar(a[i]))
    {
      optr_hash h[7] = { 0 };
      unsigned long chars_read = generate_hash_keys(a, i, i + 6, h + 1);
      while (chars_read)
	if (ismath(h[chars_read--]))
	  {
	    i += chars_read + 1;
	    b = h[chars_read + 1];
	    return GOT_MATH_FUNC;
	  }
      return cons.get_const(a, i, x);
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
    default:                  return "";
    }
}

int priority_group(const optr_hash s)//char *s)
{
  /*
    priority list:  
      const char operators[][5][4] = {
      { "&&", "||" },
      { ">", "<", ">=", "<=", "==", "!=" },
      { "+", "-" },
      { "*", "/" },
      { "%", "^" },
      { "P", "C", "log" },
      { "&", "|" },
      { ">>", "<<" }
      };
  */
  switch (s)
    {
    case H_and:
    case H_or:
      return 1;

    case H_great:
    case H_less:
    case H_equal:
    case H_not_equal:
    case H_great_equal:
    case H_less_equal:
      return 2;

    case H_plus:
    case H_minus:
      return 3;

    case H_multiply:
    case H_divide:
      return 4;

    case H_mod:
    case H_pow:
      return 5;

    case H_P:
    case H_C:
    case H_log:
      return 6;

    case H_bit_and:
    case H_bit_or:
      return 7;

    case H_bit_shift_right:
    case H_bit_shift_left:
      return 8;

    default:
      return 0;
    }
}

long check_priority(const optr_hash s1, const optr_hash s2)
{
  /*
    This is the main function of the calculator. But is placed here because of
    it deals only with strings and nothing else. Its for checking priority of
    symbols/operators. Start seeing from ans.h for understanding this function.
    Or start from cal.cpp

    Here 2 operators are taken as argument. One of them is from the
    link_oprators stack and the other operator is from broken strings of the
    input.

    It only checks the 2 operators provided by the insert() function in cal.cpp
    and returns HIGH when the operator's priority is higher than that of the
    latest inserted operator in the link_oprators stack. And returns LOW when
    the operator's priority is lower than that of the latest inserted operator
    in the link_oprators stack.

    When both operators are same then there comes the decision of binary
    operator and unary operator. When it is a binary operator then HIGH is
    returned and when its unary operator LOW is returned.

    Example(binary operator):-
    2+2+5
    Since + is a binary operator (2+2)+5 is same as 2+(2+5). In the latter case
    there would be high chances of overflow of link_operators stack without any
    need of storing both + operators in the stack. But in the 1st case the
    first + can be removed from the stack before inserting the second +. So the
    stack will have to take less pressure.

    Example(unary operator):-
    sinsin2
    Since sin is a unary operator sin(sin(2)) is the only way we can write it.
    So there is no way of removing the first sin and then adding up the new one
    because it will create problems.

    Note:
    HIGH priority means that operator s2 has the capability to pop the
    latest operator in link_oprators stack without getting any
    calculation errors. For example, if the most recently added operator
    in the link_oprators stack is '/' and now value of s2 is '+' then '+'
    will pop out the '/' from the stack to calculate it at first which is
    done by the insert function after HIGH is returned by this function.

    On the other hand if '+' is the most recent operator in the
    link_oprators stack and '/' is the value of s2 then it should not pop
    out '+' at first because it will cause calculation mistakes. So,
    instead it should itself be added on top of '+' which is done by the
    insert function after it gets the value LOW from this function.
  */
  if (s1 && s2)
    {
      if (s2 == H_close_bracket)        // highest priority
	return HIGH;
      if (s1 == H_open_bracket)         // lowest priority
	return LOW;
      if (isbinary(s1) && isunary(s2))  // 2+sin3; where s1=+ && s2=sin
	return LOW;                     // s1 < s2
      if (isunary(s1) && isbinary(s2))	// sin2+3; where s1=sin && s2=+
	return HIGH;		        // s1 > s2
      if (ismath(s1) && ismath(s2) && s1 == s2) // 2+3+2
        {
	  if (isunary(s1))
	    return LOW;
	  else
	    return HIGH;
        }
      if (isunary(s1) && isunary(s2))
	return LOW;

      unsigned char p1 = priority_group(s1), p2 = priority_group(s2);
      if (p1 && p2)
	return p1 < p2 ? LOW : HIGH;
      else
	return ERROR;
    }
  else if (!s1 && s2)
    return LOW;
  return ERROR;
}
