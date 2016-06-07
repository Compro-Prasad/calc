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
  long double num;
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
{/* [FIFO stack] */
  /* Just one word about this list. It is a list stored as a stack in reverse
   * order. Considering the usual nature of accessing answers is first answer
   * is first and not last. Similarly second answer is second and not second
   * from the last. And deleting an answer is same on an average for stack and
   * reverse stack. Because you always have to traverse to the answer to delete
   * it. So, considering that stack has just one advantage over the reverse one
   * i.e. having a single pointer to the list but seeing user experience it
   * will be awkward for an average user that the most recent answer is the
   * first one
   */
  ans *top;                          // stores first address of answer in list
  ans *end;                          // stores last address of answer in list 
  unsigned long n;                   // stores the count of answers in the list
public:
  link_ans();
  unsigned long has_ans();                 // are there answers in the list?
  void add_ans(double);              // adds an answer to the list
  ans get_ans_x(unsigned long pos);  // returns an answer which is at position x
  void show_ans_x(unsigned long pos);// prints answer on the screen present at position x
  void del_ans_x(unsigned long pos); // deletes answer from position x
  void show_all_ans();               // prints all answers on the screen
  bool deallocate();                 // frees up the memory by emptying the list
  ~link_ans();
};

#ifdef ANS_CMD
extern bool store;              /* Whether or not to store answers */
extern link_ans l;                     /* Object for storing answers in stack */
#endif // ANS_CMD

#endif // ANS_H
#endif // ANS_CMD
