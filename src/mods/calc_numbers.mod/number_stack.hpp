#include <../calc_features.hpp>
#ifndef CALC_NUMBERS
#define CALC_NUMBERS

typedef bool SIGN;
typedef long LENGTH;

long precision = 0;
calc_numbers num_free_list = NULL;

class calc_number
{
  SIGN sign;
  LENGTH precision;
  LENGTH length; /* From before decimal point */
  calc_numbers *next_num;
  char *addr_ptr;
  char *value_ptr;
  char *frac_ptr;
public:
  calc_number();
  calc_number(LENGTH, LENGTH);
  ~calc_number();
  void toggle_sign();
  SIGN sign();
  LENGTH length();
  LENGTH precision();
  void delete_number();
  void new_number();
  void operator=(calc_number);
  calc_number* operator=(calc_number*);
}
