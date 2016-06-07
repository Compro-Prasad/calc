#include <calc_colors.hpp>
#ifdef CALC_COLORS

#define STYLE_INDEX       6
#define TEXT_COLOR_INDEX  9
#define BACK_COLOR_INDEX 12

calc_font input_font  = calc_font( CYAN  , DEFAULT, REGULAR );
calc_font error_font  = calc_font( RED   , DEFAULT, BOLD    );
calc_font output_font = calc_font( GREEN , DEFAULT, REGULAR );
calc_font prompt_font = calc_font( YELLOW, DEFAULT, REGULAR );

calc_font::calc_font(char c, char b, char s)
{
  extern void strcpy(char *, const char *);
  strcpy(format, "\033[00;01;31;41m");
  format[TEXT_COLOR_INDEX] = '0' + (this->color = c);
  format[BACK_COLOR_INDEX] = '0' + (this->bagnd = b);
  format[STYLE_INDEX]      = '0' + (this->style = s);
}

void calc_font::print()
{
  fprintf(stderr, "%s", this->format);
}

void calc_font::update()
{
  this->format[STYLE_INDEX]      = style + '0';
  this->format[TEXT_COLOR_INDEX] = color + '0';
  this->format[BACK_COLOR_INDEX] = bagnd + '0';
  this->print();
}
#endif // CALC_COLORS
