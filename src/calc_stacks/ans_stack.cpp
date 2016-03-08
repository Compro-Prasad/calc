#include <calc_stacks/ans_stack.hpp>
#ifdef ANS_STACK_H
void answer::display()
{
  fprintf(PRINTFAST, " = ");
  fprintf(PRINTFAST, precision, n);
}

ans::ans()
{
  n = 0.0, next = 0;
}

link_ans::link_ans()
{
  free_list = top = 0, n = 0;
}

link_ans::~link_ans()
{
  deallocate();
}

// single answers list is to be used throughout the program

void link_ans::add_ans(const double a)
{
  if (free_list)
    {
      free_list->n = a;
      n++;
      if (top == 0)		// checking if answer list is empty
	top = free_list;	// copying the address of the first answer
      else			// if the answers list has some answers
	{
	  ans *z = top;		// another temporary pointer
	  for (; z->next != 0; z = z->next)
	    // travelling to the end of the answers list
	    ;
	  z->next = free_list;
	  // adding the newly made answer to the end of the answers list
	}
      fprintf(PRINTFAST, "[ A%ld ]", n);
      // printing the position of the newly made answer in the answers list
      free_list = free_list->next;
    }
  else
    {
      ans *temp = new ans;
      if (temp)					// memory allocated successfully
	{
	  temp->n = a;			// initialising the newly allocated memory
	  temp->next = 0;
	  n++;
	  // incrementing the size of answers list as a new answer is added
	  if (top == 0)			// checking if answer list is empty
	    top = temp;			// copying the address of the first answer
	  else					// if the answers list has some answers
	    {
	      ans *z = top;		// another temporary pointer
	      for (; z->next != 0; z = z->next)
		// travelling to the end of the answers list
		;
	      z->next = temp;
	      // adding the newly made answer to the end of the answers list
	    }
	  fprintf(PRINTFAST, "[ A%ld ]", n);
	  // printing the position of the newly made answer in the answers list
	}
      else						// if the memory is full
	fprintf(PRINTFAST, "<Answer not saved. Please delete some answers to free memory>");
    }
}

ans link_ans::get_ans_x(unsigned long x)
{
  if (top)					// answers list has some answers
    {
      unsigned long m = 1;
      for (ans * t = top; m <= n && t; m++, t = t->next)
	// traversing through the answers list
	if (m == x)			// position matching or not
	  return *t;		// returning the value if position matches
      // execution will come here iff answer is not found in the answer list
      fprintf(PRINTFAST, Not_Calc, x);
      ans k;
      return k;				// returning blank answer
    }
  else						// if answers list is empty
    {
      fprintf(PRINTFAST, Not_Calc, x);
      ans k;
      return k;				// blank answer is returned
    }
}

void link_ans::show_ans_x(unsigned long x)
{
  if (top)					// answers list has some answers
    {
      unsigned long m = 1;
      ans *t;
      // declaration is here so that it can be used outside the loop
      bool f = 1;				// a flag
      for (t = top; m <= n && t; m++, t = t->next)
	{
	  if (m == x)			// checking position match
	    {
	      f = 0;
	      char ch[20] = ". A%d = ";
	      strcat(ch, precision);
	      fprintf(PRINTFAST, ch, x, t->n);
	      break;
	      // speeding up by not traversing after answer has been found
	    }
	}
      if (f)					// answer is not in the list
#ifdef CALC_COLORS
	{
	  error_font.print();
#endif
	  fprintf(PRINTFAST, "!!Answer not found!!");
#ifdef CALC_COLORS
	  output_font.print();
	}
#endif
    }
  else
      Error = Empty;
}

void link_ans::del_ans_x(unsigned long x)
{
  if (top)					// answer list is not empty
    {
      if (x == 1)				// only one answer is there in the answer list
	{
	  ans *z = top;
	  delete z;			// deleting the 1st and the last answer
	  top = top->next;	// same as top = NULL
	  n--;				// same as n = 0
	}
      else if (top->next)
	// more than one answer is there in the answer list
	{
	  bool f = 1;			// flag
	  ans *t = top;
	  for (unsigned long m = 1; m < n && t->next; t = t->next, m++)
	    {
	      // traversal through the list
	      if (m == x - 1)	// position is found
		{
		  f = 0;		// changing the flag
		  break;
		}
	    }
	  if (f)				// out of range
	    fprintf(PRINTFAST, Invalid);
	  else				// if inside the range
	    {
	      ans *z = t->next;	// address to be deleted
	      t->next = t->next->next;
	      // leaving the address which is to be deleted by jumping to the ext address
	      delete z;
	      n--;			// after deltion reducing the size of the
	      // answers list
	    }
	}
      else					// if an unwanted error occurs
	fprintf(PRINTFAST, Invalid);
    }
  else						// if the answers list is empty
      Error = Empty;
}

void link_ans::show_all_ans()
{
  if (top)					// answers list is not empty
    {
      long m = 1;
      for (ans * t = top; t != 0; t = t->next)	// traversal through the
	// answers list
	{
	  fprintf(PRINTFAST, "\nA%ld", m++);
	  t->display();
	}
    }
  else    // if answers list is empty
      Error = Empty;
}

bool link_ans::deallocate()
{
  if (top)					// answers list is not empty
    {
      for (; top;)
	{
	  // traversal till the answers list becomes empty
	  ans *t = top;		// answer to be deleted
	  top = top->next;	// jumping to the next answer
	  delete t;
	}
      n = 0, top = 0;
      // nullifying the count and top address of answers list as the answers list is empty
      return 1;
    }
  else						// if the answers list is empty
    return 0;
}
#endif // ANS_H
