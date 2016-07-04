#include <calc_features.hpp>

#ifdef SCREEN_MANIP

#ifndef CALC_SCREEN_MANIP_H
#define CALC_SCREEN_MANIP_H

#include <calc_term_csi.hpp>

#define moveup       fprintf(PRINTFAST, CSICUA)
#define movedown     fprintf(PRINTFAST, CSICUB)
#define movefd       fprintf(PRINTFAST, CSICUC)
#define movebd       fprintf(PRINTFAST, CSICUD)
#define movexy(x, y) fprintf(PRINTFAST, FCSICUP, y, x)
#define moveyx(y, x) fprintf(PRINTFAST, FCSICUP, y, x)
#define move(x, y)   movexy(x, y)

#define clear_full     fprintf(PRINTFAST, FCSIED, FULL)
#define clear_afterCU  fprintf(PRINTFAST, FCSIED, AFTER)
#define clear_beforeCU fprintf(PRINTFAST, FCSIED, BEFORE)
#define clear          fprintf(PRINTFAST, FCSIED CSICUP, FULL)

#define clear_full_line     fprintf(PRINTFAST, FCSIEL, FULL)
#define clear_afterCU_line  fprintf(PRINTFAST, FCSIEL, AFTER)
#define clear_beforeCU_line fprintf(PRINTFAST, FCSIEL, BEFORE)

#define CUsave    fprintf(PRINTFAST, CSISCP)
#define CUrestore fprintf(PRINTFAST, CSIRCP)

#define scroll_up   fprintf(PRINTFAST, CSISU)
#define scroll_down fprintf(PRINTFAST, CSISD)

extern void clrscr();

#endif

#endif
