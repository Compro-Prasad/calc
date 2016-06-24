#include <signal.h>
#include <time.h>
#include <unistd.h>

#include <calc_process_time.hpp>

#ifdef CALC_PROCESS_TIME

bool calc_time = false;
bool calc_avg_time = false;

void calc_process_time(char sig)
{
  static clock_t start = 0;
  static long double expressions, total_time;

  if (sig == TIMER_START)
    start = clock();
  else if (sig == TIMER_STOP && start)
    {
      long double time_taken =
	((long double)(clock() - start)) / CLOCKS_PER_SEC;
      start = 0;

      if (calc_avg_time == true)
	expressions++, total_time += time_taken;

      if (calc_time == true)
	fprintf(PRINTFAST, "\nCommand Processing Time : %.8Lf seconds",
		time_taken);
    }
  else if (sig == TIMER_RESET)
    total_time = expressions = 0.0;
  else if (sig == TIMER_DISPLAY && expressions)
    fprintf(PRINTFAST, "\nAverage time = %.8Lf", (total_time / expressions));
}

#endif
