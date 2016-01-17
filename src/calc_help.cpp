#include "calc_help.h"
#ifdef HELP_CMD
void help(strings c)
{
  if (c == "file manager")
    {
      fprintf(PRINTFAST, "\n\
-> rm <file>                  - removes <file>\n\
-> ls <dir>                   - lists files and directories\n\
-> cd <dir>                   - changes directory\n\
-> open <file>                - opens <file> in text mode\n\
-> edit <file>                - for editing <file>\n\
-> pwd                        - shows present working directory");
    }
  else if (c == "constants")
    {
      fprintf(PRINTFAST, "\n\
-> constant <name>=<value>    - for creating a custom constant\n\
-> show constants             - shows all constants\n\
-> remove constant <name>     - removes constant\n\
-> remove constants           - removes all constants\n\
-> load constant pi           - loads pi as a constant");
    }
  else if (c == "answers")
    {
      fprintf(PRINTFAST, "\n\
-> start/stop storing answers - starts/stops the storing of answers\n\
-> show/delete answers        - shows/deletes all answers\n\
-> show/delete A31            - shows/deletes answer number 31");
    }
  else if (c == "font")
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
  else if (c == "command history")
    {
      fprintf(PRINTFAST, "\n\
-> allow/restrict undefined commands       - Allow/Restrict recording of undefined commands\n\
-> allow/restrict normal commands          - Allow/Restrict recording of normal commands\n\
-> allow/restrict expression commands      - Allow/Restrict recording of expression commands\n\
-> allow/restrict expressions having error - Allow/Restrict recording expression that returns an error\n\
-> <up arrow key>                          - previous command\n\
-> <down arrow key>                        - next command");
    }
  else if (c == "miscellaneous")
    {
      fprintf(PRINTFAST, "\n\
-> show settings              - shows all settings\n\
-> clear                      - clears the screen\n\
-> exit                       - quits the calculator\n\
-> help                       - shows help on calculator\n\
-> factorize <num>            - shows all factors of num\n\
-> sum <lo_lt> <up_lt> <expr> - sums up expression having i as variable\n\
-> shell <command> <args>     - command is executed from shell\n\
-> shell                      - opens up shell\n\
-> rad/deg/grad               - shows/input angle in radian/degree/grad\n\
-> show/hide e                - shows/hides exp part of a number\n\
-> precision=N                - shows precision upto N decimal places\n\
-> prompt=<new>               - changes present prompt to new one\n\
-> show/hide processing time  - shows/hides processing time of command\n\
-> show/hide operator details - shows/hides operator stack details\n\
-> show/hide number details   - shows/hides number stack details\n\
-> show/hide steps            - shows/hides steps of each calculation");
    }
  else
    {
      fprintf(PRINTFAST, "\n\
help file manager    - Help on file managing commands\n\
help constants       - Help on constant manipulating commands\n\
help answers         - Help on answer manipulating commands\n\
help font            - Help on font manipulating commands\n\
help command history - Help on command history manipulating commands\n\
help miscellaneous   - Help on miscellaneous commands");
    }
}
#endif // HELP_CMD
