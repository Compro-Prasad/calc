#include <calc_stacks/constant_stack.hpp>
#ifdef CONSTANT_STACK_H

#include <calc_strings.hpp>

#ifdef CONST_CMDS
const_list cons;                /* Object for storing constants in stack */
#endif // CONST_CMDS

extern char precision[15];

constant::constant()
{
  name[0] = 0, value = 0.0;
}

constant::constant(const char *c, long double val)
{
  strncpy(name, c, 20);
  name[20] = 0;
  value = val;
}

void constant::display()
{
  fprintf(PRINTFAST, "\n%s = ", name);
  fprintf(PRINTFAST, precision, value);
}

constnt::constnt()
{
  next = 0;
}

const_list::const_list()
{
  top = 0;
}

void const_list::disp_const()
{
  if (top)
    for (constnt * t = top; t; t = t->next)
      t->display();
  else
    Error = "!!Constant list empty!!";
}

bool const_list::get_const(const char *a, unsigned long int &i, long double &x)
{
  if (top)
    {
      char c[15];
      unsigned short k = 0;
      for (; k <= 15 && isalpha(a[i]); i++, k++)
	c[k] = a[i];
      c[k] = 0;
      for (constnt * t = top; t; t = t->next)
	if (!strcmp(c, t->name))
	  {
	    x = t->value;
	    return 1;
	  }
    }
  return 0;
}

void const_list::insert_const(constant x)
{
  if (strcmp(x.name, ""))
    {
      if (!check_const(x.name))
	{
	  Error = "!!Constant already exists!!";
	  return;
	}
      constnt *t = new constnt;
      if (t)
	{
	  t->value = x.value;
	  strncpy(t->name, x.name, 20);
	  t->name[20] = 0;
	  t->next = top, top = t;
	}
      else
	Error = "!!Cannot allocate memory!!";
    }
  else
    Error = "!!NULL constant name!!";
}

void const_list::delete_const(const char *x)
{
  if (top)
    {
      if (!strcmp(x, top->name))
	{
	  constnt *z = top;
	  top = top->next;
	  delete z;
	  return;
	}
      else if (top->next)
	{
	  for (constnt * t = top; t->next != NULL; t = t->next)
	    {
	      if (!strcmp(x, t->next->name))
		{
		  constnt *z = t->next;
		  t->next = t->next->next;
		  delete z;
		  return;
		}
	    }
	}
      Error = "!!Invalid Constant!!";
    }
  else
    Error = "!!Constant list empty!!";
}

bool const_list::check_const(const char *x)
{
  for (constnt * t = top; t; t = t->next)
    if (!strcmp(x, t->name))
      return 0;
  return 1;
}

void const_list::delete_all_const()
{
  while (top)
    {
      constnt *t = top;
      top = top->next;
      delete t;
    }
}

const_list::~const_list()
{
  delete_all_const();
}
#endif // CONSTANT_STACK_H
