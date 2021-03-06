#include <stdio.h>
#include <readline/history.h>

#include <str.hpp>
#include <calc_help.hpp>
#include <calculate.hpp>
#include <parse_expr.hpp>
#include <calc_colors.hpp>
#include <calc_history.hpp>
#include <calc_features.hpp>
#include <input_bindings.hpp>
#include <other_calc_func.hpp>
#include <calc_cmd_action.hpp>
#include <calc_process_time.hpp>
#include <calc_screen_manip.hpp>

#include <calc_stacks/ans_stack.hpp>
#include <calc_stacks/num_stack.hpp>
#include <calc_stacks/optr_stack.hpp>
#include <calc_stacks/constant_stack.hpp>

extern char precision[15];     /* String for storing precision */
extern char e[3];              /* String for showing or not showing exponential */

#ifdef SHELL_CMD
char Shell[200] = "bash";
#endif

void cmd_action()
{

#ifdef CALC_PROCESS_TIME
  calc_process_time(TIMER_START);
#endif

  strings temp_char;

#ifdef ANS_CMD
  ans k;
#endif

  if (!strcasecmp(Input.str(), "exit") || !strcasecmp(Input.str(), "quit"))
    PACKUP_AND_LEAVE("\n");
  else if (Input == "input length ")
    {
      long double x = 0;
      unsigned long i = 13;
      if (parse_expr(Input.str(), x, i) == SUCCESS && x > 24)
	{
	  strMAX = x + 2;
	  if (!Input.newsize(strMAX))
	    {
	      strMAX -= 2;
	      fprintf(stderr, "\nPlease Wait\nResizing input length to fit in memory");
	    }
	  while (!Input.newsize(strMAX))
	    strMAX -= 2;
	}
      else if (Error != "");
      else if (x < 25)
	Error = "!!Minimum length is 25!!";
      else
	Error = "!!Invalid Expression!!";
    }

  /* commands for dealing with exponentials */
  else if (!strcasecmp(Input.str(), "show e"))
    {
      strcpy(precision, "%.5Lg");
      strcpy(e, "Lg");
    }
  else if (!strcasecmp(Input.str(), "hide e"))
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
  else if (!strcasecmp(Input.str(), "clear"))
    clrscr();
#endif

#ifdef HELP_CMD
  else if (!strcasecmp(Input.str(), "help") || Input == "help ")
    {
      extract(Input.str(), temp_char.str(), 5, -1, '\0', 30);
      help(temp_char);
    }
#endif

#ifdef CALC_PROCESS_TIME
  else if (!strcasecmp(Input.str(), "show processing time"))
    calc_time = YES;
  else if (!strcasecmp(Input.str(), "hide processing time"))
    calc_time = NO;
  else if (!strcasecmp(Input.str(), "start recording"))
    {
      calc_avg_time = YES;
      calc_process_time(TIMER_RESET);
    }
  else if (!strcasecmp(Input.str(), "stop recording"))
    {
      calc_avg_time = NO;
      calc_process_time(TIMER_DISPLAY);
    }
#endif

#ifdef OPTR_DETAILS
  else if (!strcasecmp(Input.str(), "show operator details"))
    operator_detail = YES;
  else if (!strcasecmp(Input.str(), "hide operator details"))
    operator_detail = NO;
#endif

#ifdef NUM_DETAILS
  else if (!strcasecmp(Input.str(), "show number details"))
    num_detail = YES;
  else if (!strcasecmp(Input.str(), "hide number details"))
    num_detail = NO;
#endif

#ifdef STEPS_CMD
  else if (!strcasecmp(Input.str(), "show steps"))
    steps = YES;
  else if (!strcasecmp(Input.str(), "hide steps"))
    steps = NO;
#endif

#ifdef ANS_CMD
  else if (!strcasecmp(Input.str(), "store answers"))
    store = YES;
  else if (!strcasecmp(Input.str(), "dont store answers"))
    store = NO;
#endif

#ifdef CHANGE_ANGLE
  else if (!strcasecmp(Input.str(), "deg"))
    angle_type = DEG;
  else if (!strcasecmp(Input.str(), "rad"))
    angle_type = RAD;
  else if (!strcasecmp(Input.str(), "grad"))
    angle_type = GRAD;
#endif

#ifdef CALC_HISTORY
  else if (Input == "allow ")
    {
      extract(Input.str(), temp_char.str(), 6, -1, '\0', 25);
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
      extract(Input.str(), temp_char.str(), 9, -1, '\0', 30);
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
      if (isidentifier(con.name) && ismath(generate_hash_key(con.name)) != SUCCESS)
        {
	  unsigned long i = 0;
	  while (Input[i] && Input[i++] != '=');
	  if (parse_expr(Input.str(), con.value, i) == SUCCESS)
	    cons.insert_const(con);
	  else if (Error == "")
	    Error = "!!Invalid Expression!!";
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
      if (atof(Input.str(), i, x, data_type::UNSIGNED_INT) == SUCCESS)
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
      if (atof(Input.str(), i, x, data_type::UNSIGNED_INT) == SUCCESS)
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
  else if (Input == "shell=")
    extract(Input.str(), Shell, 6, -1, 0, 200);
  else if (Input == "shell ")
    {
      extract(Input.str(), temp_char.str(), 6);
      fprintf(PRINTFAST, "\nConnecting to shell...%s\n", CSI"00;37;40m");
      output_font.print();
      fprintf(PRINTFAST, "Return value %d", system(temp_char.str()));
    }
  else if (!strcasecmp(Input.str(), "shell"))
    {
      fprintf(PRINTFAST, "\nConnecting to shell...%s\n", CSI"00;37;40m");
      output_font.print();
      fprintf(PRINTFAST, "Return value %d", system(Shell));
    }
#endif // SHELL_CMD

#ifdef PROMPT
  else if (Input == "prompt=")
    {
      extract(Input.str(), temp_char.str(), 7, -1, '\0', 500);
      strncpy(prompt, temp_char.str(), 500);
    }
#endif // PROMPT

#ifdef CHANGE_PRECISION
  else if (Input == "precision=" || Input == "precision ")
    {
      long double x = 0;
      unsigned long i = 10;
      if (parse_expr(Input.str(), x, i) == SUCCESS)
        {
	  unsigned short n = x;
	  n %= 1000;
	  sprintf(precision, "%%.%d%s", n, e);
        }
      else if (Error == "")
	Error = "!!Invalid Expression!!";
    }
#endif // CHANGE_PRECISION


  else if (!strcasecmp(Input.str(), "settings"))
    {
      fprintf(PRINTFAST, "\nInput length       =  %lu", strMAX);
#ifdef PROMPT
      fprintf(PRINTFAST, "\nPrompt             =  '%s'", prompt);
#endif // PROMPT
#ifdef ANS_CMD
      fprintf(PRINTFAST, "\nStoring Answers    =  %s", store == YES ? "YES" : "NO");
#endif // ANS_CMD
#ifdef CHANGE_PRECISION
      fprintf(PRINTFAST, "\nPrecision          =  '%s'", precision);
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
#endif // CALC_COLORS


#ifdef FACTORIZE
  else if (Input == "factorize " || Input == "factorise ")
    {
      unsigned long i = 10;
      factorize(i);
#ifdef CALC_PROCESS_TIME
      calc_process_time(TIMER_STOP);
#endif
    }
#endif


#ifdef SUM
  /* Condition for calculating sum */
  else if (Input == "sum ")
    {
      long double x = 0.0;
      unsigned long i = 4;
      signed char check;
      if ((check = parse_expr(Input.str(), x, i, ' ', 0, 1)) == SUCCESS)
        {
	  long double lower_limit = x;
	  i++;
	  if ((check = parse_expr(Input.str(), x, i, ' ', 0, 1)) == SUCCESS)
	    {
	      long double upper_limit = x;
	      i++;
	      if ((check = parse_expr(Input.str(), x, i, ' ', 0, 1)) == SUCCESS)
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
#ifdef CALC_HISTORY
		  if (!(record & VALID_EXPRESSIONS) && Error == "")
		    remove_history(history_get_history_state()->length - 1);
#endif
#ifdef OPTR_DETAILS
		  operator_detail = temp_operator_detail;
#endif
#ifdef STEPS_CMD
		  steps = temp_steps;
#endif
#ifdef NUM_DETAILS
		  num_detail = temp_num_detail;
#endif
#ifdef CALC_PROCESS_TIME
		  calc_process_time(TIMER_STOP);
#endif
		}
	    }
	}
      if (check != SUCCESS && Error == "")
	sprintf(Error.str(), "\nUndefined symbols in \'%s\'", Input.str());
      return;
    }
#endif // SUM

  else
    {
      long double x = 0.0;
      unsigned long i = 0;
      if (parse_expr(Input.str(), x, i) == SUCCESS)
        {
	  fprintf(PRINTFAST, " = ");
	  fprintf(PRINTFAST, precision, x);
#ifdef ANS_CMD
	  if (store == YES)
	    l.add_ans(x);
#endif
#ifdef CALC_HISTORY
	  if (!(record & VALID_EXPRESSIONS))
	    remove_history(history_get_history_state()->length - 1);
#endif
#ifdef CALC_PROCESS_TIME
	  calc_process_time(TIMER_STOP);
#endif
        }
      else if (Error == "")
	{
	  sprintf(Error.str(), "\nUndefined command \"%s\"", Input.str());
#ifdef CALC_HISTORY
	  if (!(record & INVALID_COMMANDS))
	    remove_history(history_get_history_state()->length - 1);
#endif
	}
      return;
    }

  if (Error == "")
    {
#ifdef CALC_HISTORY
      if (!(record & VALID_COMMANDS))
	remove_history(history_get_history_state()->length - 1);
#endif
    }
}
