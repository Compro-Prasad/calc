#include <calc_stacks/optr_stack.hpp>
#ifdef CALC_OPTR_STACK_H

link_oprators::link_oprators()
{
  top = 0;
}

char* link_oprators::get()
{
  if (top)
    return top->c;
  return 0;
}

signed char link_oprators::push(const char *x)
{
  oprator *o = new oprator;
  if (o)
    {
#ifdef OPTR_DETAILS
      if (oprator_detail == YES)
	fprintf(PRINTFAST, "\nPushing \'%s\' in operator stack having location at %ld", x, (long)o);
#endif
      strcpy(o->c, x);
      o->next = top, top = o;
      return SUCCESS;
    }
#ifdef OPTR_DETAILS
  if (oprator_detail == YES)
    fprintf(PRINTFAST, "\nDynamic memory allocation is full");
#endif
  return ERROR;
}

signed char link_oprators::pop()
{
  if (top)
    {
#ifdef OPTR_DETAILS
      if (oprator_detail == YES)
	fprintf(PRINTFAST, "\nPoping \'%s\' operator from stack having location at %ld", top->c, (long)top);
#endif
      oprator *t = top;
      top = top->next;
      delete t;
      return SUCCESS;
    }
  return ERROR;
}

void link_oprators::deallocate()
{
  if (top)
    {
#ifdef OPTR_DETAILS
      if (oprator_detail == YES)
	fprintf(PRINTFAST, "\nLeft out operators in stack due to some error");
#endif
      while (top)
	{
#ifdef OPTR_DETAILS
	  if (oprator_detail == YES)
	    fprintf(PRINTFAST, "\n\t\'%s\' having location at %ld", top->c, (long)top);
#endif
	  oprator *t = top;
	  top = top->next;
	  delete t;
	}
    }
}

bool link_oprators::check_brac()
{
  for (oprator * t = top; t; t = t->next)
    if (!strcmp(t->c, "("))
      return 1;
  return 0;
}

#endif // CALC_OPTR_STACK_H
