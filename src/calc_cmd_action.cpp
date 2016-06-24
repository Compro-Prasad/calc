#include <signal.h>

#include <cal.hpp>
#include <calc_help.hpp>
#include <calc_input.hpp>
#include <calc_colors.hpp>
#include <calc_features.hpp>
#include <calc_cmd_action.hpp>
#include <calc_process_time.hpp>
#include <calc_screen_manip.hpp>
#include <calc_stacks/ans_stack.hpp>
#include <calc_stacks/num_stack.hpp>
#include <calc_stacks/optr_stack.hpp>
#include <calc_stacks/history_stack.hpp>
#include <calc_stacks/constant_stack.hpp>

extern char precision[15];     /* String for storing precision */
extern char e[3];              /* String for showing or not showing exponential */

void cmd_action()
{

#ifdef CALC_PROCESS_TIME
  calc_process_time(TIMER_START);
#endif

  strings temp_char;

#ifdef ANS_CMD
  ans k;
#endif

  if (Input == "exit" || Input == "quit")
    PACKUP_AND_LEAVE("\n");
  else if (Input == "input length ")
    {
      long double x = 0;
      unsigned long i = 13;
      if (calculate(Input.str(), x, i) == SUCCESS && x > 24)
        {
	  strMAX = x + 2;
#ifdef CALC_HISTORY
	  if (!(record & VALID_COMMANDS))
	    h.pop();
#endif
	}
      else
        {
	  if (Error != "")
	    Error += " Error!!";
	  else if (x < 25)
	    Error = "!!Minimum length is 25!!";
	  else
	    Error = "!!Invalid Expression!!";
#ifdef CALC_HISTORY
	  if (!(record & INVALID_EXPRESSIONS))
	    h.pop();
#endif
	}
    }
  /* commands for dealing with exponentials */
  else if (Input == "show e")
    {
      strcpy(precision, "%.5Lg");
      strcpy(e, "Lg");
    }
  else if (Input == "hide e")
    {
      strcpy(precision, "%.5Lf");
      strcpy(e, "Lf");
    }
  /******************************************/
  else if (Input == "warranty")
    {
      fprintf(PRINTFAST, "\n\n\t\
This program is free software; you can redistribute it and/or modify\n\t\
it under the terms of the GNU General Public License as published by\n\t\
the Free Software Foundation; either version 2 of the License , or\n\t\
(at your option) any later version.\n\
\n\t\
This program is distributed in the hope that it will be useful,\n\t\
but WITHOUT ANY WARRANTY; without even the implied warranty of\n\t\
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\t\
GNU General Public License for more details.\n\
\n\t\
You should have received a copy of the GNU General Public License\n\t\
along with this program. If not, write to\n\
\n\t\t\
The Free Software Foundation, Inc.\n\t\t\
51 Franklin Street, Fifth Floor\n\t\t\
Boston, MA 02110-1301  USA\n");
    }

#ifdef SCREEN_MANIP
  else if (Input == "clear")
    clrscr();
#endif

#ifdef HELP_CMD
  else if (!strncasecmp(Input.str(), "help ", 5) || Input == "help")
    {
      extract(Input.str(), temp_char.str(), 5, -1, NUL, 30);
      help(temp_char);
    }
#endif

#ifdef CALC_PROCESS_TIME
  else if (Input == "show processing time")
    calc_time = YES;
  else if (Input == "hide processing time")
    calc_time = NO;
  else if (Input == "start recording")
    {
      calc_avg_time = YES;
      calc_process_time(TIMER_RESET);
    }
  else if (Input == "stop recording")
    {
      calc_avg_time = NO;
      calc_process_time(TIMER_DISPLAY);
    }
#endif

#ifdef OPTR_DETAILS
  else if (Input == "show operator details")
    operator_detail = YES;
  else if (Input == "hide operator details")
    operator_detail = NO;
#endif

#ifdef NUM_DETAILS
  else if (Input == "show number details")
    num_detail = YES;
  else if (Input == "hide number details")
    num_detail = NO;
#endif

#ifdef STEPS_CMD
  else if (Input == "show steps")
    steps = YES;
  else if (Input == "hide steps")
    steps = NO;
#endif

#ifdef ANS_CMD
  else if (Input == "store answers")
    store = YES;
  else if (Input == "dont store answers")
    store = NO;
#endif

#ifdef CHANGE_ANGLE
  /* commands for changing angle type */
  else if (Input == "deg")
    angle_type = DEG;
  else if (Input == "rad")
    angle_type = RAD;
  else if (Input == "grad")
    angle_type = GRAD;
  /************************************/
#endif // CHANGE_ANGLE

#ifdef CALC_HISTORY
  else if (Input == "allow ")
    {
      extract(Input.str(), temp_char.str(), 6, -1, NUL, 25);
      if (temp_char == "ALL")
	record |= ALL_;
      else if (temp_char == "ALL VALID")
	record |= ALL_VALID;
      else if (temp_char == "ALL INVALID")
	record |= ALL_INVALID;
      else if (temp_char == "ALL COMMANDS")
	record |= ALL_COMMANDS;
      else if (temp_char == "ALL EXPRESSIONS")
	record |= ALL_EXPRESSIONS;
      else if (temp_char == "VALID COMMANDS")
	record |= VALID_COMMANDS;
      else if (temp_char == "INVALID COMMANDS")
	record |= INVALID_COMMANDS;
      else if (temp_char == "VALID EXPRESSIONS")
	record |= VALID_EXPRESSIONS;
      else if (temp_char == "INVALID EXPRESSIONS")
	record |= INVALID_EXPRESSIONS;
      else
	Error = "!!Not a valid history type!!";
    }
  else if (Input == "restrict ")
    {
      extract(Input.str(), temp_char.str(), 9, -1, NUL, 30);
      if (temp_char == "ALL")
	record &= ~ALL_;
      else if (temp_char == "ALL VALID")
	record &= ~ALL_VALID;
      else if (temp_char == "ALL INVALID")
	record &= ~ALL_INVALID;
      else if (temp_char == "ALL COMMANDS")
	record &= ~ALL_COMMANDS;
      else if (temp_char == "ALL EXPRESSIONS")
	record &= ~ALL_EXPRESSIONS;
      else if (temp_char == "VALID COMMANDS")
	record &= ~VALID_COMMANDS;
      else if (temp_char == "INVALID COMMANDS")
	record &= ~INVALID_COMMANDS;
      else if (temp_char == "VALID EXPRESSIONS")
	record &= ~VALID_EXPRESSIONS;
      else if (temp_char == "INVALID EXPRESSIONS")
	record &= ~INVALID_EXPRESSIONS;
      else
	Error = "!!Not a valid history type!!";
    }
  else if (!strcasecmp(Input.str(), "history"))
    h.display();
#endif

#ifdef CONST_CMDS
  /* commands for dealing with constants */
  else if (!strcasecmp(Input.str(), "load constant pi"))
    {
#ifdef PI
      constant x = constant("pi", PI);
      cons.insert_const(x);
#else
      Error = "!!PI was not declared in program!!";
#endif // PI
    }
  else if (Input == "constant ")
    {
      constant con;
      extract(Input.str(), con.name, 9, -1, '=');
      if (isidentifier(con.name) && ismath(con.name) != SUCCESS)
        {
	  unsigned long i = 0;
	  while (Input[i] && Input[i++] != '=');
	  if (calculate(Input.str(), con.value, i) == SUCCESS)
#ifdef CALC_HISTORY
	    {
#endif
	      cons.insert_const(con);
#ifdef CALC_HISTORY
	      if (!(record & VALID_COMMANDS))
		h.pop();
	    }
#endif
	  else
	    {
	      if (Error != "")
		Error += " Error!!";
	      else
		Error = "!!Invalid Expression!!";
#ifdef CALC_HISTORY
	      if (!(record & INVALID_EXPRESSIONS))
		h.pop();
#endif
	    }
        }
      else
	sprintf(Error.str(), "!!%s already defined as a mathematical function!!", con.name);
    }
  else if (Input == "constants")
    cons.disp_const();
  else if (Input == "remove constant ")
    {
      char name[15];
      extract(Input.str(), name, strlen("remove constant "), 16 + 15);
      cons.delete_const(name);
    }
  else if (!strcasecmp(Input.str(), "remove constants"))
    {
      fprintf(PRINTFAST, "\nDelete all constants?(Y for yes)");
      if (getchar() == 'y')
	cons.delete_all_const();
    }
  /***************************************/
#endif // CONST_CMDS

#ifdef ANS_CMD
  /* commands for dealing with answers */
  else if (!strcasecmp(Input.str(), "answers"))
    l.show_all_ans();
  else if (Input == "show a")
    {
      unsigned long d = 0, i = 5;
      if (separate_ans(Input.str(), i, d) == SUCCESS)
	l.show_ans_x(d);
      else
	Error = "!!Syntax Error!!\nSyntax is : show A<positive integer>";
    }
  else if (!strcasecmp(Input.str(), "delete answers"))
    {
      if (!l.deallocate())
	Error = "!!Answers list empty!!";
    }
  else if (Input == "delete answers leaving ")
    {
      long double x = 0.0;
      unsigned long y, i = 23;
      if (atof(Input.str(), i, x, UNSIGNED_INT) == SUCCESS)
	if (y = x, !l.has_ans())
	  Error = "!!Answers list empty!!";
	else
	  while (l.has_ans() > y)
	    l.del_ans_x(1);
      else
	Error = "!!Syntax Error!!\nSyntax is : delete answers leaving <positive integer>";
    }
  else if (Input == "delete answers first ")
    {
      long double x = 0.0;
      unsigned long y, i = 21;
      if (atof(Input.str(), i, x, UNSIGNED_INT) == SUCCESS)
	if (y = x, !l.has_ans())
	  Error = "!!Answers list empty!!";
	else
	  while (l.has_ans() && y--)
	    l.del_ans_x(1);
      else
	Error = "!!Syntax Error!!\nSyntax is : delete answers first <positive integer>";
    }
  else if (Input == "delete a")
    {
      unsigned long d = 0, i = 7;
      if (separate_ans(Input.str(), i, d) == SUCCESS)
	l.del_ans_x(d);
      else
	Error = "!!Syntax Error!!\nSyntax is : delete A<positive integer>";
    }
  /*************************************/
#endif // ANS_CMD

#ifdef SHELL_CMD
  /* commands to deal with shell */
  else if (Input == "shell ")
    {
      extract(Input.str(), temp_char.str(), 6);
      fprintf(PRINTFAST, "\nConnecting to shell...\n");
      fprintf(PRINTFAST, "Return value %d", system(temp_char.str()));
    }
  else if (!strcasecmp(Input.str(), "shell"))
    {
      fprintf(PRINTFAST, "\nConnecting to shell...\n");
      change_input_flags(1);
      fprintf(PRINTFAST, "Return value %d", system("bash"));
      change_input_flags(0);
    }
  /*******************************/
#endif // SHELL_CMD

#ifdef PROMPT
  else if (Input == "prompt=")
    {
      extract(Input.str(), temp_char.str(), 7, -1, NUL, 500);
      strncpy(prompt, temp_char.str(), 500);
    }
#endif // PROMPT

#ifdef CHANGE_PRECISION
  else if (Input == "precision=" || Input == "precision ")
    {
      long double x = 0;
      unsigned long i = 10;
      if (calculate(Input.str(), x, i) == SUCCESS)
        {
	  unsigned short n = x;
	  n %= 1000;
	  sprintf(precision, "%%.%d%s", n, e);
#ifdef CALC_HISTORY
	  if (!(record & VALID_COMMANDS))
	    h.pop();
#endif
        }
      else
        {
	  if (Error != "")
	    Error += " Error!!";
	  else
	    Error = "!!Invalid Expression!!";
#ifdef CALC_HISTORY
	  if (!(record & INVALID_EXPRESSIONS))
	    h.pop();
#endif
	}
    }
#endif // CHANGE_PRECISION


  else if (!strcasecmp(Input.str(), "settings"))
    {
#ifdef PROMPT
      fprintf(PRINTFAST, "\nPrompt             =  \"%s\"", prompt);
#endif // PROMPT
#ifdef ANS_CMD
      fprintf(PRINTFAST, "\nStoring Answers    =  %s", store == YES ? "YES" : "NO");
#endif // ANS_CMD
#ifdef CHANGE_PRECISION
      fprintf(PRINTFAST, "\nPrecision          =  \"%s\"", precision);
#endif // CHANGE_PRECISION
      fprintf(PRINTFAST, "\nShow Exponential   =  %s", strcasecmp(e, "Lf") ? "NO" : "YES");
      fprintf(PRINTFAST, "\nAngle Mode         =  %s", angle_type == DEG ? "DEGREE" : angle_type == GRAD ? "GRAD" : "RADIAN");
#ifdef STEPS_CMD
      fprintf(PRINTFAST, "\nSteps              =  %s", steps == YES ? "YES" : "NO");
#endif // STEPS_CMD
#ifdef OPTR_DETAILS
      fprintf(PRINTFAST, "\nOperator details   =  %s", operator_detail == YES ? "YES" : "NO");
#endif // OPTR_DETAILS
    }

#ifdef CALC_COLORS
  else if (Input == "change ")
    {
      unsigned long i = 7;
      extract(Input.str(), temp_char.str(), i, -1, ' ');
      calc_font *font_t;
      char *x;
      temp_char.update_len();
      i += temp_char.len() + 1;
      if (temp_char == "input")
	font_t = &input_font;
      else if (temp_char == "output")
	font_t = &output_font;
      else if (temp_char == "error")
	font_t = &error_font;
      else if (temp_char == "prompt")
	font_t = &prompt_font;
      else
	{
	  Error = "Invalid font object";
	  return;
	}
      extract(Input.str(), temp_char.str(), i, -1, ' ');
      temp_char.update_len();
      i += temp_char.len() + 1;
      bool flag = true;
      if ((temp_char == "color" && (x = &font_t->color) != 0) ||
	  (temp_char == "background" && (x = &font_t->bagnd) != 0))
	{
	  extract(Input.str(), temp_char.str(), i);
	  for (int j = 0; j < NO_OF_COLORS; j++)
	    if (temp_char == calc_font_colors[j])
	      {
		*x = j, flag = false;
		font_t->update();
		break;
	      }
	  if (flag)
	    Error = "Error: Color mismatch";
	}
      else if (temp_char == "style")
	{
	  extract(Input.str(), temp_char.str(), i);
	  for (int j = 0; j < NO_OF_STYLES; j++)
	    if (temp_char == calc_font_styles[j])
	      {
		font_t->style = j, flag = false;
		font_t->update();
		break;
	      }
	  if (flag)
	    Error = "Error: Style mismatch";
	}
      else
	Error = "Invalid font attribute";
    }
#endif


#ifdef FACTORIZE
  else if (Input == "factorize " || Input == "factorise ")
    {
      unsigned long i = 10;
      factorize(i);
    }
#endif // FACTORIZE


#ifdef SUM
  /* Condition for calculating sum */
  else if (Input == "sum ")
    {
      long double x = 0.0;
      unsigned long i = 4;
      signed char check;
      if ((check = calculate(Input.str(), x, i, ' ', 0, 1)) == SUCCESS)
        {
	  long double lower_limit = x;
	  i++;
	  if ((check = calculate(Input.str(), x, i, ' ', 0, 1)) == SUCCESS)
	    {
	      long double upper_limit = x;
	      i++;
	      if ((check = calculate(Input.str(), x, i, ' ', 0, 1)) == SUCCESS)
		{
		  i++;
		  long double rate = x;
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
		  sum(lower_limit, upper_limit, rate, i);
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
	    }
	}
      if (check != SUCCESS)
#ifdef CALC_HISTORY
	{
#endif
	  if (Error != "")
	    Error += " Error!!";
	  else
	    sprintf(Error.str(), "\nUndefined symbols in \'%s\'", Input.str());
#ifdef CALC_HISTORY
	  if (!(record & INVALID_EXPRESSIONS))
	    h.pop();
	}
#endif
      num.reset();
      optr.reset();
    }
#endif // SUM

  else
    {
      long double x = 0.0;
      unsigned long i = 0;
      signed char check_calculate = calculate(Input.str(), x, i);
      if (check_calculate == SUCCESS)
        {
	  fprintf(PRINTFAST, " = ");
	  fprintf(PRINTFAST, precision, x);
#ifdef ANS_CMD
	  if (store == YES)
	    l.add_ans(x);
#endif
#ifdef CALC_HISTORY
	  if (!(record & VALID_EXPRESSIONS))
	    h.pop();
#endif
        }
      else if (check_calculate == ERROR)
        {
	  Error += " Error!!";
#ifdef CALC_HISTORY
	  if (!(record & INVALID_EXPRESSIONS))
	    h.pop();
#endif
	}
      else if (check_calculate == FAILURE)
#ifdef CALC_HISTORY
        {
#endif
	  sprintf(Error.str(), "\nUndefined command \"%s\"", Input.str());
#ifdef CALC_HISTORY
	  if (!(record & INVALID_COMMANDS))
	    h.pop();
        }
#endif
      num.reset();
      optr.reset();
    }

#ifdef CALC_PROCESS_TIME
  if (Error == "")
    calc_process_time(TIMER_STOP);
#endif
}
