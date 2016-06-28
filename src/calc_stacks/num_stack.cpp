#include <stdio.h>
#include <calc_stacks/num_stack.hpp>

#ifdef NUM_DETAILS
bool num_detail;
#endif

numbers_stack::numbers_stack()
{
  size = 16;
#if defined(SPEED_UP)
  rate = 16;
#elif defined(ACCELERATE_UP)
  accelerate = 1;
#endif
  start = new long double[size];
  current = 0;
}

numbers_stack::numbers_stack(const numbers_stack &t)
{
  this->size = t.size;
#if defined(SPEED_UP)
  this->rate = t.rate;
#elif defined(ACCELERATE_UP)
  this->accelerate = t.accelerate;
#endif
  this->start = new long double[this->size];
  this->current = t.current ? this->start + (t.current - t.start) : 0;
  for (long double *temp1 = this->start, *temp2 = t.start;
       temp2 < t.current; ++temp1, ++temp2)
    *temp1 = *temp2;
}

void numbers_stack::operator=(const numbers_stack &t)
{
  if (this->start)
    delete this->start;
  this->start = new long double[this->size = t.size];
#if defined(SPEED_UP)
  this->rate = t.rate;
#elif defined(ACCELERATE_UP)
  this->accelerate = t.accelerate;
#endif
  this->current = t.current ? this->start + (t.current - t.start) : 0;
  for (long double *temp1 = this->start, *temp2 = t.start;
       temp2 < t.current; ++temp1, ++temp2)
    *temp1 = *temp2;
}

numbers_stack::~numbers_stack()
{
  this->reset();
  delete [] start;
}

signed char numbers_stack::get(long double &y)
{
  if (current)
    {
      y = *(--current);
#ifdef NUM_DETAILS
      if (num_detail)
	fprintf(PRINTFAST, "\nPoping \t%.15Lg\tfrom location\t%lx", y, (unsigned long)current);
#endif
      if (start == current)
	current = 0;
      return SUCCESS;
    }
  return ERROR;
}

signed char numbers_stack::push(const long double y)
{
  if (current)
    {
      if ((long unsigned)(current - start) == size && this->increase_size() == ERROR)
	return ERROR;
      *(current++) = y;
    }
  else
    *((current = start + 1) - 1) = y;
#ifdef NUM_DETAILS
  if (num_detail)
    fprintf(PRINTFAST, "\nPushing\t%.15Lg\tto   location\t%lx", y, (unsigned long)current - 1);
#endif
  return SUCCESS;
}

void numbers_stack::reset()
{
  current = 0;
}

signed char numbers_stack::decrease_size()
{
#if defined(SPEED_UP)
  if (size - rate > size)
#elif defined(ACCELERATE_UP)
    if (accelerate - 1 > accelerate)
#endif
      return FAILURE;

#if defined(SPEED_UP)
  long double *temp = new long double[size - rate];
#elif defined(ACCELERATE_UP)
  long double *temp = new long double[size / accelerate];
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
	  long double *x = start, *y = temp;
	  while ((unsigned long)(y - temp) < size)
	    *(y++) = *(x++);
	  current = y - 1;
	}
      delete [] start;
      start = temp;
      return SUCCESS;
    }
  return ERROR;
}

signed char numbers_stack::increase_size()
{
#if defined(SPEED_UP)
  long double *temp = new long double[rate + size];
#elif defined(ACCELERATE_UP)
  long double *temp = new long double[(accelerate + 1) * size];
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
	  long double *x = start, *y = temp;
	  while (current - x)
	    *(y++) = *(x++);
	  current = y - 1;
	}
      delete [] start;
      start = temp;
      return SUCCESS;
    }
  return ERROR;
}
