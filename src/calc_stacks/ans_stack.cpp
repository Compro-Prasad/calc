#include <calc_stacks/ans_stack.hpp>

#ifdef ANS_CMD

#include <string.h>

bool store = true;              /* Whether or not to store answers */
link_ans l;                     /* Object for storing answers in stack */

extern char precision[15];

void answer::display()
{
  fprintf(PRINTFAST, " = ");
  fprintf(PRINTFAST, precision, num);
}

ans::ans()
{
  num = 0.0, next = 0;
}

link_ans::link_ans()
{
  top = end = 0, n = 0;
}

link_ans::~link_ans()
{
  deallocate();
}

unsigned long link_ans::has_ans()
{
  return n;
}

void link_ans::add_ans(const double a)
{
  ans *temp = new ans;
  if (temp)
    {
      temp->num = a;
      temp->next = 0;
      n++;

      if (top == 0)
	top = end = temp;
      else
	end->next = temp, end = temp;
      fprintf(PRINTFAST, "  [A%lu]", n);
    }
  else
    Error = "!!Cannot allocate memory!!";
}

ans link_ans::get_ans_x(unsigned long pos)
{
  if (!pos && end)
    return *end;
  ans * t = top;
  for (; t && --pos; t = t->next);
  if (pos)
    {
      fprintf(PRINTFAST, "!!Ans%ld not yet calculated and is 0!!", pos);
      ans k;
      return k;
    }
  else
    return *t;
}

void link_ans::show_ans_x(unsigned long pos)
{
  if (!top)
    {
      Error = Empty;
      return;
    }
  ans *t;
  if (pos)
    for (t = top; t && --pos; t = t->next);
  else
    t = end;
  if (pos)
    Error = "!!Answer not found!!";
  else
    {
      char printf_format_string[20] = " = ";
      strcat(printf_format_string, precision);
      fprintf(PRINTFAST, printf_format_string, t->num);
    }
}

void link_ans::del_ans_x(unsigned long pos)
{
  if (!top)
    Error = Empty;
  else
    {
      ans **t = &this->top;
      while (*t != NULL && --pos)
	t = &(*t)->next;
      if (*t != NULL && pos == 0)
	{
	  ans *ans_to_delete = *t;
	  *t = (*t)->next;
	  delete ans_to_delete;
	}
      else
	Error = "!!Position Invalid!!";
    }
}

void link_ans::show_all_ans()
{
  if (top)
    {
      unsigned long m = 1;
      for (ans * t = top; t; t = t->next)
	{
	  fprintf(PRINTFAST, "\nA%ld", m++);
	  t->display();
	}
    }
  else
    Error = Empty;
}

bool link_ans::deallocate()
{
  if (top)
    {
      for (; top;)
	{
	  ans *t = top;
	  top = top->next;
	  delete t;
	}
      n = 0, top = end = 0;
      return 1;
    }
  else
    return 0;
}

#endif // ANS_CMD
