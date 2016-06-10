#include <signal.h>
#include <time.h>
#include <unistd.h>

#include <calc_process_time.hpp>

#ifdef CALC_PROCESS_TIME

bool calc_time = false;
bool calc_avg_time = false;
pid_t my_pid = getpid();

void calc_process_time(int sig)
{
  static clock_t start = 0;
  static long double time_taken = 0, expressions = 0, total_time = 0;

  if (sig == SIGUSR1)
    {
      if (start)
	{
	  time_taken = ((long double)(clock() - start)) / CLOCKS_PER_SEC;
	  start = 0;

	  if (calc_time == true)
	    fprintf(PRINTFAST, "Command Processing Time : %.8Lf seconds\n", time_taken);

	  if (calc_time == true && calc_avg_time == true)
	    expressions++, total_time += time_taken;
	}
      else
	start = clock();
    }
  else if (sig == SIGUSR2)
    {
      if (total_time)
	fprintf(PRINTFAST, "Average time = %.8Lf", (total_time / expressions));
      total_time = expressions = 0.0;
    }
}

#endif
