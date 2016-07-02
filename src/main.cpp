#include <calc_features.hpp>

#include <signal.h>
#include <readline/readline.h>

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

strings Error;

#ifdef CALC_HISTORY
short record = ALL_; /* Switch for (not )storing specific history types */
#endif

unsigned long strMAX = 1000;

char precision[15] = "%.5Lg";/* String for storing precision */
char e[3] = "Lg";            /* String for showing or not showing exponential */

#ifdef DIRECT_INPUT
bool welcome_msg = true;
#endif

int main(int argc, char *argv[])
{
#ifdef CALC_COLORS
  output_font.print();
#endif

#ifdef PROMPT
  sprintf(prompt,
	  "%s"
#ifdef CALC_COLORS
	  "%s%s", prompt_font.str()
#endif
	  , ">> "
#ifdef CALC_COLORS
	  , input_font.str()
#endif
	  );
#endif // PROMPT

  init_readline();

#ifdef SHELL_INPUT


  /* ****************************************************************** */
  /*                     checking out shell arguments                   */
  /*                   */ parse_options(argc, argv); /*                 */
  /*                           parsing complete                         */
  /* ****************************************************************** */

  if (argc != 1
#ifdef DIRECT_INPUT
      && !direct_input
#endif
      )
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


  while (Input != "exit")
    {

      fprintf(PRINTFAST, "\n");

      Error = "";

      /* ************************************************************** */
      /*                           take input                           */
      /* */                 Input = readline(prompt);                /* */
      /* ************************************************************** */

#ifdef CALC_COLORS
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
