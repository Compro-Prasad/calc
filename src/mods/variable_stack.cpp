#include <calc_features.hpp>
#include <calc_error.hpp>
#include <strings.h>
#include <ctype.h>
#ifdef CALC_VARIABLES
#ifndef CALC_VARIABLES_STACK_H
#define CALC_VARIABLES_STACK_H
struct variable
{
  long double value;
  char name[21];
  variable()
  {
    value = 0.0;
    name[0] = 0;
  }
  variable(const long double x)
  {
    value = x;
    name[0] = 0;
  }
  variable(const char *c)
  {
    value = 0;
    strncpy(name, c, 21);
  }
  variable(const long double x, const char *c)
  {
    value = x;
    strncpy(name, c, 21);
  }
};

bool check_variable_name(const char *name)
{
  for (int i = 0; name[i]; i++)
    if (i == 20 && !name[i + 1] ||
    !isalpha(name[i]) && name[i] != '_')
      return 0;
  return 1;
}

struct variable_node
{
  variable var;
  variable_node *next;
  variable_node()
  {
    next = 0;
  }
};

variable_node *most_recent_vars[5];
unsigned char pos = 0;

class variable_list
{
  variable_node *top;
public:
  variable_list()
  {
    top = 0;
  }
  bool display();
  long double return_value(const char *variable_name);
  bool change_value(const variable x);
  void deallocate();
  ~variable_list()
  {
    deallocate();
  }
} var;

long double variable_list::return_value(const char *variable_name)
{
  if (top)
    {
      for (int i = 0; i < 5; i++)
	if (!strcmp(variable_name, most_recent_vars[i]->var.name))
	  return most_recent_vars[i]->var.value;
      for (variable_node * temp = top; temp; temp = temp->next)
	if (!strcmp(variable_name, temp->var.name))
	  {
	    most_recent_vars[pos = pos == 4 ? 0 : pos + 1] = temp;
	    return temp->var.value;
	  }
      calc_error = CALC_VARIABLE_NOT_FOUND;
    }
  calc_error = CALC_VARIABLE_LIST_EMPTY;
}

bool variable_list::change_value(const variable x)
{
  for (int i = 0; i < 5; i++)
    if (!strcmp(x.name, most_recent_vars[i]->var.name))
      {
	most_recent_vars[i]->var.value = x.value;
	return 1;
      }
  for (variable_node *temp = top; temp; temp = temp->next)
    if (!strcmp(x.name, temp->var.name))
      {
	temp->var.value = x.value;
	most_recent_vars[pos = pos == 4 ? 0 : pos + 1] = temp;
	return 1;
      }
  variable_node *temp = new variable_node;
  if (temp)
    {
      temp->var = x;
      temp->next = top;
      top = temp;
      return 1;
    }
  calc_error = CALC_MEMORY_FULL;
  return 0;
}

void variable_list::deallocate()
{
  variable_node *temp;
  while (top)
  {
    temp = top;
    top = top->next;
    delete temp;
  }
}
#endif // CALC_VARIABLES_STACK_H
#endif // CALC_VARIABLES
