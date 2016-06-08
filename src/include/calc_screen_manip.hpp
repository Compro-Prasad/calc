#include <calc_features.hpp>

#ifdef SCREEN_MANIP

#ifndef CALC_SCREEN_MANIP_H
#define CALC_SCREEN_MANIP_H

#include <calc_term_csi.hpp>

#define moveup       fprintf(stderr, CSICUA)
#define movedown     fprintf(stderr, CSICUB)
#define movefd       fprintf(stderr, CSICUC)
#define movebd       fprintf(stderr, CSICUD)
#define movexy(x, y) fprintf(stderr, FCSICUP, y, x)
#define moveyx(y, x) fprintf(stderr, FCSICUP, y, x)
#define move(x, y)   movexy(x, y)

#define clear_full     fprintf(stderr, FCSIED, FULL)
#define clear_afterCU  fprintf(stderr, FCSIED, AFTER)
#define clear_beforeCU fprintf(stderr, FCSIED, BEFORE)
#define clear          fprintf(stderr, FCSIED CSICUP, FULL)

#define clear_full_line     fprintf(stderr, FCSIEL, FULL)
#define clear_afterCU_line  fprintf(stderr, FCSIEL, AFTER)
#define clear_beforeCU_line fprintf(stderr, FCSIEL, BEFORE)

#define CUsave    fprintf(stderr, CSISCP)
#define CUrestore fprintf(stderr, CSIRCP)

#define scroll_up   fprintf(stderr, CSISU)
#define scroll_down fprintf(stderr, CSISD)

#define DEC_CUR_POS (!(cur_col >> 1) && cur_line > 1 ? --cur_line : 0,	\
		     cur_col = cur_col >> 1 ? cur_col - 1 : max_cols)
#define INC_CUR_POS (cur_col = cur_col == max_cols ? 1 : cur_col + 1,	\
		     !(cur_col >> 1) && cur_line < max_lines ? ++cur_line : 0)


extern void current_pos(unsigned short &x, unsigned short &y);
extern void clrscr();
extern void get_screen_size(int);
extern void change_screen_values(int);

extern unsigned short max_lines, max_cols;
extern unsigned short cur_line, cur_col;

#endif

#endif
