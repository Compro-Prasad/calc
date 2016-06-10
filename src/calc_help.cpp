#include <calc_help.hpp>
#ifdef HELP_CMD
void help(strings c)
{
#ifdef CONST_CMDS
    if (c == "constants")
      {
        fprintf(PRINTFAST, "\n\
-> constant <name>=<value>  - for creating a custom constant\n\
-> constants                - shows all constants\n\
-> remove constant <name>   - removes constant\n\
-> remove constants         - removes all constants\n\
-> load constant pi         - loads pi as a constant");
      }
#endif
#ifdef ANS_CMD
#if defined(CONST_CMDS)
    else
#endif
      if (c == "answers")
	{
	  fprintf(PRINTFAST, "\n\
-> start/stop storing answers  - starts/stops the storing of answers\n\
-> answers                     - shows all answers\n\
-> delete answers              - deletes all answers\n\
-> delete answers leaving NUM  - deletes all answers leaving NUM of them\n\
-> show/delete A31             - shows/deletes answer number 31");
	}
#endif
#ifdef CALC_COLORS
#if defined(CONST_CMDS) || defined(ANS_CMD)
      else
#endif
	if (c == "font")
	  {
	    fprintf(PRINTFAST, "\n\
-> change <object> <attribute> <color/style>\n\n\
\
<object> :\n\t\
Input\n\t\
Output\n\t\
Error\n\t\
Prompt\n\n\
\
<attribute> :\n\t\
Color\n\t\
Background\n\t\
Style\n\n\
\
<color> :\n\t\
1. Black      5. Red\n\t\
2. Green      6. Yellow\n\t\
3. Blue       7. Magenta\n\t\
4. Cyan       8. White\n\n\
\
<style> :\n\t\
1. Regular    5. Bold\n\t\
2. Deep       6. Italic\n\t\
3. Underline  7. Blink\n\t\
4. Negative   8. Strikeoff");
	  }
#endif
#ifdef CALC_HISTORY
#if defined(CONST_CMDS) || defined(ANS_CMD) || defined(CALC_COLORS)
	else
#endif
	  if (c == "command history")
	    {
	      fprintf(PRINTFAST, "\n\
-> allow/restrict undefined commands       - Allow/Restrict recording of undefined commands\n\
-> allow/restrict normal commands          - Allow/Restrict recording of normal commands\n\
-> allow/restrict expression commands      - Allow/Restrict recording of expression commands\n\
-> allow/restrict expressions having error - Allow/Restrict recording expression that returns an error\n\
-> <up arrow key>                          - previous command\n\
-> <down arrow key>                        - next command");
	    }
#endif
	  else if (c == "miscellaneous")
	    {
	      fprintf(PRINTFAST, "\n-> settings                   - shows all settings");
#ifdef SCREEN_MANIP
	      fprintf(PRINTFAST, "\n-> clear                      - clears the screen");
#endif
	      fprintf(PRINTFAST, "\n-> exit                       - quits the calculator");
#ifdef FACTORIZE
	      fprintf(PRINTFAST, "\n-> factorize <num>            - shows all factors of num");
#endif
#ifdef SUM
	      fprintf(PRINTFAST, "\n-> sum <lo_lt> <up_lt> <rate> <expr> - sums up expression having i as variable");
#endif
#ifdef SHELL_CMD
	      fprintf(PRINTFAST, "\n-> shell <command> <args>     - command is executed from shell\n\
-> shell                      - opens up shell");
#endif
	      fprintf(PRINTFAST, "\n\
-> input length N             - input string length upto N characters\n\
-> rad/deg/grad               - shows/input angle in radian/degree/grad\n\
-> show/hide e                - shows/hides exp part of a number\n\
-> precision=N                - shows precision upto N decimal places");
#ifdef PROMPT
	      fprintf(PRINTFAST, "\n-> prompt=<new>               - changes present prompt to new one");
#endif
#ifdef CALC_PROCESS_TIME
	      fprintf(PRINTFAST, "\n-> show/hide processing time  - shows/hides processing time of command");
#endif
#ifdef OPTR_DETAILS
	      fprintf(PRINTFAST, "\n-> show/hide operator details - shows/hides operator stack details");
#endif
#ifdef NUM_DETAILS
	      fprintf(PRINTFAST, "\n-> show/hide number details   - shows/hides number stack details");
#endif
#ifdef STEPS_CMD
	      fprintf(PRINTFAST, "\n-> show/hide steps            - shows/hides steps of each calculation");
#endif
	      fprintf(PRINTFAST, "\n-> show/hide e                - shows/hides exp part of a number");
	    }
	  else
	    {
#ifdef CONST_CMDS
	      fprintf(PRINTFAST, "\nhelp constants       - Help on constant manipulating commands");
#endif
#ifdef ANS_CMD
	      fprintf(PRINTFAST, "\nhelp answers         - Help on answer manipulating commands");
#endif
#ifdef CALC_COLORS
	      fprintf(PRINTFAST, "\nhelp font            - Help on font manipulating commands");
#endif
#ifdef CALC_HISTORY
	      fprintf(PRINTFAST, "\nhelp command history - Help on command history manipulating commands");
#endif
	      fprintf(PRINTFAST, "\nhelp miscellaneous   - Help on miscellaneous commands");
	    }
}
#endif // HELP_CMD
