#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>

#include <calc_features.hpp>
#include <calc_input.hpp>
#include <calc_colors.hpp>
#include <calc_stacks/history_stack.hpp>

extern bool printpwd;
extern calc_font input_font, prompt_font, output_font;
extern char pwd[MAX_LEN];
extern char prompt[500];

/* Copied from source code of conio.h
 * in C4droid
 */
void terminal_lnbuf(int yn)
{
    struct termios oldt, newt;
    tcgetattr(0, &oldt);
    newt = oldt;
    if (!yn) newt.c_lflag &= ~ICANON;
    else newt.c_lflag |= ICANON;
    tcsetattr(0, TCSANOW, &newt);
}

void terminal_echo(int yn)
{
    struct termios oldt, newt;
    tcgetattr(0, &oldt);
    newt = oldt;
    if (!yn) newt.c_lflag &= ~ECHO;
    else newt.c_lflag |= ECHO;
    tcsetattr(0, TCSANOW, &newt);
}

int getch()
{
    register int ch;
    terminal_lnbuf(0);
    terminal_echo(0);
    ch = getchar();
    terminal_lnbuf(1);
    terminal_echo(1);
    return ch;
}
/* ******************** */
void print_prompt()
{
#ifdef PROMPT
#ifdef FILE_MANAGER
    if (printpwd == YES)
#ifdef CALC_COLORS
    {
        prompt_font.print();
#endif
        fprintf(PRINTFAST, "%s", pwd);
#ifdef CALC_COLORS
        output_font.print();
    }
#endif
#endif // FILE_MANAGER
    /* show prompt */
#ifdef CALC_COLORS
    prompt_font.print();
#endif
    fprintf(PRINTFAST, "%s", prompt);
#ifdef CALC_COLORS
    output_font.print();
#endif
    /***************/
#endif // PROMPT
}
void calc_input(strings &a)
{
    bool space_flag = 1;
    char ch = 0, tempch = 0;
    long shift = 1;
    for (long i = 0;;)
    {
        if (!(i % 5) && tempch)
            fflush(stdin);
        /* single character as input */
        ch = getch();
#ifdef CALC_HISTORY
        if (!i)  h.cmd_modify(a);
#endif
        /* processing of character according to condition */
        if (ch == ESC)
        {
            tempch = ch;
            continue;
        }
        if (tempch == ESC && ch == '[')
        {
            ch = getch();
            /* When Right Arrow Key is pressed */
            if (ch == 'C')
            {
                if (shift > 1)
                {
                    shift--, tempch = 0;
                    fprintf(PRINTFAST, "%c", a[i++]);
                }
                continue;
            }

            /* When Left Arrow Key is pressed */
            if (ch == 'D')
            {
                if (shift <= a.len())
                {
                    i--, shift++, tempch = 0;
                    fprintf(PRINTFAST, "\b");
                }
                continue;
            }

#ifdef CALC_HISTORY
            /* When Up/Down Arrow Key is pressed */
            if (ch == 'A' || ch == 'B')
            {
                command *temp = ch == 'A' ? h.get_prev_cmd() : h.get_next_cmd();
                if (temp && temp->c != a)
                {
                    shift = 1;
                    i = temp->c.len();
                    long l = a.len();
                    a = temp->c;
                    fprintf(PRINTFAST, "\r");
                    print_prompt();
#ifdef CALC_COLORS
                    input_font.print();
#endif
                    fprintf(PRINTFAST, "%s", a.str());
                    for (long j = l - i; j > 0; j--)
                        fprintf(PRINTFAST, " ");
                    for (l = l - i; l > 0; l--)
                        fprintf(PRINTFAST, "\b");
                }
                continue;
            }
#endif // CALC_HISTORY

            /* If Home Key is pressed */
            if (ch == 'H')
            {
                if (shift <= a.len())
                {
                    i = 0, shift = a.len() + 1, tempch = 0;
                    fprintf(PRINTFAST, "\r");
                    print_prompt();
#ifdef CALC_COLORS
                    input_font.print();
#endif
                }
                continue;
            }

            /* If End Key is pressed */
            if (ch == 'F')
            {
                if (shift > 1)
                {
                    shift = 1, i = a.len(), tempch = 0;
                    fprintf(PRINTFAST, "\r");
                    print_prompt();
#ifdef CALC_COLORS
                    input_font.print();
#endif
                    fprintf(PRINTFAST, "%s", a.str());
                }
                continue;
            }

            tempch = 0;
            fflush(stdin);
        }
        if ((ch >= ' ' && ch <= DEL) || ch == LF)
        {
            /* if a line feed(LF) is the input */
            if (ch != ' ' || (i && a[i - 1] != ' '))
                space_flag = 1;
            else
                space_flag = 0;

            if (ch == LF)
            {
                if (!a[0])
                    continue;
                while (shift)
                    fprintf(PRINTFAST, "%c", a[i++]), shift--;
                if (a[i - 2] == ' ')
                {
                    a.write(0, i - 2);
                    fprintf(PRINTFAST, "\b");
                }
                break /* the loop */ ;
            }
            /* if a backspace is the input */
            if (ch == DEL)
            {
                /* if i is zero then there is nothing to delete */
                /* so */ if (i > 0)
                {
                    a.del(--i);
#ifdef CALC_HISTORY
                    h.cmd_modify(a);
#endif
                    /* remove a character from output screen */
                    fprintf(PRINTFAST, "\b");
                    for (long z = a.len() - shift + 1; z < a.len(); z++)
                        fprintf(PRINTFAST, "%c", a[z]);
                    fprintf(PRINTFAST, " ");
                    for (long z = a.len() - shift; z < a.len(); z++)
                        fprintf(PRINTFAST, "\b");
                }
            }

            else if (i < strMAX - 2 && space_flag)	/* for other characters */
            {
                fprintf(PRINTFAST, "%c", ch);
                a.shift_right(a.len() - shift);
                a.write(ch, i++);
#ifdef CALC_HISTORY
                h.cmd_modify(a);
#endif
                for (long z = a.len() - shift + 1; z < a.len(); z++)
                    fprintf(PRINTFAST, "%c", a[z]);
                for (long z = a.len() - shift + 1; z < a.len(); z++)
                    fprintf(PRINTFAST, "\b");
            }
        }
    }
}
