#include <calc_features.hpp>

#ifdef SHELL_INPUT

#ifndef CALC_OPTIONS_H
#define CALC_OPTIONS_H

extern void parse_options(int, char **);
extern signed char option_action(const char *action, char **action_arg);

#endif
#endif
