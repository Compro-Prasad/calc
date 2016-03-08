#include <calc_features.hpp>

#ifdef ANS_CMD
#ifndef ANS_STACK_H
#define ANS_STACK_H

#include <calc_strings.hpp>
#include <calc_colors.hpp>

/* constant strings used repeatedly in the program */
#define Not_Calc "!!Ans%ld not yet calculated and is 0!!"
#undef Empty
#define Empty "!!Answers list empty!!"
#define Invalid "!!Position invalid!!"

extern bool store;
extern char precision[15];
extern calc_font error_font;
extern calc_font output_font;

/* structure for storing answers */
struct answer
{
  long double n;
  void display();
};

/* structure for helping in linking answers which is inherited publicly from
   answer */
struct ans:public answer
{
  ans *next;
  ans();
};

class link_ans
{
  ans *top, *free_list;                              // stores the starting address of answers list
  unsigned long n;                       // stores the number of answers in the list
 public:
  link_ans();
  void add_ans(double);                  // adds an answer to the list
  ans get_ans_x(unsigned long x);        // returns an answer which is at position x
  void show_ans_x(unsigned long x);      // prints answer on the screen present at position x
  void del_ans_x(unsigned long x);       // deletes answer from position x
  void show_all_ans();                   // prints all answers on the screen
  bool deallocate();                     // frees up the memory by emptying the list
  ~link_ans();
};
#endif // ANS_H
#endif // ANS_CMD
