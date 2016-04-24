#include <calc_stacks/constant_stack.hpp>
#ifdef CONSTANT_STACK_H
constant::constant()
{
	name[0] = 0, value = 0.0;
}

constant::constant(const char *c, long double val)
{
	strcpy(name, c);
	value = val;
}

void constant::display()
{
	fprintf(PRINTFAST, "%s = ", name);
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
	{
		for (constnt * t = top; t; t = t->next)
		{
			fprintf(PRINTFAST, "\n");
			t->display();
		}
	}
	else
		fprintf(PRINTFAST, Empty);
}

long double const_list::get_const(const char *x, unsigned long int &i)
{
	if (top)
	{
		long double h = 0;
		char c[15];
		unsigned long j, p;
		for (constnt * t = top; t != NULL; t = t->next)
		{
			for (j = i; ((j - i) < 15) && isalpha(x[j]); j++)
			{
				unsigned int k = 0;
				for (; k <= (j - i); k++)
					c[k] = x[i + k];
				c[k] = 0;
				if (!strcmp(c, t->name))
					h = t->value, p = j;
			}
		}
		if (h)
		{
			i = p + 1;
			return h;
		}
	}
	return 0;
}

bool const_list::insert_const(constant x)
{
	if (strcmp(x.name, ""))
	{
		if (!check_const(x.name))
		{
#ifdef CALC_COLORS
                        error_font.print();
#endif
			fprintf(PRINTFAST, "!!Constant already exists!!");
#ifdef CALC_COLORS
                        output_font.print();
#endif
			return 1;
		}
		constnt *t = new constnt;
		if (t)
		{
			t->value = x.value;
			strcpy(t->name, x.name);
			t->next = top, top = t;
			return 1;
		}
		else
			fprintf(PRINTFAST, "!!Cannot allocate memory!!");
	}
	return 0;
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
#ifdef CALC_COLORS
                error_font.print();
#endif
		fprintf(PRINTFAST, "!!Constant is not recorded yet!!");
#ifdef CALC_COLORS
                output_font.print();
#endif
	}
	else
		fprintf(PRINTFAST, Empty);
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
