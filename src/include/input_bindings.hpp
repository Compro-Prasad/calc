#include <calc_features.hpp>

#ifndef INPUT_BINDINGS_HPP
#define INPUT_BINDINGS_HPP

extern void init_readline();

class strings;
extern strings Input;

#ifdef PROMPT
extern char prompt[500];
#else
#define prompt NULL
#endif

#endif
