#include <calc_colors.hpp>
#ifdef CALC_COLORS_H
calc_font::calc_font(char c, char b, char s)
{
  calc_font::color = c;
  calc_font::bagnd = b;
  calc_font::style = s;
  const char *temp_str = "\e[00;37m\e[49m";
  char *i = format;
  while (*temp_str)
    *(i++) = *(temp_str++);
  *i = 0;
  calc_font::update();
}

void calc_font::print()
{
  fprintf(stderr, "\e[00;37m\e[49m%s", calc_font::format);
}

void calc_font::update()
{
  calc_font::format[3]  = style + '0';
  calc_font::format[6]  = color + '0';
  calc_font::format[11] = bagnd + '0';
  calc_font::print();
}
#endif // CALC_COLORS_H
