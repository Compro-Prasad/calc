#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>

#include <calc_features.hpp>
#include <chatr.hpp>
#include <calc_input.hpp>
#include <calc_colors.hpp>
#include <calc_stacks/history_stack.hpp>
#include <calc_screen_manip.hpp>
#include <calc_strings.hpp>

strings Input;

#ifdef SCREEN_MANIP
unsigned short cur_prompt_line;
unsigned long cur_pos = 0;
#endif

#ifdef PROMPT
char prompt[500] = ">> "; /* String for storing prompt */
#endif // PROMPT

/* Copied from source code of conio.h
 * in C4droid app on Android
 * And later modified on 28 May 2016
 */
void change_input_flags(int yn)
{
  struct termios oldt, newt;
  tcgetattr(0, &oldt);
  newt = oldt;
  if (!yn)
    newt.c_lflag &= ~ICANON & ~ECHO;
  else
    newt.c_lflag |= ICANON | ECHO;
  tcsetattr(0, TCSANOW, &newt);
}
/* ******************************* */

void print_prompt()
{
#ifdef PROMPT
  /* show prompt */
#ifdef CALC_COLORS
  prompt_font.print();
#endif
  fprintf(PRINTFAST, "%s", prompt);
#ifdef CALC_COLORS
  output_font.print();
#endif
  /***************/
#endif // PROMPT
}

void calc_input()
{
  bool space_flag = 1;
  register char ch = 0, tempch = 0;
  register unsigned long shift = 1;
  register unsigned long z, temp;
#ifdef SCREEN_MANIP
  unsigned short t1, t2;
  current_pos(cur_col, cur_line);
#endif
  Input = "";
  for (register unsigned long i = 0;;)
    {
#ifdef SCREEN_MANIP
      cur_pos = i;
#endif
      if (tempch && !(i % 5))
	fflush(stdin);
      /* single character as input */
      ch = getchar();

#ifdef CALC_HISTORY
      if (!i)  h.cmd_modify(Input);
#endif

      /* processing of character according to condition */
      if (ch == ESC)
        {
	  tempch = ESC;
	  continue;
        }
      if (tempch == ESC && ch == '[')
        {
	  ch = getchar();


	  /* When Right Arrow Key is pressed */
	  if (ch == 'C')
            {
	      if (shift > 1)
                {
#ifdef SCREEN_MANIP
		  cur_col = cur_col == max_cols ? 1 : cur_col + 1;
		  if (cur_line == max_lines && !(cur_col >> 1))
		    {
		      for (z = i; Input[z] && cur_col <= max_cols; ++z, ++cur_col)
			fprintf(PRINTFAST, "%c", Input[z]);
		      fprintf(PRINTFAST, "\r"), cur_col = 1;
		    }
#endif
		  shift--, tempch = 0;
		  fprintf(PRINTFAST, "%c", Input[i++]);
                }
	      continue;
            }


	  /* When Left Arrow Key is pressed */
	  if (ch == 'D')
            {
	      if (shift <= Input.len())
                {
#ifdef SCREEN_MANIP
		  if (cur_col == 1 && cur_line == 1)
		    scroll_down;
		  DEC_CUR_POS;
		  if (cur_col == max_cols && cur_line == 1)
		    {
		      if (cur_pos < max_cols)
#ifdef CALC_COLORS
			{
			  prompt_font.print();
#endif
			  for (z = strlen(prompt) - cur_pos; prompt[z]; --z)
			    fprintf(PRINTFAST, "%c", prompt[z]);
#ifdef CALC_COLORS
			  input_font.print();
			}
#endif
		      z = cur_pos < max_cols ? 0 : cur_pos - max_cols;
		      Input.print(z, cur_pos);
		    }
		  move(cur_col, cur_line);
#endif
		  --i, ++shift, tempch = 0;
#ifndef SCREEN_MANIP
		  fprintf(PRINTFAST, "\b");
#endif
                }
	      continue;
            }


#ifdef CALC_HISTORY
	  /* When Up/Down Arrow Key is pressed */
	  if (ch == 'A' || ch == 'B')
            {
	      command *t = ch == 'A' ? h.get_prev_cmd() : h.get_next_cmd();
	      if (t && t->c != Input)
                {
		  shift = 1;
		  i = t->c.len();
		  temp = Input.len();
		  Input = t->c.str();
		  fprintf(PRINTFAST, "\r");
		  print_prompt();
#ifdef CALC_COLORS
		  input_font.print();
#endif
		  fprintf(PRINTFAST, "%s", Input.str());
#ifdef SCREEN_MANIP
		  current_pos(cur_col, cur_line);
		  CUsave;
#endif
		  for (z = temp - i
#ifdef SCREEN_MANIP
			 , t1 = cur_col, t2 = cur_line
#endif
			 ;
		       z > 0
#ifdef SCREEN_MANIP
			 && (t1 < max_cols || t2 < max_lines)
#endif
			 ;
		       --z
#ifdef SCREEN_MANIP
			 , t1 = t1 == max_cols ? 1 : t1 + 1,
			 t2 < max_lines ? ++t2 : 0
#endif
		       )
		    fprintf(PRINTFAST, " ");
#ifdef SCREEN_MANIP
		  CUrestore;
#else
		  for (z = temp - i; z > 0; --z)
		    fprintf(PRINTFAST, "\b");
#endif
                }
	      continue;
            }
#endif // CALC_HISTORY

	  /* If Home Key is pressed */
	  if (ch == 'H')
            {
	      if (shift <= Input.len())
                {
		  i = 0, shift = Input.len() + 1, tempch = 0;
		  fprintf(PRINTFAST, "\r");
		  print_prompt();
#ifdef CALC_COLORS
		  input_font.print();
#endif
                }
	      continue;
            }

	  /* If End Key is pressed */
	  if (ch == 'F')
            {
	      if (shift > 1)
                {
		  shift = 1, i = Input.len(), tempch = 0;
		  fprintf(PRINTFAST, "\r");
		  print_prompt();
#ifdef CALC_COLORS
		  input_font.print();
#endif
		  fprintf(PRINTFAST, "%s", Input.str());
                }
	      continue;
            }

	  tempch = 0;
	  fflush(stdin);
        }
      if ((ch >= ' ' && ch <= DEL) || ch == LF)
        {
	  /* if a space is the input */
	  if (ch != ' ' || (i && Input[i - 1] != ' '))
	    space_flag = 1;
	  else
	    space_flag = 0;
	  /* *********************** */


	  /* When return[enter] key is the input
	     prepare for evacuation              */
	  if (ch == LF)
            {
	      /* Don't leave if Input is empty */
	      if (!Input[0])
		continue/* taking Input */;
	      /* ***************************** */


	      /* Dumping all Input to output screen
		 if user was inserting instead of appending */
	      while (shift)
		fprintf(PRINTFAST, "%c", Input[i++]), --shift;
	      /* ****************************************** */


	      /* Remove trailing space if any just leaving a single case */
	      if (Input[i - 2] == ' ' && Input != "prompt=")
                {
		  Input.write(0, i - 2);
		  fprintf(PRINTFAST, "\b");
                }
	      /* ******************************************************* */


#ifdef CALC_HISTORY
	      h.cmd_modify(Input); // Modify the history in case of changes
#endif
	      break /* the loop */ ;
            }
	  /* *********************************** */


	  /* if a backspace is the input */
	  if (ch == DEL)
            {
	      /* Dont join the two if conditions using and(&&)
		 It is a protection so that none other than
		 printing characters are passed to the else
		 condition
		 if i is zero then there is nothing to delete
		 so */ if (i > 0)
		{
		  Input.del(--i);
#ifdef CALC_HISTORY
		  h.cmd_modify(Input);
#endif
		  /* remove a character from output screen */
#ifdef SCREEN_MANIP
		  DEC_CUR_POS;
		  move(cur_col, cur_line);
		  CUsave;
#else
		  fprintf(PRINTFAST, "\b");
#endif
		  z = i;
		  Input.print(z);
#ifdef SCREEN_MANIP
		  if (z < Input.len())
		    fprintf(PRINTFAST, "%c", Input[z]);
		  else
#endif
		    fprintf(PRINTFAST, " ");
#ifdef SCREEN_MANIP
		  CUrestore;
#else
		  temp = Input.len();
		  for (z = i - 1; z < temp; ++z)
		    fprintf(PRINTFAST, "\b");
#endif
		}
	    }

	  else if (i < strMAX - 2 && space_flag) /* for other characters */
            {
#ifdef SCREEN_MANIP
	      INC_CUR_POS;
#endif
	      fprintf(PRINTFAST, "%c", ch);
	      Input.shift_right(i - 1);
	      Input.write(ch, i++);
#ifdef CALC_HISTORY
	      h.cmd_modify(Input);
#endif
	      z = i;
	      Input.print(z);
#ifdef SCREEN_MANIP
	      move(cur_col, cur_line);
#else
	      temp = Input.len();
	      for (z = i; z < temp; ++z)
		fprintf(PRINTFAST, "\b");
#endif
	    }
	}
    }
#ifdef SCREEN_MANIP
  cur_line = 0;
#endif
}
