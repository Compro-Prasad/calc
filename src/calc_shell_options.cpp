#include <calc_shell_options.hpp>

#ifdef SHELL_INPUT

#include <fstream>
using namespace std;

#include <math.h>

#include <calc_cmd_action.hpp>
#include <calc_strings.hpp>
#include <cal.hpp>
#include <calc_input.hpp>
#include <calc_stacks/num_stack.hpp>
#include <calc_stacks/ans_stack.hpp>
#include <calc_stacks/optr_stack.hpp>
#include <calc_stacks/history_stack.hpp>
#include <calc_stacks/constant_stack.hpp>

#define CHECK_OPTION_AMONG(short, long)					\
  ((!ret_value && *action == short) || (ret_value && !strcmp(action, long)))

#ifdef DIRECT_INPUT
extern bool direct_input;
extern bool welcome_msg;
#endif

void parse_options(int argc, char *argv[])
{
  char *c;
  signed char ret_value, max_ret_value;
  for (int i = 1; i < argc; i++)
    {
      c = argv[i];
      if (*c == '-')
	{
	  ret_value = 1;
	  max_ret_value = -1;
	  while (*(++c) && (ret_value = option_action(c, argv + i + 1)) >= 0)
	    {
	      max_ret_value < ret_value ? max_ret_value = ret_value : 0;
	      if (*c == '-' || !*c)
		break;
	      else if (*c == 'N')
		++c;
	    }
	  if (ret_value == -1)
	    {
	      if (Error == "")
		Error = "Error in option ";
	      else
		Error += "Error in option ";
	      Error += argv[i];
	      return;
	    }
	  else if (!*c)
	    ++max_ret_value;
	  i += max_ret_value - 1;
	}
      else
	{
	  Input = c;
	  print_prompt();
#ifdef CALC_COLORS
	  input_font.print();
#endif
	  fprintf(PRINTFAST, "%s", Input.str());
#ifdef CALC_COLORS
	  output_font.print();
#endif
	  cmd_action();
	}
    }
}

signed char option_action(const char *action, char **action_args)
{
  signed char ret_value = 0;
  bool negate = NO;
  extern char e[3];

  if (*action == '-')
    {
      ret_value = 1;
      ++action;
    }

  if (*action == 'N')
    negate = YES, ++action;
  else if (!*action)
    return -1;

  if (CHECK_OPTION_AMONG('e', "show-exp"))
    {
      if (*(action - 1) == 'N')
	{
	  strcpy(precision, "%.5Lf");
	  strcpy(e, "Lf");
	}
      else
	{
	  strcpy(precision, "%.5Lg");
	  strcpy(e, "Lg");
	}
    }
  else if (CHECK_OPTION_AMONG('w', "welcome"))
    welcome_msg = YES - negate;
#ifdef ANS_CMD
  else if (CHECK_OPTION_AMONG('a', "store-answers"))
    store = YES - negate;
#endif
#ifdef OPTR_DETAILS
  else if (CHECK_OPTION_AMONG('o', "show-optr-details"))
    operator_detail = YES - negate;
#endif
#ifdef NUM_DETAILS
  else if (CHECK_OPTION_AMONG('n', "show-num-details"))
    num_detail = YES - negate;
#endif
#ifdef STEPS_CMD
  else if (CHECK_OPTION_AMONG('s', "show-steps"))
    steps = YES - negate;
#endif
#ifdef CALC_PROCESS_TIME
  else if (CHECK_OPTION_AMONG('t', "show-processing-time"))
    calc_time = YES - negate;
  else if (CHECK_OPTION_AMONG('r', "start-recording"))
    calc_avg_time = YES - negate;
#endif
#ifdef DIRECT_INPUT
  else if (CHECK_OPTION_AMONG('q', "quit") ||
	   CHECK_OPTION_AMONG('q', "exit"))
    direct_input = 0 - negate;
#endif
  else if (negate)
    {
#ifdef CALC_HISTORY
      if (CHECK_OPTION_AMONG('H', "ignore-history"))
	{
	  if (!strcmp(*action_args, "undef_cmd"))
	    record &= ~UNDEFINED_COMMANDS;
	  else if (!strcmp(*action_args, "normal_cmd"))
	    record &= ~NORMAL_COMMANDS;
	  else if (!strcmp(*action_args, "expr"))
	    record &= ~EXPRESSION_COMMANDS;
	  else if (!strcmp(*action_args, "error_expr"))
	    record &= ~EXPRESSIONS_HAVING_ERROR;
	  else
	    return -1;
	  ++ret_value;
	}
      else
#endif
	return -1;
    }
  else if (!negate)
    {
      if (CHECK_OPTION_AMONG('h', "help"))
	{
	  fprintf(PRINTFAST,
		  "USAGE:\n\t"
		  "calc [<expression>]\n\t"
#ifdef DIRECT_INPUT
		  "calc [-q]           Quits after reading all shell arguments\n\t"
		  "calc [-[N]w]        Show welcome message\n\t"
#endif
		  "calc [-f FILE]      Loads calculator's script from FILE\n\t"
#ifdef NUM_DETAILS
		  "calc [-[N]n]        Show number details\n\t"
#endif
#ifdef OPTR_DETAILS
		  "calc [-[N]q]        Show operator details\n\t"
#endif
#ifdef CALC_PROCESS_TIME
		  "calc [-[N]t]        Show processing time\n\t"
#endif
#ifdef ANS_CMD
		  "calc [-[N]a]        Store answers\n\t"
#endif
		  "calc [-[N]e]        Show exponential part if necessary\n\t"
#ifdef PROMPT
		  "calc [-p PROMPT]    Show PROMPT after each input\n\t"
#endif
#ifdef CHANGE_PRECISION
		  "calc [-P PRECISION] Show upto PRECISION decimal places\n\t"
#endif
		  "calc [-A TYPE]      TYPE should be angle of type deg/rad/grad\n\t"
#ifdef FACTORIZE
		  "calc [-F NUM]       Find all factors of NUM\n\t"
#endif
#ifdef SUM
		  "calc [-S <low_lt> <up_lt> <rate> <expr>]\n"
#endif
		  "[-N] represents negation of the specific action\n"
		  "Other options and long options can be consulted from manpage\n");
	}
#ifdef DIRECT_INPUT
      else if (*action_args && CHECK_OPTION_AMONG('i', "input-length"))
	{
	  unsigned long i = 0;
	  long double x = 0;
	  if (calculate(*action_args, x, i) == SUCCESS)
	    {
	      if (x < 25)
		{
		  Error = "Minimum length is 25\n";
		  return -1;
		}
	      strMAX = x + 2;
	    }
	  else
	    return -1;
	  ++ret_value;
	}
#endif
#ifdef DIRECT_INPUT
      else if (*action_args && CHECK_OPTION_AMONG('f', "file"))
	{
	  Input = *action_args;
	  ifstream f;
	  f.open(Input.str());
	  if (f)
	    {
	      while (!f.eof())
		{
		  f.getline(Input.str(), 4000, '\n');
		  print_prompt();
#ifdef CALC_COLORS
		  input_font.print();
#endif
		  fprintf(PRINTFAST, "%s", Input.str());
#ifdef CALC_COLORS
		  output_font.print();
#endif
		  cmd_action();
		  fprintf(PRINTFAST, "\n");
		}
	    }
	  else
#ifdef CALC_COLORS
	    {
	      error_font.print();
#endif
	      fprintf(stderr, "\"%s\" file could not be read\n", Input.str());
#ifdef CALC_COLORS
	      output_font.print();
	    }
#endif
	  ++ret_value;
	}
#endif
      else if (*action_args && CHECK_OPTION_AMONG('A', "angle-type"))
	{
	  if (!strcmp(*action_args, "deg"))
	    angle_type = DEG;
	  else if (!strcmp(*action_args, "rad"))
	    angle_type = RAD;
	  else if (!strcmp(*action_args, "grad"))
	    angle_type = GRAD;
	  else
	    return -1;
	  ++ret_value;
	}
#ifdef SCREEN_MANIP
      else if (CHECK_OPTION_AMONG('C', "clear"))
	clrscr();
#endif
#ifdef CALC_HISTORY
      else if (CHECK_OPTION_AMONG('h', "store-history"))
	{
	  if (!strcmp(*action_args, "undef_cmd"))
	    record |= UNDEFINED_COMMANDS;
	  else if (!strcmp(*action_args, "normal_cmd"))
	    record |= NORMAL_COMMANDS;
	  else if (!strcmp(*action_args, "expr"))
	    record |= EXPRESSION_COMMANDS;
	  else if (!strcmp(*action_args, "error_expr"))
	    record |= EXPRESSIONS_HAVING_ERROR;
	  else
	    return -1;
	  ++ret_value;
	}
#endif
#ifdef CONST_CMDS
      else if (*action_args && CHECK_OPTION_AMONG('c', "constant"))
	{
	  constant con;
	  if (isidentifier(*action_args) && ismath(con.name) != SUCCESS)
	    {
	      strncpy(con.name, *(action_args++), 21);
	      con.name[20] = 0;
	    }
	  else
	    return -1;
	  ++ret_value;
	  if (*action_args)
	    {
	      con.value = 0;
	      unsigned long i = 0;
	      if (calculate(*(action_args++), con.value, i) == SUCCESS)
		cons.insert_const(con);
	      else
		return -1;
	    }
	  else
	    return -1;
	  ++ret_value;
	}
#endif
#ifdef PROMPT
      else if (*action_args && CHECK_OPTION_AMONG('p', "prompt"))
	{
	  strncpy(prompt, *action_args, 500);
	  prompt[499] = 0;
	  ++ret_value;
	}
#endif
#ifdef FACTORIZE
      else if (*action_args && CHECK_OPTION_AMONG('F', "factorize"))
	{
	  long double x = 0, y = 0;
	  unsigned long i = 0;
	  if (calculate(*action_args, y, i) == SUCCESS)
	    {
	      y < 0 ? y = -y : 0;
	      modfl(y, &x);
	      fprintf(PRINTFAST, "Factors of %.0Lf: ", x);
	      for (long double g = 1; g <= x / 2; g++)
		if (!fmodl(x, g))
		  fprintf(PRINTFAST, "%.0Lf, ", g);
	      fprintf(PRINTFAST, "%.0Lf\n", x);
	    }
	  else
	    return -1;
	  ++ret_value;
	}
#endif
#ifdef SUM
      else if (*action_args && *(action_args + 1) && *(action_args + 2) &&
	       *(action_args + 3) && CHECK_OPTION_AMONG('S', "sum"))
	{
	  long double lower_limit;
	  unsigned long i = 0;
#ifdef OPTR_DETAILS
	  bool temp_operator_detail = operator_detail;
	  operator_detail = NO;
#endif
#ifdef ANS_CMD
	  bool temp_steps = steps;
	  steps = NO;
#endif
#ifdef NUM_DETAILS
	  bool temp_num_detail = num_detail;
	  num_detail = NO;
#endif

	  if (calculate(*(action_args++), lower_limit, i) == SUCCESS)
	    {
	      long double upper_limit;
	      i = 0, ++ret_value;
	      if (calculate(*(action_args++), upper_limit, i) == SUCCESS)
		{
		  long double rate;
		  i = 0, ret_value += 2;
		  if (calculate(*(action_args++), rate, i) == SUCCESS)
		    {
		      i = 0, ++ret_value;
		      Input = *action_args;
		      sum(lower_limit, upper_limit, rate, i);
		      if (Error != "")
			{
			  ret_value = -1;
			  Error += "\n";
			}
		      fprintf(PRINTFAST, "\n");
		    }
		  else
		    ret_value = -1;
		}
	      else
		ret_value = -1;
	    }
	  else
	    ret_value = -1;
#ifdef OPTR_DETAILS
	  operator_detail = temp_operator_detail;
#endif
#ifdef ANS_CMD
	  steps = temp_steps;
#endif
#ifdef NUM_DETAILS
	  num_detail = temp_num_detail;
#endif
	}
#endif
#ifdef CHANGE_PRECISION
      else if (*action_args && CHECK_OPTION_AMONG('P', "precision"))
	{
	  long double x = 0;
	  unsigned long i = 0;
	  if (calculate(Input.str(), x, i) == SUCCESS)
	    {
	      unsigned short n = x;
	      n %= 1000;
	      sprintf(precision, "%%.%d%s", n, e);
	    }
	  else
	    return -1;
	  ++ret_value;
	}
#endif
      else
	return -1;
    }
  else
    return -1;
  return ret_value;
}

#endif // SHELL_INPUT