#include <calc_features.hpp>

#if defined(FILE_MANAGER) || defined(SHELL_INPUT)
#include <fstream>
using namespace std;
#endif

#ifdef FILE_MANAGER
#include <chatr.hpp>
#include <iostream>
#include <string.h>
#include <stdlib.h>

extern int getch();

extern bool line_no;

bool open_file(const char *b);

void edit_file(char b[MAX_LEN]);

void remove_dot(char *a);
#endif // FILE_MANAGER
