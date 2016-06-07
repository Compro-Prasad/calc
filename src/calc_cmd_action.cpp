#include <math.h>
#include <time.h>
#include <stdlib.h>

#include <calc_cmd_action.hpp>
#include <str.hpp>
#include <calc_features.hpp>
#include <calc_stacks/num_stack.hpp>
#include <calc_colors.hpp>
#include <cal.hpp>
#include <calc_help.hpp>
#include <calc_stacks/optr_stack.hpp>
#include <calc_stacks/constant_stack.hpp>
#include <calc_stacks/history_stack.hpp>
#include <calc_screen_manip.hpp>
#include <calc_input.hpp>

#ifdef CALC_PROCESS_TIME
bool calc_time = false;         /* Whether or not to show processing time for each calculation */
bool calc_avg_time = false;     /* Whether or not to show average processing time for a set of sequential calculations */
#endif // CALC_PROCESS_TIME

extern strings Error;                  /* String for storing errors generated after each command */

#ifdef PROMPT
extern char prompt[500];       /* String for storing prompt */
#endif // PROMPT

extern char precision[15];  /* String for storing precision */
extern char e[3];              /* String for showing or not showing exponential */

void cmd_action()
{
#ifdef CALC_PROCESS_TIME
  clock_t start;
  static long double time_taken, expressions, total_time;
  start = clock();
#endif
  strings temp_char;
#ifdef ANS_CMD
  ans k;
#endif
  if (Input == "exit" || Input == "quit")
    {
      fprintf(PRINTFAST, "\n");
      change_input_flags(1);
      exit(0);
    }
  else if (Input == "input length ")
    {
      long double x = 0;
      unsigned long i = 13;
      if (calculate(Input.str(), x, i) == SUCCESS && x > 24)
        {
	  strMAX = x + 2;
#ifdef CALC_HISTORY
	  if (!(record & NORMAL_COMMANDS))
	    h.pop();
#endif
        }
      else
#ifdef CALC_HISTORY
        {
#endif
	  if (Error != "")
	    Error += " Error!!";
	  else if (x < 25)
	    Error = "!!Minimum length is 25!!";
	  else
	    Error = "!!Invalid Expression!!";
#ifdef CALC_HISTORY
	  if (!(record & EXPRESSIONS_HAVING_ERROR))
	    h.pop();
        }
#endif
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
    calc_avg_time = YES, total_time = expressions = 0.0;
  else if (Input == "stop recording")
    {
      calc_avg_time = NO;
      fprintf(PRINTFAST, "\nAverage time = %.8Lf", (total_time / expressions));
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
  /* commands to show/hide steps */
  else if (Input == "show steps")
    steps = YES;
  else if (Input == "hide steps")
    steps = NO;
  /*******************************/
#endif

#ifdef ANS_CMD
  /* commands to manipulate storing of answers */
  else if (Input == "store answers")
    store = YES;
  else if (Input == "dont store answers")
    store = NO;
  /*********************************************/
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
      if (temp_char == "UNDEFINED COMMANDS")
	record |= UNDEFINED_COMMANDS;
      else if (temp_char == "NORMAL COMMANDS")
	record |= NORMAL_COMMANDS;
      else if (temp_char == "EXPRESSION COMMANDS")
	record |= EXPRESSION_COMMANDS;
      else if (temp_char == "EXPRESSIONS HAVING ERROR")
	record |= EXPRESSIONS_HAVING_ERROR;
    }
  else if (Input == "restrict ")
    {
      extract(Input.str(), temp_char.str(), 9, -1, NUL, 30);
      if (temp_char == "UNDEFINED COMMANDS")
	record &= ~UNDEFINED_COMMANDS;
      else if (temp_char == "NORMAL COMMANDS")
	record &= ~NORMAL_COMMANDS;
      else if (temp_char == "EXPRESSION COMMANDS")
	record &= ~EXPRESSION_COMMANDS;
      else if (temp_char == "EXPRESSIONS HAVING ERROR")
	record &= ~EXPRESSIONS_HAVING_ERROR;
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
      if (isidentifier(con.name) && ismath(con.name) != SUCCESS)
        {
	  unsigned long i = 0, d;
	  while (Input[i] != '=' && Input[i])
	    i++;
	  if (!Input[i] || !Input[i + 1])
	    Error = "!!Syntax Error!!";
	  else
            {
	      i++, con.value = 0;
	      if (separate_ans(Input.str(), i, d) == SUCCESS)
		{
		  con.value = l.get_ans_x(d).num;
		  cons.insert_const(con);
		}
	      else if (atof(Input.str(), i, con.value) == SUCCESS)
		cons.insert_const(con);
	      else
		Error = "!!Syntax error!!";
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
	fprintf(PRINTFAST, "!!Answers list empty!!");
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

#ifdef CALC_HISTORY
  else if (!strcasecmp(Input.str(), "history"))
    h.display();
#endif

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
	  if (!(record & NORMAL_COMMANDS))
	    h.pop();
#endif
        }
      else
#ifdef CALC_HISTORY
        {
#endif
	  if (Error != "")
	    Error += " Error!!";
	  else
	    Error = "!!Invalid Expression!!";
#ifdef CALC_HISTORY
	  if (!(record & EXPRESSIONS_HAVING_ERROR))
	    h.pop();
        }
#endif
    }
#endif // CHANGE_PRECISION


  else if (!strcasecmp(Input.str(), "settings"))
    {
#ifdef PROMPT
      fprintf(PRINTFAST, "\n");
      fprintf(PRINTFAST, "Prompt             =  \"%s\"", prompt);
#endif // PROMPT
#ifdef ANS_CMD
      fprintf(PRINTFAST, "\n");
      fprintf(PRINTFAST, "Storing Answers    =  %s", store == YES ? "YES" : "NO");
#endif // ANS_CMD
#ifdef CHANGE_PRECISION
      fprintf(PRINTFAST, "\n");
      fprintf(PRINTFAST, "Precision          =  \"%s\"", precision);
#endif // CHANGE_PRECISION
      fprintf(PRINTFAST, "\n");
      fprintf(PRINTFAST, "Show Exponential   =  %s", strcasecmp(e, "Lf") ? "NO" : "YES");
      fprintf(PRINTFAST, "\n");
      fprintf(PRINTFAST, "Angle Mode         =  %s", angle_type == DEG ? "DEGREE" : angle_type == GRAD ? "GRAD" : "RADIAN");
#ifdef STEPS_CMD
      fprintf(PRINTFAST, "\n");
      fprintf(PRINTFAST, "Steps              =  %s", steps == YES ? "YES" : "NO");
#endif // STEPS_CMD
#ifdef OPTR_DETAILS
      fprintf(PRINTFAST, "\n");
      fprintf(PRINTFAST, "Operator details   =  %s", operator_detail == YES ? "YES" : "NO");
#endif // OPTR_DETAILS
    }

#ifdef CALC_COLORS
  else if (Input == "input font color ")
    {
      extract(Input.str(), temp_char.str(), 17);
      bool flag = true;
      for (int j = 0; j < NO_OF_COLORS; j++)
	if (temp_char == calc_font_colors[j])
	  {
	    input_font.color = j, flag = false;
	    input_font.update();
	    break;
	  }
      if (flag)
	sprintf(Error.str(), "Error: Color mismatch");
    }
  else if (Input == "output font color ")
    {
      extract(Input.str(), temp_char.str(), strlen("output font color "));
      bool flag = true;
      for (int j = 0; j < NO_OF_COLORS; j++)
	if (temp_char == calc_font_colors[j])
	  {
	    output_font.color = j, flag = false;
	    output_font.update();
	    break;
	  }
      if (flag)
	sprintf(Error.str(), "Error: Color mismatch");
    }
  else if (Input == "error font color ")
    {
      extract(Input.str(), temp_char.str(), 17);
      bool flag = true;
      for (int j = 0; j < NO_OF_COLORS; j++)
	if (temp_char == calc_font_colors[j])
	  {
	    error_font.color = j, flag = false;
	    error_font.update();
	    break;
	  }
      if (flag)
	sprintf(Error.str(), "Error: Color mismatch");
    }
  else if (Input == "prompt font color ")
    {
      extract(Input.str(), temp_char.str(), 18);
      bool flag = true;
      for (int j = 0; j < NO_OF_COLORS; j++)
	if (temp_char == calc_font_colors[j])
	  {
	    prompt_font.color = j, flag = false;
	    prompt_font.update();
	    break;
	  }
      if (flag)
	sprintf(Error.str(), "Error: Color mismatch");
    }
  else if (Input == "input font background ")
    {
      extract(Input.str(), temp_char.str(), 23);
      bool flag = true;
      for (int j = 0; j < NO_OF_COLORS; j++)
	if (temp_char == calc_font_colors[j])
	  {
	    input_font.bagnd = j, flag = false;
	    input_font.update();
	    break;
	  }
      if (flag)
	sprintf(Error.str(), "Error: Color mismatch");
    }
  else if (Input == "output font background ")
    {
      extract(Input.str(), temp_char.str(), 23);
      bool flag = true;
      for (int j = 0; j < NO_OF_COLORS; j++)
	if (temp_char == calc_font_colors[j])
	  {
	    output_font.bagnd = j, flag = false;
	    output_font.update();
	    break;
	  }
      if (flag)
	sprintf(Error.str(), "Error: Color mismatch");
    }
  else if (Input == "error font background ")
    {
      extract(Input.str(), temp_char.str(), 22);
      bool flag = true;
      for (int j = 0; j < NO_OF_COLORS; j++)
	if (temp_char == calc_font_colors[j])
	  {
	    error_font.bagnd = j, flag = false;
	    error_font.update();
	    break;
	  }
      if (flag)
	sprintf(Error.str(), "Error: Color mismatch");
    }
  else if (Input == "prompt font background ")
    {
      extract(Input.str(), temp_char.str(), 23);
      bool flag = true;
      for (int j = 0; j < NO_OF_COLORS; j++)
	if (temp_char == calc_font_colors[j])
	  {
	    prompt_font.bagnd = j, flag = false;
	    prompt_font.update();
	    break;
	  }
      if (flag)
	sprintf(Error.str(), "Error: Color mismatch");
    }
  else if (Input == "input font style ")
    {
      extract(Input.str(), temp_char.str(), 17);
      bool flag = true;
      for (int j = 0; j < NO_OF_COLORS; j++)
	if (temp_char == calc_font_styles[j])
	  {
	    input_font.style = j, flag = false;
	    input_font.update();
	    break;
	  }
      if (flag)
	sprintf(Error.str(), "Error: Font style not defined");
    }
  else if (Input == "output font style ")
    {
      extract(Input.str(), temp_char.str(), 18);
      bool flag = true;
      for (int j = 0; j < NO_OF_STYLES; j++)
	if (temp_char == calc_font_styles[j])
	  {
	    output_font.style = j, flag = false;
	    output_font.update();
	    break;
	  }
      if (flag)
	sprintf(Error.str(), "Error: Font style not defined");
    }
  else if (Input == "error font style ")
    {
      extract(Input.str(), temp_char.str(), 17);
      bool flag = true;
      for (int j = 0; j < NO_OF_STYLES; j++)
	if (temp_char == calc_font_styles[j])
	  {
	    error_font.style = j, flag = false;
	    error_font.update();
	    break;
	  }
      if (flag)
	sprintf(Error.str(), "Error: Font style not defined");
    }
  else if (Input == "prompt font style ")
    {
      extract(Input.str(), temp_char.str(), 18);
      bool flag = true;
      for (int j = 0; j < NO_OF_STYLES; j++)
	if (temp_char == calc_font_styles[j])
	  {
	    prompt_font.style = j, flag = false;
	    prompt_font.update();
	    break;
	  }
      if (flag)
	sprintf(Error.str(), "Error: Font style not defined");
    }
#endif


#ifdef FACTORIZE
  else if (Input == "factorize " || Input == "factorise ")
    {
      long double x = 0, y = 0;
      unsigned long i = 10;
      if (calculate(Input.str(), y, i) == SUCCESS)
        {
	  y < 0 ? y = -y : 0;
	  modfl(y, &x);
	  fprintf(PRINTFAST, "\nFactors of %.0Lf: ", x);
	  for (long double g = 1; g <= x / 2; g++)
	    if (!fmodl(x, g))
	      fprintf(PRINTFAST, "%.0Lf, ", g);
	  fprintf(PRINTFAST, "%.0Lf", x);
#ifdef CALC_HISTORY
	  if (!(record & EXPRESSION_COMMANDS))
	    h.pop();
#endif
        }
      else
#ifdef CALC_HISTORY
        {
#endif
	  if (Error != "")
	    Error += " Error!!";
	  else
	    sprintf(Error.str(), "\nUndefined symbols in \'%s\'", Input.str());
#ifdef CALC_HISTORY
	  if (!(record & EXPRESSIONS_HAVING_ERROR))
	    h.pop();
        }
#endif
      num.reset();
      optr.reset();
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
#ifdef ANS_CMD
		  bool temp_steps = steps;
		  steps = NO;
#endif
#ifdef NUM_DETAILS
		  bool temp_num_detail = num_detail;
		  num_detail = NO;
#endif
		  fprintf(PRINTFAST, "\n");
		  sum(lower_limit, upper_limit, rate, i);
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
	  if (!(record & EXPRESSIONS_HAVING_ERROR))
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
#endif // ANS_CMD
#ifdef CALC_HISTORY
	  if (!(record & EXPRESSION_COMMANDS))
	    h.pop();
#endif
        }
      else if (check_calculate == ERROR)
#ifdef CALC_HISTORY
        {
#endif
	  Error += " Error!!";
#ifdef CALC_HISTORY
	  if (!(record & EXPRESSIONS_HAVING_ERROR))
	    h.pop();
        }
#endif
      else if (check_calculate == FAILURE)
#ifdef CALC_HISTORY
        {
#endif
	  sprintf(Error.str(), "\nUndefined command \"%s\"", Input.str());
#ifdef CALC_HISTORY
	  if (!(record & UNDEFINED_COMMANDS))
	    h.pop();
        }
#endif
      num.reset();
      optr.reset();
    }

  if (Error == "")
    {
      fprintf(PRINTFAST, "\n");

#ifdef CALC_PROCESS_TIME

      time_taken = ((long double)(clock() - start)) / CLOCKS_PER_SEC;

      if (calc_time == YES)
	fprintf(PRINTFAST, "Command Processing Time : %.8Lf seconds\n", time_taken);

      if (calc_time == YES && calc_avg_time == YES)
	expressions++, total_time += time_taken;
#endif // CALC_PROCESS_TIME
    }
}
