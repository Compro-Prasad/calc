#include <calc_features.hpp>
#include <calc_cmd_action.hpp>
#include <calc_input.hpp>


strings Error;                  /* String for storing errors generated after each command */
link_oprators optr;             /* Object for storing operators in the stack for calculation */
link_numbers num;               /* Object for storing numbers in the stack for calculation */

#if defined(DIRECT_INPUT) || defined(SHELL_INPUT)
long strMAX = MAX_LEN;
#endif

#ifdef CALC_COLORS
calc_font input_font  = calc_font( CYAN  , DEFAULT, REGULAR );
calc_font error_font  = calc_font( RED   , DEFAULT, BOLD    );
calc_font output_font = calc_font( GREEN , DEFAULT, REGULAR );
calc_font prompt_font = calc_font( YELLOW, DEFAULT, REGULAR );
#endif // CALC_COLORS

#ifdef CALC_HISTORY
history h;                      /* Object for inserting commands in stack for further retrieval */
unsigned short record = NORMAL_COMMANDS | EXPRESSION_COMMANDS | UNDEFINED_COMMANDS | EXPRESSIONS_HAVING_ERROR; /* Switch for (not)storing specific types commands */
#endif

#ifdef ANS_CMD
bool store = true;              /* Whether or not to store answers */
link_ans l;                     /* Object for storing answers in stack */
#endif // ANS_CMD

#ifdef CONST_CMDS
const_list cons;                /* Object for storing constants in stack */
#endif // CONST_CMDS

#ifdef STEPS_CMD
bool steps = false;             /* Whether or not to show steps */
#endif // STEPS_CMD

#ifdef FILE_MANAGER
bool line_no = false;           /* Whether or not to show line numbers */
bool printpwd = false;          /* Whether or not to show pwd */
char pwd[MAX_LEN] = HOME;       /* String for storing pwd */
#endif // FILE_MANAGER

#ifdef CALC_PROCESS_TIME
bool calc_time = false;         /* Whether or not to show processing time for each calculation */
bool calc_avg_time = false;     /* Whether or not to show average processing time for a set of sequential calculations */
#endif // CALC_PROCESS_TIME

#ifdef OPTR_DETAILS
bool oprator_detail = false;    /* Whether or not to show status of operators stack */
#endif // OPTR_DETAILS

#ifdef NUM_DETAILS
bool num_detail = false;        /* Whether or not to show status of numbers stack */
#endif // NUM_DETAILS

#ifdef PROMPT
char prompt[500] = ">> ";       /* String for storing prompt */
#endif // PROMPT

unsigned char angle_type = DEG;/* Type of angle to be taken input and shown output */
char precision[15] = "%.5Lg";  /* String for storing precision */
char e[3] = "Lg";              /* String for showing or not showing exponential */

int main(int argc, char *argv[])
{
#ifdef CALC_COLORS
  output_font.print();
#endif
  strings a;

#ifdef SHELL_INPUT
  for (int index = 1; index < argc; index++)
    {
      a = argv[index];
      Error = "";
      /* option for reading commands from file */
      if (a == "-f")
        {
	  if (index < (argc - 1))
            {
	      a = argv[++index];
	      ifstream f;
	      f.open(a.str());
	      if (f)
                {
		  while (!f.eof())
                    {
		      f.getline(a.str(), 4000, '\n');
		      print_prompt();
		      fprintf(PRINTFAST, "%s ", a.str());
		      cmd_action(a.str());
                    }
                }
	      else
		sprintf(Error.str(), "\"%s\" file could not be read\n", a.str());
            }
	  else
	    sprintf(Error.str(), "(null) file can't be opened\n");
        }
      else
        {
	  print_prompt();
	  fprintf(PRINTFAST, "%s", a.str());
	  cmd_action(a.str());
        }
    }

  if (argc != 1)
    return 0;

#endif // SHELL_INPUT

#ifdef DIRECT_INPUT
  fprintf(PRINTFAST, "\
This is free software with ABSOLUTELY NO WARRANTY.\n\
For details type `warranty'.\n\
Type help and press return to know more.\n");

  /* till the user doesnt type exit the loop will go on */
  while (a != "exit")
    {
      print_prompt();

      a = "";
      Error = "";

#ifdef CALC_HISTORY
      h.reset();
#endif

#ifdef CALC_COLORS
      input_font.print();
#endif
      calc_input(a);
#ifdef CALC_COLORS
      output_font.print();
#endif
#ifdef CALC_HISTORY
      h.cmd_modify(a);
#endif
      if (a == "exit")
	break;
      else
	cmd_action(a);
      if (Error != "")
        {
#ifdef CALC_COLORS
	  error_font.print();
#endif
	  fprintf(PRINTFAST, "%s\n", Error.str());
#ifdef CALC_COLORS
	  output_font.print();
#endif
        }
    }
  /******************************************************/
#endif
#if !defined(SHELL_INPUT) && !defined(DIRECT_INPUT)
  fprintf(PRINTFAST, "No input was enabled at the time of compilation\n");
  fprintf(PRINTFAST, "Recompile with either of the following inputs enabled:\n");
  fprintf(PRINTFAST, "1) Shell Input\n");
  fprintf(PRINTFAST, "2) Direct Input");
#endif
  fprintf(PRINTFAST, "\n");
  return 0;
}
