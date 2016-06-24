#include <calc_features.hpp>

#ifdef CALC_PROCESS_TIME

#ifndef CALC_PROCESS_TIME_H
#define CALC_PROCESS_TIME_H

extern void calc_process_time(char sig);

extern bool calc_time;         /* Whether or not to show processing time for each calculation */
extern bool calc_avg_time;     /* Whether or not to show average processing time for a set of sequential calculations */

#define TIMER_START   0
#define TIMER_STOP    1
#define TIMER_RESET   2
#define TIMER_DISPLAY 3

#endif // CALC_PROCESS_TIME_H
#endif // CALC_PROCESS_TIME
