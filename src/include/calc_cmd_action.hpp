#include <calc_strings.hpp>

extern void cmd_action();

#ifdef CALC_PROCESS_TIME
extern bool calc_time;         /* Whether or not to show processing time for each calculation */
extern bool calc_avg_time;     /* Whether or not to show average processing time for a set of sequential calculations */
#endif // CALC_PROCESS_TIME
