#include <calc_file.cpp"

struct variable
{
  char name[20];
  // long double value;
  variable *next;
  variable()
  {
    next = NULL;
  }
};

class var_list
{
  variable *top;
  unsigned long total_vars;
public:
  var_list();
  bool ispresent(char*);
  bool push(char*);
  const char* return_and_pop(char*);
  ~var_list();
  unsigned long ret_total_vars()
  {
    return total_vars;
  }
};

  var_list::var_list()
  {
    top = NULL;
    total_vars = 0;
  }

bool var_list::push(char* x)
{
  if (ispresent(x) == YES)
    {
      fprintf(errfile, "!!Variable \"%s\" already exists!!", x);
      return FAILURE;
    }
  else
    {
      variable *temp = new variable;
      if (temp)
	{
	  strncpy(temp->name, x, 20);
	  temp->next = top, top = temp;
	  total_vars++;
	  return SUCCESS;
	}
      else
	{
	  fprintf(errfile, "!!Stack Overflow!!");
	  return FAILURE;
	}
    }
}

const char* var_list::return_and_pop(char* x)
{
  if (top)
    {
      if (!strcmp(x, top->name))
	{
	  char c[20];
	  variable* temp = top;
	  top = top->next;
	  delete temp;
	  total_vars--;
	  return ;
	}
      else if (top->next)
	{
	  for (variable* t = top; t->next != NULL; t = t->next)
	    {
	      if (!strcmp(x, t->next->name))
		{
		  variable* z = t->next;
		  t->next = t->next->next;
		  delete z;
		  total_vars--;
		  return SUCCESS;
		}
	    }
	}
      return FAILURE;
    }
  return FAILURE;
}

bool var_list::ispresent(char* x)
{
  for (variable *i = top; i; i = i->next)
    if (!strcmp(x, i->name))
      return YES;
  return NO;
}

var_list::~var_list()
{
  for (; top; top = top->next)
    delete top;
}

class function
{
  char name[30];
  strings expr;
  var_list var;
  bool check_expr();
public:
  function();
  function(char*);
  bool init(char*);
  bool func_def();
  bool func_call(char*);
};

function::function()
{
  name[0] = '\0';
}

function::function(char* a)
{
  init(a);
}

bool function::init(char* a)
{
  unsigned long open_brackets = 0, close_brackets = 0, i = 0;
  unsigned char equals = 0, namepos = 0;
  unsigned short exprpos = 0;
  bool flag = 0;
  for (; a[i]; i++)
    {
      if (a[i] == '=')
	{
            if (open_brackets != 1 || close_brackets != 1)
	    {
              fprintf(errfile, "!!Unwanted Bracket Error!!");
	      return FAILURE;
	    }
	    equals++;
	}
      else if (a[i] == '(')
	  open_brackets++;
      else if (a[i] == ')')
	{
	  if (open_brackets <= close_brackets)
	    {
              fprintf(errfile, "!!Bracket Error!!");
              return FAILURE;
            }
	  close_brackets++;
	}
      else if
	(
	 a[i] == '[' ||
	 a[i] == '{' ||
	 a[i] == '}' ||
	 a[i] == ']'
	)
	{
	  fprintf(errfile, "!!Unsupported Brackets!!");
	  return FAILURE;
	}
      else if (equals == 1 && !ismathchar(a[i]))
	{
	  fprintf(errfile, "!!Unsupported token in expression!!");
	  return FAILURE;
	}
      if (equals > 1)
	{
	  fprintf(errfile, "!!Equals Error!!");
	  return FAILURE;
	}
      if (equals == 1)
	expr.write(a[i], exprpos++);
      if (open_brackets == 0)
	name[namepos++] = a[i];
      else if (close_brackets == 0)
	name[namepos] = '\0';
      if (open_brackets == 1)
	{
	  char temp[20];
	  unsigned char varpos = 0;
	  for (i++; a[i]; i++)
	    {
	      if
		(
		 !isalpha(a[i]) &&
		 a[i] != '_' &&
		 a[i] != ',' &&
		 a[i] != ')'
		)
		{
		  fprintf(errfile, "!!Function Defination Error!!");
		  return FAILURE;
		}
	      else if (isalpha(a[i]) || a[i] == '_')
		temp[varpos++] = a[i];
	      else if (a[i] == ',')
		{
		  temp[varpos] = '\0';
		  if (var.push(temp) == FAILURE)
		    return FAILURE;
		  else
		    varpos = temp[0] = 0;
		}
	      else if(a[i] == ')')
		{
		  close_brackets++;
		  temp[varpos] = '\0';
		  if (a[i + 1] != '=')
		    {
		      fprintf(errfile, "!!Function Defination Error!!");
		      return FAILURE;
		    }
		  if (var.push(temp) == FAILURE)
		    return FAILURE;
		  else
		    break;
		}
	    }
	}
    }
  expr.write('\0', exprpos);
}

bool function::function_def()
{
  unsigned long total_vars = var.ret_total_vars();
  char **c = new char[total_vars];
  system("\
if [ -d $HOME/.calc_function ]\n\
then\n\
if diff -q $HOME/.calc_function/\n\
else\n\
mkdir $HOME/calc_function\n\
cp function_user.cpp cal_function/functions.cpp\n\
fi\n");
  FILE* f = fopen("calc_functions/functions.cpp", "a");
  fprintf(f, "\
