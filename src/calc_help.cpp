#include <calc_help.hpp>

#ifdef HELP_CMD

#include <calc_strings.hpp>

void help(strings c)
{
#ifdef CONST_CMDS
    if (c == "constants")
      fprintf(PRINTFAST,
	      "\n-> constant <name>=<value> - for creating a custom constant"
	      "\n-> constants               - shows all constants"
	      "\n-> remove constant <name>  - removes constant"
	      "\n-> remove constants        - removes all constants"
	      "\n-> load constant pi        - loads pi as a constant");
#endif
#ifdef ANS_CMD
#if defined(CONST_CMDS)
    else
#endif
      if (c == "answers")
	fprintf(PRINTFAST,
		"\n-> (dont) store answers       - starts/stops the storing of answers"
		"\n-> answers                    - shows all answers"
		"\n-> delete answers             - deletes all answers"
		"\n-> delete answers leaving NUM - deletes all answers leaving NUM of them"
		"\n-> show/delete A31            - shows/deletes answer number 31");
#endif
#ifdef CALC_COLORS
#if defined(CONST_CMDS) || defined(ANS_CMD)
      else
#endif
	if (c == "font")
	  fprintf(PRINTFAST,
		  "\n-> change <object> <attribute> <color/style>\n"

		  "\n<object> :"
		  "\n\tInput"
		  "\n\tOutput"
		  "\n\tError"
		  "\n\tPrompt\n"

		  "\n<attribute> :"
		  "\n\tColor"
		  "\n\tBackground"
		  "\n\tStyle\n"

		  "\n<color> :"
		  "\n\t1. Black      5. Red"
		  "\n\t2. Green      6. Yellow"
		  "\n\t3. Blue       7. Magenta"
		  "\n\t4. Cyan       8. White\n"

		  "\n<style> :"
		  "\n\t1. Regular    5. Bold"
		  "\n\t2. Deep       6. Italic"
		  "\n\t3. Underline  7. Blink"
		  "\n\t4. Negative   8. Strikeoff");
#endif
#ifdef CALC_HISTORY
#if defined(CONST_CMDS) || defined(ANS_CMD) || defined(CALC_COLORS)
	else
#endif
	  if (c == "command history")
	    {
	      fprintf(PRINTFAST, "\n\
-> allow/restrict <history_type> - Allow/Restrict recording of history types\n\
   <history_type>:\n\
\t   Valid Commands\n\
\t   Valid Expressions\n\
\t   Invalid Commands\n\
\t   Invalid Expressions\n\
\t   All Valid\n\
\t   All Invalid\n\
\t   All Commands\n\
\t   All Expressions\n\n\
-> <up arrow key>                          - previous command\n\
-> <down arrow key>                        - next command");
	    }
#endif
	  else if (c == "miscellaneous")
	    fprintf(PRINTFAST,
		    "\n-> exit                       - quits the calculator"
		    "\n-> settings                   - shows all settings"
		    "\n-> input length N             - input string length upto N characters"
		    "\n-> rad/deg/grad               - shows/input angle in radian/degree/grad"
		    "\n-> show/hide e                - shows/hides exp part of a number"
		    "\n-> show/hide e                - shows/hides exp part of a number"
		    "\n-> precision=N                - shows precision upto N decimal places"
#ifdef SCREEN_MANIP
		    "\n-> clear                      - clears the screen"
#endif
#ifdef FACTORIZE
		    "\n-> factorize <num>            - shows all factors of num"
#endif
#ifdef SUM
		    "\n-> sum <lo_lt> <up_lt> <rate> <expr> - sums up expression having i as variable"
#endif
#ifdef SHELL_CMD
		    "\n-> shell=<shell_name>         - change shell"
		    "\n-> shell <command> <args>     - command is executed from shell"
		    "\n-> shell                      - opens up a shell"
#endif
#ifdef PROMPT
		    "\n-> prompt=<new>               - changes present prompt to new one"
#endif
#ifdef CALC_PROCESS_TIME
		    "\n-> show/hide processing time  - shows/hides processing time of command"
		    "\n-> start/stop recording       - starts/stops recording processing time"
#endif
#ifdef OPTR_DETAILS
		    "\n-> show/hide operator details - shows/hides operator stack details"
#endif
#ifdef NUM_DETAILS
		    "\n-> show/hide number details   - shows/hides number stack details"
#endif
#ifdef STEPS_CMD
		    "\n-> show/hide steps            - shows/hides steps of each calculation"
#endif
		    );
	  else
	    fprintf(PRINTFAST,
		    "\nhelp miscellaneous   - Help on miscellaneous commands"
#ifdef CONST_CMDS
		    "\nhelp constants       - Help on constant manipulating commands"
#endif
#ifdef ANS_CMD
		      "\nhelp answers         - Help on answer manipulating commands"
#endif
#ifdef CALC_COLORS
		    "\nhelp font            - Help on font manipulating commands"
#endif
#ifdef CALC_HISTORY
		    "\nhelp command history - Help on command history manipulating commands"
#endif
		    );
}
#endif // HELP_CMD
