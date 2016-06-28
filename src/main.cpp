#include <calc_features.hpp>

#include <signal.h>

#ifdef SHELL_INPUT
#include <fstream>
using namespace std;
#endif

#include <calc_cmd_action.hpp>
#include <calc_shell_options.hpp>
#include <calc_input.hpp>
#include <calc_colors.hpp>
#include <calc_screen_manip.hpp>

#include <calc_stacks/history_stack.hpp>

strings Error;

unsigned long strMAX = 1000;

char precision[15] = "%.5Lg";/* String for storing precision */
char e[3] = "Lg";            /* String for showing or not showing exponential */

#ifdef DIRECT_INPUT
#ifdef SHELL_INPUT
bool direct_input = 1;
#endif
bool welcome_msg = true;
#endif

int main(int argc, char *argv[])
{


#ifdef CALC_COLORS
  output_font.print();
#endif


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

#ifdef SCREEN_MANIP
  unsigned short t;
  get_screen_size(0);
  if (signal(SIGWINCH, change_screen_values) == SIG_ERR)
    fprintf(stderr, "\nUnable to attach signal 'SIGWINCH'\n");
#endif


  /* ****************************************************************** */
  /* Changing input flags to prevent printing while typing and every    */
  /*      character is returned without pressing the return key         */
  /*                    */change_input_flags(0);/*                      */
  /* ****************************************************************** */


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
#ifdef SCREEN_MANIP
      current_pos(t, cur_prompt_line);
#endif
      print_prompt();

      Input = "";
      Error = "";


      /* ************************************************************** */
      /*                  input functioning begins here                 */
#ifdef CALC_HISTORY
      /*    reset the position of history scroller to a new position    */
      /*  */                      h.reset();                        /*  */
#endif
#ifdef CALC_COLORS
      /*              change to input font characteristics              */
      /*  */                 input_font.print();                    /*  */
#endif
      /*                      start taking in input                     */
      /*  */                    calc_input();                       /*  */
#ifdef CALC_COLORS
      /*            reset font characteristics to output mode           */
      /*  */                 output_font.print();                   /*  */
#endif
      /*                           Input over                           */
      /* ************************************************************** */


      /* ************************************************************** */
      /*                   bring the input in action                    */
      /*  */                     cmd_action();                      /*  */
      /* ************************************************************** */


      /* ************************************************************** */
      /*                     if an error occured                        */
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
      /*                         then print it                          */
      /*                                                                */
      /*                   input fuctioning over(reloop)                */
      /* ************************************************************** */
    }
#endif // DIRECT_INPUT


  PACKUP_AND_LEAVE("");
}
