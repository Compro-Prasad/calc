#include <stdio.h>

#include <operators.hpp>
#include <calc_stacks/optr_stack.hpp>

#ifdef OPTR_DETAILS
bool operator_detail;
#endif

operators_stack::operators_stack()
{
  size = 16;
#if defined(SPEED_UP)
  rate = 16;
#elif defined(ACCELERATE_UP)
  accelerate = 1;
#endif
  start = new optr_hash[size];
  current = 0;
}

operators_stack::operators_stack(const operators_stack &t)
{
  this->size = t.size;
#if defined(SPEED_UP)
  this->rate = t.rate;
#elif defined(ACCELERATE_UP)
  this->accelerate = t.accelerate;
#endif
  this->start = new optr_hash[this->size];
  this->current = t.current ? this->start + (t.current - t.start) : 0;
  for (optr_hash *temp1 = this->start, *temp2 = t.start;
       temp2 < t.current;
       *(temp1++) = *(temp2++));
}

void operators_stack::operator=(const operators_stack &t)
{
  if (this->start)
    delete [] this->start;
  this->start = new optr_hash[this->size = t.size];
#if defined(SPEED_UP)
  this->rate = t.rate;
#elif defined(ACCELERATE_UP)
  this->accelerate = t.accelerate;
#endif
  this->current = t.current ? this->start + (t.current - t.start) : 0;
  for (optr_hash *temp1 = this->start, *temp2 = t.start;
       temp2 < t.current;
       *(temp1++) = *(temp2++));
}

operators_stack::~operators_stack()
{
  this->reset();
  delete [] this->start;
}

optr_hash operators_stack::get()
{
  if (current)
    return *(current - 1);
  return 0;
}

signed char operators_stack::push(const optr_hash x)
{
  if (current)
    {
      if ((long unsigned)(current - start) == size && this->increase_size() == ERROR)
	return ERROR;
      *(current++) = x;
    }
  else
    *((current = start + 1) - 1) = x;
#ifdef OPTR_DETAILS
  if (operator_detail)
    fprintf(PRINTFAST, "\nPushing     %6s\tto   location\t%lx", optr_from_hash(x), (unsigned long)(current - 1));
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
	fprintf(PRINTFAST, "\nPoping      %6s\tfrom location\t%lx", optr_from_hash(*current), (unsigned long)current);
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
  for (optr_hash *t = start; current - t; ++t)
    if (*t == H_open_bracket)
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
  optr_hash *temp = new optr_hash[size - rate];
#elif defined(ACCELERATE_UP)
  optr_hash *temp = new optr_hash[size / accelerate];
#endif
  if (temp)
    {
#if defined(SPEED_UP)
      size -= rate;
#elif defined(ACCELERATE_UP)
      size /= (--accelerate);
#endif
      if (current)
	{
	  optr_hash *x = start, *y = temp;
	  while ((unsigned long)(y - temp) < size)
	    *(y++) = *(x++);
	  current = y - 1;
	}
      delete [] this->start;
      start = temp;
      return SUCCESS;
    }
  return ERROR;
}

signed char operators_stack::increase_size()
{
#if defined(SPEED_UP)
  optr_hash *temp = new optr_hash[rate + size];
#elif defined(ACCELERATE_UP)
  optr_hash *temp = new optr_hash[(accelerate + 1) * size];
#endif
  if (temp)
    {
#if defined(SPEED_UP)
      size += rate;
#elif defined(ACCELERATE_UP)
      size *= (++accelerate);
#endif
      if (current)
	{
	  optr_hash *x = start, *y = temp;
	  while (current - x)
	    *(y++) = *(x++);
	  current = y - 1;
	}
      delete [] this->start;
      start = temp;
      return SUCCESS;
    }
  return ERROR;
}
