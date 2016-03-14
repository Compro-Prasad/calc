#include <calc_features.hpp>
#include <calc_cmd_action.hpp>
#include <conio.h>

history h;                      /* Object for inserting commands in stack for further retrieval */
strings Error;                  /* String for storing errors generated after each command */
link_oprators optr;             /* Object for storing operators in the stack for calculation */
link_numbers num;               /* Object for storing numbers in the stack for calculation */

#ifdef CALC_COLORS
calc_font input_font  = calc_font( CYAN  , DEFAULT, REGULAR );
calc_font error_font  = calc_font( RED   , DEFAULT, BOLD    );
calc_font output_font = calc_font( GREEN , DEFAULT, REGULAR );
calc_font prompt_font = calc_font( YELLOW, DEFAULT, REGULAR );
#endif // CALC_COLORS

unsigned short record = NORMAL_COMMANDS | EXPRESSION_COMMANDS | UNDEFINED_COMMANDS | EXPRESSIONS_HAVING_ERROR; /* Switch for (not)storing specific types commands */

#ifdef ANS_CMD
bool store = true;              /* Whether or not to store answers */
link_ans l;                     /* Object for storing answers in stack */
#endif // ANS_CMD

#ifdef CONST_CMDS
const_list cons;                /* Object for storing constants in stack */
#endif // CONST_CMDS

#ifdef STEPS_CMD
bool steps = false;             /* Whether or not to show steps */
#endif // STEPS_CMD

#ifdef FILE_MANAGER
bool line_no = false;           /* Whether or not to show line numbers */
bool printpwd = false;          /* Whether or not to show pwd */
char pwd[MAX_LEN] = HOME;       /* String for storing pwd */
#endif // FILE_MANAGER

#ifdef CALC_PROCESS_TIME
bool calc_time = false;         /* Whether or not to show processing time for each calculation */
bool calc_avg_time = false;     /* Whether or not to show average processing time for a set of sequential calculations */
#endif // CALC_PROCESS_TIME

#ifdef OPTR_DETAILS
bool oprator_detail = false;    /* Whether or not to show status of operators stack */
#endif // OPTR_DETAILS

#ifdef NUM_DETAILS
bool num_detail = false;        /* Whether or not to show status of numbers stack */
#endif // NUM_DETAILS

#ifdef PROMPT
char prompt[500] = ">> ";       /* String for storing prompt */
#endif // PROMPT

unsigned char angle_type = DEG;/* Type of angle to be taken input and shown output */
char precision[15] = "%.5Lg";  /* String for storing precision */
char e[3] = "Lg";              /* String for showing or not showing exponential */

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

int main(int argc, char *argv[])
{
#ifdef CALC_COLORS
    output_font.print();
#endif
    bool space_flag = 1;
    strings a;

#ifdef SHELL_INPUT
    for (int index = 1; index < argc; index++)
    {
        a = argv[index];
        Error = "";
        /* option for reading commands from file */
        if (a == "-f")
        {
            if (index < (argc - 1))
            {
                a = argv[++index];
                ifstream f;
                f.open(a.str());
                if (f)
                {
                    while (!f.eof())
                    {
                        f.getline(a.str(), 4000, '\n');
                        print_prompt();
                        fprintf(PRINTFAST, "%s ", a.str());
                        cmd_action(a.str());
                    }
                }
                else
                    sprintf(Error.str(), "\"%s\" file could not be read\n", a.str());
            }
            else
                sprintf(Error.str(), "(null) file can't be opened\n");
        }
        else
        {
            print_prompt();
            cmd_action(a.str());
        }
    }

    if (argc != 1)
        return 0;

#endif // SHELL_INPUT

#ifdef DIRECT_INPUT
    fprintf(PRINTFAST, "\
This is free software with ABSOLUTELY NO WARRANTY.\n\
For details type `warranty'.\n\
Type help and press return to know more.\n");

    /* till the user doesnt type exit the loop will go on */
    while (a != "exit")
    {
        a = "";

        print_prompt();

        char ch = 0, tempch = 0;
        long shift = 1;
        Error = "";

#ifdef CALC_HISTORY
        h.reset();
#endif

#ifdef CALC_COLORS
        input_font.print();
#endif
        /* loop for input */
        for (long i = 0;;)
        {
            if (!(i % 5) && tempch)
                fflush(stdin);
            /* single character as input */
            ch = getch();
#ifdef CALC_HISTORY
            if (!i)
                h.cmd_modify(a);
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
                    while (shift)
                        fprintf(PRINTFAST, "%c", a[i++]), shift--;
                    if (a[i - 1] == ' ')
                        a.write(0, i - 1);
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

                else if (i < strMAX - 5 && space_flag)	/* for other characters */
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
#ifdef CALC_COLORS
        output_font.print();
#endif
        /* loop for input ends */

        reduce_space(a.str());
        h.cmd_modify(a);

#if defined(CONST_CMDS) && defined(ANS_CMD)
        if (a == "exit")
            fprintf(PRINTFAST, "\nExiting...");
        else
#endif
            cmd_action(a);
        if (Error != "")
        {
#ifdef CALC_COLORS
            error_font.print();
#endif
            fprintf(PRINTFAST, "%s\n", Error.str());
#ifdef CALC_COLORS
            output_font.print();
#endif
        }
    }
    /******************************************************/
#ifdef CONST_CMDS
    fprintf(PRINTFAST, "\nDeallocating Constants...");
    cons.delete_all_const();
    fprintf(PRINTFAST, "[Deleted all Constants]");
#endif
#ifdef ANS_CMD
    fprintf(PRINTFAST, "\nDeallocating Answers...");
    l.deallocate();
    fprintf(PRINTFAST, "[Deleted all Answers]");
#endif
#if defined(CONST_CMDS) && defined(ANS_CMD)
    fprintf(PRINTFAST, "\nCalculator exited successfully\n");
#endif
#endif
#if !defined(SHELL_INPUT) && !defined(DIRECT_INPUT)
    fprintf(PRINTFAST, "No input was enabled at the time of installation\n");
    fprintf(PRINTFAST, "Reinstall with either of the following inputs enabled:\n");
    fprintf(PRINTFAST, "1) Shell Input\n");
    fprintf(PRINTFAST, "2) Direct Input\n");
#endif
    return 0;
}
