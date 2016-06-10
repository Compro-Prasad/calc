#include <calc_features.hpp>

#ifdef CALC_PROCESS_TIME

#ifndef CALC_PROCESS_TIME_H
#define CALC_PROCESS_TIME_H

extern void calc_process_time(int sig);

extern bool calc_time;         /* Whether or not to show processing time for each calculation */
extern bool calc_avg_time;     /* Whether or not to show average processing time for a set of sequential calculations */
extern pid_t my_pid;

#endif // CALC_PROCESS_TIME_H
#endif // CALC_PROCESS_TIME
