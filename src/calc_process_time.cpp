#include <signal.h>
#include <time.h>
#include <unistd.h>

#include <calc_process_time.hpp>

#ifdef CALC_PROCESS_TIME

bool calc_time = false;
bool calc_avg_time = false;
pid_t my_pid = getpid();

void calc_process_time(char sig)
{
  static clock_t start = 0;
  static long double expressions = 0, total_time = 0;

  if (sig == TIMER_DO_NORMAL)
    {
      if (start)
	{
	  long double time_taken =
	    ((long double)(clock() - start)) / CLOCKS_PER_SEC;
	  start = 0;

	  if (calc_time == true)
	    {
	      fprintf(PRINTFAST, "\nCommand Processing Time : %.8Lf seconds",
		      time_taken);
	      if (calc_avg_time == true)
		expressions++, total_time += time_taken;
	    }
	}
      else
	start = clock();
    }
  else if (sig == TIMER_RESET)
    total_time = expressions = 0.0;
  else if (sig == TIMER_DISPLAY && total_time)
    fprintf(PRINTFAST, "\nAverage time = %.8Lf", (total_time / expressions));
}

#endif
