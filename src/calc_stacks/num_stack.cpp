#include <calc_stacks/num_stack.hpp>
#ifdef CALC_NUM_STACK_H

link_numbers::link_numbers()
{
  top = 0;
}

signed char link_numbers::get(long double &y)
{
  if (top)
    {
#ifdef NUM_DETAILS
      if (num_detail == YES)
	fprintf(PRINTFAST, "\nPoping %Lf from number stack having location at %llx", top->x, (long long unsigned)top);
#endif
      number *t = top;
      y = top->x;
      top = top->next;
      delete t;
      return SUCCESS;
    }
  return ERROR;
}

signed char link_numbers::push(const long double y)
{
  number *n = new number;
  if (n)
    {
#ifdef NUM_DETAILS
      if (num_detail == YES)
	fprintf(PRINTFAST, "\nPushing %Lf in number stack having location at %llx", y, (long long unsigned)n);
#endif
      n->x = y;
      n->next = top, top = n;
      return SUCCESS;
    }
#ifdef NUM_DETAILS
  if (num_detail == YES)
    fprintf(PRINTFAST, "\nDynamic memory allocation is full");
#endif
  return ERROR;
}

void link_numbers::deallocate()
{
  if (top)
    {
#ifdef NUM_DETAILS
      if (num_detail == YES)
	fprintf(PRINTFAST, "\nLeft out numbers in stack due to some error");
#endif
      while (top)
	{
#ifdef NUM_DETAILS
	  if (num_detail == YES)
	    fprintf(PRINTFAST, "\n\t\'%Lf\' having location at %llx", top->x, (long long unsigned)top);
#endif
	  number *t = top;
	  top = top->next;
	  delete t;
	}
    }
}

#endif // CALC_NUM_STACK_H
