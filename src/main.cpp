#include <calc_features.hpp>

#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

#ifdef SHELL_INPUT
#include <fstream>
using namespace std;
#endif

#include <calc_colors.hpp>
#include <calc_history.hpp>
#include <input_bindings.hpp>
#include <calc_cmd_action.hpp>
#include <calc_screen_manip.hpp>
#include <calc_shell_options.hpp>

char precision[15] = "%.5Lg";/* String for storing precision */
char e[3]          = "Lg";   /* String for showing or not showing exponential */
strings Error;
unsigned long strMAX = 1000;

#ifdef CALC_HISTORY
short record = ALL_; /* Switch for (not )storing specific history types */
#endif
#ifdef DIRECT_INPUT
bool welcome_msg = true;
#endif
#ifdef SHELL_INPUT
const char *prog_name = NULL;
#endif

int main(int argc, char *argv[])
{

  prog_name = *argv;

#ifdef CALC_COLORS
  output_font.print();
#endif


#ifdef SHELL_INPUT
  /* ****************************************************************** */
  /*                     checking out shell arguments                   */
  /*                   */ parse_options(argc, argv); /*                 */
  /*                           parsing complete                         */
  /* ****************************************************************** */
  if (argc != 1)
#ifdef DIRECT_INPUT
    if (!direct_input)
#endif
      PACKUP_AND_LEAVE("");
#endif // SHELL_INPUT


#ifdef DIRECT_INPUT

  /* ******************************************************************* */
  /*                             Welcome message                         */
  if (welcome_msg)
    fprintf(PRINTFAST,
	    "This is free software with ABSOLUTELY NO WARRANTY.\n"
	    "For details type `warranty'.\n"
	    "Type help and press return to know more.");
  /* ******************************************************************* */

  init_readline();

  while (Input != "exit")
    {

      fprintf(PRINTFAST, "\n");
#ifdef PROMPT
#ifdef CALC_COLORS
      /* Setting prompt font settings */
      prompt_font.print();
#endif
      /* Displaying prompt */
      fprintf(PRINTFAST, "%s", prompt);
#endif // PROMPT
#ifdef CALC_COLORS
      /* Setting input font settings */
      input_font.print();
#endif

      Error = "";

      /* ************************************************************** */
      /*                           take input                           */
      /* */                 Input = readline(prompt);                /* */
      /* ************************************************************** */

      if (Input == "#") /* A comment  */
	continue;       /* Do nothing */

#ifdef CALC_HISTORY
      add_history(Input.str());
#endif

#ifdef CALC_COLORS
      /* Setting output font settings */
      output_font.print();
#endif

      /* ************************************************************** */
      /*                   bring the input in action                    */
      /*  */                     cmd_action();                      /*  */
      /* ************************************************************** */

      if (Error != "")
#ifdef CALC_COLORS
	{
	  error_font.print(PRINTFAST);
#endif
	  fprintf(PRINTFAST, "%s", Error.str());
#ifdef CALC_COLORS
	  output_font.print();
	}
#endif
    }
#endif // DIRECT_INPUT


  PACKUP_AND_LEAVE("");
}
