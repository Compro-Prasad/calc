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

#include <calc_stacks/optr_stack.hpp>
#include <calc_stacks/num_stack.hpp>
#include <calc_stacks/history_stack.hpp>
#include <calc_stacks/constant_stack.hpp>
#include <calc_stacks/ans_stack.hpp>

strings Error;

unsigned long strMAX = 1000;

char precision[15] = "%.5Lg";  /* String for storing precision */
char e[3] = "Lg";              /* String for showing or not showing exponential */

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


  /* ****************************************************************** */
  /*                          if an error occured                       */
  if (Error != "")
#ifdef CALC_COLORS
  {
    error_font.print();
#endif
    fprintf(PRINTFAST, "%s\n", Error.str());
#ifdef CALC_COLORS
    output_font.print();
  }
#endif
  /*                                print it                            */
  /* ****************************************************************** */


  if (argc != 1
#ifdef DIRECT_INPUT
      && !direct_input
#endif
      )
    return 0;


#endif // SHELL_INPUT


#ifdef DIRECT_INPUT


#ifdef SCREEN_MANIP
  unsigned short t;
  get_screen_size(0);
  if (signal(SIGWINCH, change_screen_values) == SIG_ERR)
    fprintf(stderr, "\nUnable to catch signal\n");
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
	    "Type help and press return to know more.\n");
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
      /*   reset the positioning of history scroller to a new position  */
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
	  error_font.print();
#endif
	  fprintf(PRINTFAST, "%s\n", Error.str());
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


  fprintf(PRINTFAST, "\n");


  change_input_flags(1);


  return 0;
}
