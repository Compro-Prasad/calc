#include <calc_features.hpp>

#ifdef CALC_COLORS
#ifndef CALC_COLORS_H
#define CALC_COLORS_H

#include <stdio.h>

/* COLORS */
#define BLACK   0
#define RED     1
#define GREEN   2
#define YELLOW  3
#define BLUE    4
#define MAGENTA 5
#define CYAN    6
#define WHITE   7
#define DEFAULT 8

#define NO_OF_COLORS 9
#define NO_OF_STYLES 10

/* FONT STYLES */
#define REGULAR   0
#define BOLD      1
#define DEEP      2
#define ITALIC    3
#define UNDERLINE 4
#define BLINK     5
#define NEGATIVE  7
#define STRIKEOFF 9

const char calc_font_colors[NO_OF_COLORS][8] =
  {
    "black",
    "red",
    "green",
    "yellow",
    "blue",
    "magenta",
    "cyan",
    "white",
    "default"
  };

const char calc_font_styles[NO_OF_STYLES][10] =
  {
    "regular",
    "bold",
    "deep",
    "italic",
    "underline",
    "blink",
    "",
    "negative",
    "",
    "strikeoff"
  };

class calc_font
{
  char format[20];
public:
  char color;
  char bagnd;
  char style;
  calc_font(char, char, char);
  void print();
  void update();
};

extern calc_font input_font, prompt_font, output_font;

#endif // CALC_COLORS_H
#endif // CALC_COLORS
