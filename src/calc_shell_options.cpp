#include <calc_shell_options.hpp>

#ifdef SHELL_INPUT

#include <fstream>
using namespace std;

#include <math.h>
#include <signal.h>

#include <cal.hpp>
#include <calc_history.hpp>
#include <calc_strings.hpp>
#include <input_bindings.hpp>
#include <calc_cmd_action.hpp>
#include <calc_process_time.hpp>
#include <calc_screen_manip.hpp>

#include <calc_stacks/ans_stack.hpp>
#include <calc_stacks/num_stack.hpp>
#include <calc_stacks/optr_stack.hpp>
#include <calc_stacks/constant_stack.hpp>

#define CHECK_OPTION_AMONG(short, long)					\
  ((!ret_value && *action == short) || (ret_value && !strcmp(action, long)))

bool direct_input = true;

extern const char *prog_name;

#ifdef DIRECT_INPUT
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
	  while (*(++c))
	    {
#ifdef CALC_PROCESS_TIME
	      calc_process_time(TIMER_START);
#endif
	      if ((ret_value = option_action(c, argv + i + 1)) < 0)
		break;
#ifdef CALC_PROCESS_TIME
	      calc_process_time(TIMER_STOP);
#endif

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
		Error += "\nError in option ";
	      Error += argv[i];
#ifdef CALC_COLORS
	      error_font.print(PRINTFAST);
#endif
	      fprintf(PRINTFAST, "%s", Error.str());
#ifdef CALC_COLORS
	      output_font.print();
#endif
	      fprintf(PRINTFAST, "\n");
	      Error = "";
	      continue;
	    }
	  else if (!*c)
	    ++max_ret_value;
	  i += max_ret_value - 1;
	}
      else if (*c == '#')
	continue;
      else
	{
	  Input = c;
	  fprintf(PRINTFAST, "\n%s%s", prompt, Input.str());
#ifdef CALC_COLORS
	  output_font.print();
#endif
	  cmd_action();
	  if (Error != "")
	    {
#ifdef CALC_COLORS
	      error_font.print(PRINTFAST);
#endif
	      fprintf(PRINTFAST, "%s", Error.str());
#ifdef CALC_COLORS
	      output_font.print();
#endif
	      Error = "";
	    }
	  fprintf(PRINTFAST, "\n");
	}
    }
#ifdef CALC_PROCESS_TIME
  if (calc_time == true)
    fprintf(PRINTFAST, "\n");
#endif
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
      extern char precision[15];
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
#ifdef DIRECT_INPUT
  else if (CHECK_OPTION_AMONG('w', "welcome"))
    welcome_msg = YES - negate;
#endif

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
    {
      if ((calc_avg_time = YES - negate) != 0)
	calc_process_time(TIMER_DISPLAY);
      else
	calc_process_time(TIMER_RESET);
      fprintf(PRINTFAST, "\n");
    }
#endif
#ifdef DIRECT_INPUT
  else if (CHECK_OPTION_AMONG('q', "quit") ||
	   CHECK_OPTION_AMONG('q', "exit"))
    direct_input = 0 - negate;
#endif

#ifdef CALC_HISTORY
  else if (CHECK_OPTION_AMONG('H', "ignore-history"))
    {
      long x;
      if (!strcasecmp(*action_args, "ALL"))
	x = ALL_;
      else if (!strcasecmp(*action_args, "ALL VALID"))
	x = ALL_VALID;
      else if (!strcasecmp(*action_args, "ALL INVALID"))
	x = ALL_INVALID;
      else if (!strcasecmp(*action_args, "ALL COMMANDS"))
	x = ALL_COMMANDS;
      else if (!strcasecmp(*action_args, "ALL EXPRESSIONS"))
	x = ALL_EXPRESSIONS;
      else if (!strcasecmp(*action_args, "VALID COMMANDS"))
	x = VALID_COMMANDS;
      else if (!strcasecmp(*action_args, "INVALID COMMANDS"))
	x = INVALID_COMMANDS;
      else if (!strcasecmp(*action_args, "VALID EXPRESSIONS"))
	x = VALID_EXPRESSIONS;
      else if (!strcasecmp(*action_args, "INVALID EXPRESSIONS"))
	x = INVALID_EXPRESSIONS;
      else
	{
	  Error = "!!Not a valid history type!!";
	  return -1;
	}
      record = negate ? record & ~x : record | x;
      ++ret_value;
    }
#endif

  else if (!negate)
    {
      if (CHECK_OPTION_AMONG('h', "help"))
	{
	  fprintf(PRINTFAST,
		  "USAGE:\n\t"
		  "%s [-short_options] [--long_option] [<expression>]\n\t"
#ifdef DIRECT_INPUT
		  "%s [-q]           Quits after reading all shell arguments\n\t"
		  "%s [-[N]w]        Show welcome message\n\t"
#endif
		  "%s [-f FILE]      Loads calculator's script from FILE\n\t"
#ifdef NUM_DETAILS
		  "%s [-[N]n]        Show number details\n\t"
#endif
#ifdef OPTR_DETAILS
		  "%s [-[N]q]        Show operator details\n\t"
#endif
#ifdef CALC_PROCESS_TIME
		  "%s [-[N]t]        Show processing time\n\t"
#endif
#ifdef ANS_CMD
		  "%s [-[N]a]        Store answers\n\t"
#endif
		  "%s [-[N]e]        Show exponential part if necessary\n\t"
#ifdef PROMPT
		  "%s [-p PROMPT]    Show PROMPT after each input\n\t"
#endif
#ifdef CHANGE_PRECISION
		  "%s [-P PRECISION] Show upto PRECISION decimal places\n\t"
#endif
		  "%s [-A TYPE]      TYPE should be angle of type deg/rad/grad\n\t"
#ifdef FACTORIZE
		  "%s [-F NUM]       Find all factors of NUM\n\t"
#endif
#ifdef SUM
		  "%s [-S <low_lt> <up_lt> <rate> <expr>]\n"
#endif
		  "[N] represents negation of the specific action\n"
		  "Other options and long options can be consulted from manpage\n"
		  , prog_name, prog_name, prog_name, prog_name, prog_name, prog_name
		  , prog_name, prog_name, prog_name, prog_name, prog_name, prog_name
		  , prog_name, prog_name);
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
		  Error = "Minimum length is 25";
		  return -1;
		}
	      strMAX = x + 2;
	    }
	  else
	    return -1;
	  ++ret_value;
	}
#endif

      else if (*action_args && CHECK_OPTION_AMONG('f', "file"))
	{
	  Input = *action_args;
	  ifstream f;
	  f.open(Input.str());
	  if (f)
	    {
	      while (!f.eof())
		{
		  f.getline(Input.str(), strMAX, '\n');
		  if (Input == "#")
		    continue;
		  fprintf(PRINTFAST, "\n%s%s", prompt, Input.str());
#ifdef CALC_COLORS
		  output_font.print();
#endif
		  cmd_action();
		  if (Error != "")
		    {
#ifdef CALC_COLORS
		      error_font.print(PRINTFAST);
#endif
		      fprintf(PRINTFAST, "%s", Error.str());
#ifdef CALC_COLORS
		      output_font.print();
#endif
		      Error = "";
		    }
		}
	    }
	  else
	    {
	      sprintf(Error.str(), "'%s' file could not be read\n", Input.str());
	      return -1;
	    }
	  ++ret_value;
	}
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
	  unsigned long i = 0;
	  factorize(i);
	  if (Error != "")
	    return -1;
	  fprintf(PRINTFAST, "\n");
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
#ifdef STEPS_CMD
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
			ret_value = -1;
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
#ifdef STEPS_CMD
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
	      extern char precision[15];
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
