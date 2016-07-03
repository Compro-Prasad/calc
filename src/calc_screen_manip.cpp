#include <calc_features.hpp>

#ifdef SCREEN_MANIP

#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include <calc_screen_manip.hpp>

unsigned short max_lines, max_cols;

void get_screen_size()
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

void clrscr()
{
  get_screen_size();
  fprintf(PRINTFAST, "\n\r");
  for (unsigned short i = 1; i < max_lines; i++)
    fprintf(PRINTFAST, "\n");
  move(1, 1);
}

#endif
