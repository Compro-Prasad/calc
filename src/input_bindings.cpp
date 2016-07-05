#include <calc_features.hpp>

#include <readline/readline.h>
#include <malloc.h>

#include <calc_strings.hpp>

strings Input;

#ifdef PROMPT
char prompt[500];
#endif

static int return_pressed(int x, int input_char)
{
  if ((input_char == RETURN || input_char == NEWLINE) && rl_end)
    {
      if (rl_line_buffer[rl_end - 1] == SPACE
	  && strncasecmp(rl_line_buffer, "prompt=", 7))
	rl_line_buffer[--rl_end] = '\0';
      rl_point = rl_end;
      rl_redisplay();
      rl_done = true;
    }
  return x;
}

static int space_pressed(int x, int input_char)
{
  if (input_char == SPACE &&
      (!strncasecmp(rl_line_buffer, "prompt=", 7) ||
       (rl_point && rl_line_buffer[rl_point - 1] != SPACE &&
	(rl_point == rl_end || rl_line_buffer[rl_point] != SPACE))))
    rl_insert(x, input_char);
  return x;
}

static int do_nothing(int x, int input_char) { return x + input_char; }

void init_readline()
{
  rl_bind_key(SPACE, space_pressed);
  rl_bind_key(TAB, do_nothing);
  rl_bind_key(RETURN, return_pressed);
  rl_bind_key(NEWLINE, return_pressed);
}
