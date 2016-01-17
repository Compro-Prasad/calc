#include "calc_file.h"
#ifdef FILE_MANAGER
bool open_file(const char *b)
{
  ifstream f;
  long double CharCount = 0;
  f.open(b, ios::binary);
  if (f)
    {
      char c;
      long i = 1;
      fprintf(PRINTFAST, "\n");
      if (line_no == YES)
	fprintf(PRINTFAST, "%ld:", i);
      while (f.read((char *)&c, 1))
	{
	  if (line_no == YES)
	    CharCount++;
	  fprintf(PRINTFAST, "%c", c);
	  if (c == '\n')
	    if (line_no == YES)
	      fprintf(PRINTFAST, "%ld:", ++i);
	}
      if (line_no == YES)
	fprintf(PRINTFAST, "\n\nCharacter count : %.0Lf", CharCount);
      f.close();
      return 1;
    }
  f.close();
  return 0;
}

void edit_file(char b[MAX_LEN])
{
  char ch = NUL;
  fprintf(PRINTFAST, "\n1. Edit with internal editor");
  fprintf(PRINTFAST, "\n2. Edit with other editor");
  fprintf(PRINTFAST, "\n3. Exit");
  fprintf(PRINTFAST, "\nEnter choice: ");
  while (ch != 1 && ch != 2 && ch != 3)
    ch = getch() - 48;
  fprintf(PRINTFAST, "%c", ch + 48);
  if (ch == 1)
    {
      ofstream f;
      f.open(b, ios::binary | ios::app);
      if (f)
	{
	  char a[1000];
	  fprintf(PRINTFAST, "\nTo finish editing type \"/*\\\"\n");
	  while (!f.eof())
	    {
	      cin.getline(a, 1000);
	      int i = 0;
	      if (strcmp(a, "/*\\"))
		{
		  strcat(a, "\n\n");
		  for (; a[i] != '\n'; i++);
		  f.write((char *)&a, i + 1);
		}
	      else
		break;
	    }
	}
      else
	fprintf(PRINTFAST, "!!An error occured while opening the file!!");
      f.close();
    }
  else if (ch == 2)
    {
      fprintf(PRINTFAST, "\nEnter editor's name: ");
      char c[MAX_LEN];
      scanf("%s", c);
      c[strlen(c) + 1] = NUL, c[strlen(c)] = ' ';
      strcat(c, b);
      system(c);
    }
}

void remove_dot(char *a)
{
  for (unsigned long i = 0; a[i]; i++)
    {
      if (a[i] == '.' && a[i + 1] == '.' && a[i + 2] == '/')
	{
	  unsigned long k = i - 2;
	  while (a[k] != '/')
	    k--;
	  for (unsigned long j = k + 1; j < strlen(a); j++)
	    a[j] = a[j + i - k + strlen("../") - 1];
	  i = k;
	}
      if (a[i] == '.' && a[i + 1] == '/')
	{
	  for (unsigned long j = i; j < strlen(a); j++)
	    a[j] = a[j + 2];
	  i--;
	}
    }
}
#endif // FILE_MANAGER
