#include <calc_help.hpp>
#ifdef HELP_CMD
void help(strings c)
{
#ifdef FILE_MANAGER
  if (c == "file manager")
    {
      fprintf(PRINTFAST, "\n\
-> rm <file>    - removes <file>\n\
-> ls <dir>     - lists files and directories\n\
-> cd <dir>     - changes directory\n\
-> open <file>  - opens <file> in text mode\n\
-> edit <file>  - for editing <file>\n\
-> pwd          - shows present working directory");
    }
#endif
#ifdef CONST_CMDS
#ifdef FILE_MANAGER
  else
#endif
    if (c == "constants")
      {
        fprintf(PRINTFAST, "\n\
-> constant <name>=<value>  - for creating a custom constant\n\
-> show constants           - shows all constants\n\
-> remove constant <name>   - removes constant\n\
-> remove constants         - removes all constants\n\
-> load constant pi         - loads pi as a constant");
      }
#endif
#ifdef ANS_CMD
#if defined(FILE_MANAGER) || defined(CONST_CMDS)
    else
#endif
      if (c == "answers")
	{
	  fprintf(PRINTFAST, "\n\
-> start/stop storing answers  - starts/stops the storing of answers\n\
-> show/delete answers         - shows/deletes all answers\n\
-> show/delete A31             - shows/deletes answer number 31");
	}
#endif
#ifdef CALC_COLORS
#if defined(FILE_MANAGER) || defined(CONST_CMDS) || defined(ANS_CMD)
      else
#endif
	if (c == "font")
	  {
	    fprintf(PRINTFAST, "\n\
The following commands are self explanatory:\n\
-> input font color <color>\n\
-> input font background <color>\n\
-> input font style <style>\n\
-> error font color <color>\n\
-> error font background <color>\n\
-> error font style <style>\n\
-> output font color <color>\n\
-> output font background <color>\n\
-> output font style <style>\n\
-> prompt font color <color>\n\
-> prompt font background <color>\n\
-> prompt font style <style>\n\
where <color> represents one of the following:\n\
1. Black      5. Red\n\
2. Green      6. Yellow\n\
3. Blue       7. Magenta\n\
4. Cyan       8. White\n\
and <style> represents one of the folowing:\n\
1. Regular    5. Bold\n\
2. Deep       6. Italic\n\
3. Underline  7. Blink\n\
4. Negative   8. Strikeoff");
	  }
#endif
#ifdef CALC_HISTORY
#if defined(FILE_MANAGER) || defined(CONST_CMDS) || defined(ANS_CMD) || defined(CALC_COLORS)
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
	      fprintf(PRINTFAST, "\n-> show settings              - shows all settings\n");
#ifdef CLEAR_CMD
	      fprintf(PRINTFAST, "-> clear                      - clears the screen\n");
#endif
	      fprintf(PRINTFAST, "-> exit                       - quits the calculator\n");
#ifdef FACTORIZE
	      fprintf(PRINTFAST, "-> factorize <num>            - shows all factors of num\n");
#endif
#ifdef SUM
	      fprintf(PRINTFAST, "-> sum <lo_lt> <up_lt> <expr> - sums up expression having i as variable\n");
#endif
#ifdef SHELL_CMD
	      fprintf(PRINTFAST, "-> shell <command> <args>     - command is executed from shell\n\
-> shell                      - opens up shell\n");
#endif
	      fprintf(PRINTFAST, "\
-> input length N             - input string length upto N characters\n\
-> rad/deg/grad               - shows/input angle in radian/degree/grad\n\
-> show/hide e                - shows/hides exp part of a number\n\
-> precision=N                - shows precision upto N decimal places\n");
#ifdef PROMPT
	      fprintf(PRINTFAST, "-> prompt=<new>               - changes present prompt to new one\n");
#endif
#ifdef CALC_PROCESS_TIME
	      fprintf(PRINTFAST, "-> show/hide processing time  - shows/hides processing time of command\n");
#endif
#ifdef OPTR_DETAILS
	      fprintf(PRINTFAST, "-> show/hide operator details - shows/hides operator stack details\n");
#endif
#ifdef NUM_DETAILS
	      fprintf(PRINTFAST, "-> show/hide number details   - shows/hides number stack details\n");
#endif
#ifdef STEPS_CMD
	      fprintf(PRINTFAST, "-> show/hide steps            - shows/hides steps of each calculation\n");
#endif
	      fprintf(PRINTFAST, "-> show/hide e                - shows/hides exp part of a number");
	    }
	  else
	    {
#ifdef FILE_MANAGER
	      fprintf(PRINTFAST, "\nhelp file manager    - Help on file managing commands");
#endif
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
