#include <calc_features.hpp>

#ifdef FILE_MANAGER
#include <chatr.hpp>
#include <fstream>
#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

extern int getch();

extern bool line_no;

bool open_file(const char *b);

void edit_file(char b[MAX_LEN]);

void remove_dot(char *a);
#endif // FILE_MANAGER
