#include <calc_features.hpp>

#ifdef SCREEN_MANIP

#include <signal.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include <str.hpp>
#include <calc_screen_manip.hpp>
#include <calc_strings.hpp>
#include <calc_colors.hpp>
#include <calc_input.hpp>

unsigned short max_lines, max_cols;
unsigned short cur_line, cur_col;   /* Current position of cursor while taking
				       input */

void current_pos(unsigned short &x, unsigned short &y)
{
  fwrite(CSIDSR, 1, 5, PRINTFAST);
  char c[20];
  if (fread(c, 1, 2, stdin) == 2)
    {
      x = 0, y = 0;
      while (fread(c, 1, 1, stdin) == 1 && isdigit(*c))
	y = y * 10 + *c - '0';
      while (fread(c, 1, 1, stdin) == 1 && isdigit(*c))
	x = x * 10 + *c - '0';
    }
}

void clrscr()
{
  for (unsigned short i = 0; i < max_lines; i++)
    fprintf(PRINTFAST, "\n");
  move(1, 1);
}

void get_screen_size(int sig)
{
  struct winsize win_size;
  int fd = open("/dev/tty", O_NONBLOCK);
  if (fd)
    {
      ioctl(fd, TIOCGWINSZ, &win_size);
      max_lines = win_size.ws_row;
      max_cols = win_size.ws_col;
    }
  else
    fprintf(stderr, "\nUnable to access tty device\n");
}

void change_screen_values(int sig)
{
  if (sig == SIGWINCH && cur_line)
    {
      /* Updating max_cols and max_lines */
      get_screen_size(SIGWINCH);
      /* ******************************* */

      unsigned short t1, t2;
      current_pos(t1, t2);
      unsigned long length = Input.len(), i;


      /* Updating prompt current line */
      if (max_lines < cur_prompt_line)
	cur_prompt_line = max_lines;
      else if (t2 > cur_line)
	cur_prompt_line += t2 - cur_line;
      t1 = (cur_pos + strlen(prompt)) / max_cols;
      if (t1 + cur_prompt_line > max_lines)
	cur_prompt_line =
	  (signed short)max_lines - (signed short)t1 < 0 ? 0 : max_lines - t1;
      else
	cur_prompt_line = t1 + t2;
      move(1, cur_prompt_line);
      clear_afterCU;
      print_prompt();
      /* **************************** */


      /* Printing the Input till current position */
      input_font.print();
      for (i = 0; i < cur_pos; i++)
	fprintf(PRINTFAST, "%c", Input[i]);
      /* *************************************** */


      /* Printing left out Input characters(if any)
	 This happens usually when the user is not
	 appending characters but inserting them    */
      CUsave;
      for (current_pos(t1, t2);
	   i < length && (t1 < max_cols || t2 < max_lines);
	   ++i, ++t1, t1 > max_cols ? (++t2, t1 = 1) : 0)
	fprintf(PRINTFAST, "%c", Input[i]);
      CUrestore;
      /* ****************************************** */


      /* Updating current positon of cursor */
      current_pos(cur_col, cur_line);
      /* ********************************** */
    }
  else if (sig != SIGWINCH)
    fprintf(stderr, "\nError: Unknown signal[%#x]\n", sig);
}

#endif
