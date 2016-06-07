#include <stdio.h>
#include <str.hpp>
#include <calc_stacks/optr_stack.hpp>

operators_stack optr;
#ifdef OPTR_DETAILS
bool operator_detail;
#endif

operators_stack::operators_stack()
{
  size = 16;
#if defined(SPEED_UP)
  rate = 16;
#elif defined(ACCELERATE_UP)
  accelerator = 1;
#endif
  start = new char[size][7];
  current = 0;
}

operators_stack::~operators_stack()
{
  this->reset();
  delete start;
}

char* operators_stack::get()
{
  if (current)
    return *(current - 1);
  return 0;
}

signed char operators_stack::push(const char *x)
{
  if (current)
    {
      if ((long unsigned)(current - start) == size && this->increase_size() == ERROR)
	return ERROR;
      strcpy(*(current++), x);
    }
  else
    strcpy(*((current = start + 1) - 1), x);
#ifdef OPTR_DETAILS
  if (operator_detail)
    fprintf(PRINTFAST, "\nPushing     %6s\tto   location\t%lx", x, (unsigned long)(current - 1));
#endif
  return SUCCESS;
}

signed char operators_stack::pop()
{
  if (current)
    {
      --current;
#ifdef OPTR_DETAILS
      if (operator_detail)
	fprintf(PRINTFAST, "\nPoping      %6s\tfrom location\t%lx", *current, (unsigned long)current);
#endif
      if (start == current)
	current = 0;
      return SUCCESS;
    }
  return ERROR;
}

void operators_stack::reset()
{
  current = 0;
}

bool operators_stack::check_brac()
{
  for (char (*t)[7] = start; current - t; ++t)
    if (**t == '(')
      return 1;
  return 0;
}

signed char operators_stack::decrease_size()
{
#if defined(SPEED_UP)
  if (size - rate > size)
#elif defined(ACCELERATE_UP)
    if (accelerate - 1 > accelerate)
#endif
      return FAILURE;

#if defined(SPEED_UP)
  char (*temp)[7] = new char[size - rate][7];
#elif defined(ACCELERATE_UP)
  char (*temp)[7] = new char[size / accelerate][7];
#endif
  if (temp)
    {
#if defined(SPEED_UP)
      size -= rate;
#elif defined(ACCELERATE_UP)
      size /= (--accelerator);
#endif
      if (current)
	{
	  char (*x)[7] = start, (*y)[7] = temp;
	  while ((unsigned long)(y - temp) < size)
	    strcpy(*(y++), *(x++));
	  current = y - 1;
	}
      delete [] start;
      start = temp;
      return SUCCESS;
    }
  return ERROR;
}

signed char operators_stack::increase_size()
{
#if defined(SPEED_UP)
  char (*temp)[7] = new char[rate + size][7];
#elif defined(ACCELERATE_UP)
  char (*temp)[7] = new char[(accelerate + 1) * size][7];
#endif
  if (temp)
    {
#if defined(SPEED_UP)
      size += rate;
#elif defined(ACCELERATE_UP)
      size *= (++accelerator);
#endif
      if (current)
	{
	  char (*x)[7] = start, (*y)[7] = temp;
	  while (current - x)
	    strcpy(*(y++), *(x++));
	  current = y - 1;
	}
      delete [] start;
      start = temp;
      return SUCCESS;
    }
  return ERROR;
}
