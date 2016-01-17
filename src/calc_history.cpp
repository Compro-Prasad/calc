#include "calc_history.h"
#ifdef CALC_HISTORY_H
history::history()
{
  top = 0;
  current = (command *) - 1;
}

history::~history()
{
  command *t;
  while (top)
    {
      t = top, top = top->next;
      delete t;
    }
}

void history::display()
{
  if (top)
    for (command *t = top; t; t = t->next)
      fprintf(PRINTFAST, "\n%s", t->c.str());
}

void history::reset()
{
  current = (command *)(-1);
}

void history::push(strings cmd)
{
  command *temp = new command;
  if (temp)
    {
      reset();
      temp->c = cmd;
      temp->next = top;
      if (top)
	top->prev = temp;
      top = temp;
    }
}
void history::cmd_modify(strings cmd)
{
  if (current == (void *)-1)
    {
      command *temp = new command;
      if (temp)
	{
	  temp->c = cmd;
	  temp->next = top;
	  if (top)
	    top->prev = temp;
	  current = top = temp;
	}
    }
  else if (current)
    top->c = cmd;
}
command* history::get_prev_cmd()
{
  if (top)
    {
      if (current == (void *)-1)
	{
	  if (top->next)
	    return current = top->next;
	}
      else if (current)
	{
	  if (current->next)
	    return current = current->next;
	  else
	    {
	      fprintf(stderr, "\a");
	      return current;
	    }
	}
      fprintf(stderr, "\a");
      return top;
    }
  return 0;
}
command* history::get_next_cmd()
{
  if (top && current != (void *)-1)
    {
      if (current == top)
	return current;
      else if (current)
	return current = current->prev;
    }
  return 0;
}
void history::pop()
{
  if (top)
    {
      command *temp;
      if (current == (void *)-1)
	temp = top, top = top->next, top->prev = 0;
      else if (current)
	{
	  temp = current, current = current->next;
	  if (top->next == current)
	    {
	      top = current;
	      if (current)
		current->prev = 0;
	    }
	  else
	    {
	      if (current)
		{
		  current->prev->prev->next = current;
		  current->prev = current->prev->prev;
		}
	    }
	}
      if (!current)
	current = (command *)-1;
      delete temp;
    }
}
#endif // CALC_HISTORY_H
