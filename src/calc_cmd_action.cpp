#include <calc_cmd_action.hpp>

void cmd_action(strings a)
{
#ifdef CALC_PROCESS_TIME
    clock_t start;
    static long double time_taken, expressions, total_time;
    start = clock();
#endif
    strings temp_char;
#ifdef ANS_CMD
    ans k;
#endif
    unsigned long d;
    unsigned long i;
    /* commands for dealing with exponentials */
    if (a == "show e")
    {
        extract(a.str(), temp_char.str(), strlen("show "));
        strcpy(precision, "%.5Lg");
        strcpy(e, "Lg");
    }
    else if (a == "hide e")
    {
        strcpy(precision, "%.5Lf");
        strcpy(e, "Lf");
    }
    /******************************************/
    else if (a == "warranty")
    {
        fprintf(PRINTFAST, "\n\n\t\
This program is free software; you can redistribute it and/or modify\n\t\
it under the terms of the GNU General Public License as published by\n\t\
the Free Software Foundation; either version 2 of the License , or\n\t\
(at your option) any later version.\n\
\n\t\
This program is distributed in the hope that it will be useful,\n\t\
but WITHOUT ANY WARRANTY; without even the implied warranty of\n\t\
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\t\
GNU General Public License for more details.\n\
\n\t\
You should have received a copy of the GNU General Public License\n\t\
along with this program. If not, write to\n\
\n\t\t\
The Free Software Foundation, Inc.\n\t\t\
51 Franklin Street, Fifth Floor\n\t\t\
Boston, MA 02110-1301  USA\n");
    }
#ifdef CLEAR_CMD
    else if (a == "clear")
        clrscr();
#endif
#ifdef HELP_CMD
    else if (!strncasecmp(a.str(), "help ", 5) || a == "help")
    {
        extract(a.str(), temp_char.str(), 5, -1, NUL, 30);
        help(temp_char);
    }
#endif
#ifdef FILE_MANAGER

#endif
#ifdef CALC_PROCESS_TIME
    else if (a == "show processing time")
        calc_time = YES;
    else if (a == "hide processing time")
        calc_time = NO;
    else if (a == "start recording")
        calc_avg_time = YES, total_time = expressions = 0.0;
    else if (a == "stop recording")
    {
        calc_avg_time = NO;
        fprintf(PRINTFAST, "\nAverage time = %.8Lf", (total_time / expressions));
    }
#endif
#ifdef OPTR_DETAILS
    else if (a == "show operator details")
        oprator_detail = YES;
    else if (a == "hide operator details")
        oprator_detail = NO;
#endif
#ifdef NUM_DETAILS
    else if (a == "show number details")
        num_detail = YES;
    else if (a == "hide number details")
        num_detail = NO;
#endif
#ifdef STEPS_CMD
    /* commands to show/hide steps */
    else if (a == "show steps")
        steps = YES;
    else if (a == "hide steps")
        steps = NO;
    /*******************************/
#endif
#ifdef ANS_CMD
    /* commands to manipulate storing of answers */
    else if (a == "start storing answers")
        store = YES;
    else if (a == "stop storing answers")
        store = NO;
    /*********************************************/
#endif
#ifdef CHANGE_ANGLE
    /* commands for changing angle type */
    else if (a == "deg")
        angle_type = DEG;
    else if (a == "rad")
        angle_type = RAD;
    else if (a == "grad")
        angle_type = GRAD;
    /************************************/
#endif // CHANGE_ANGLE
#ifdef CALC_HISTORY
    else if (!strncasecmp(a.str(), "allow ", 6))
    {
        extract(a.str(), temp_char.str(), 6, -1, NUL, 30);
        if (temp_char == "UNDEFINED COMMANDS")
            record |= UNDEFINED_COMMANDS;
        else if (temp_char == "NORMAL COMMANDS")
            record |= NORMAL_COMMANDS;
        else if (temp_char == "EXPRESSION COMMANDS")
            record |= EXPRESSION_COMMANDS;
        else if (temp_char == "EXPRESSIONS HAVING ERROR")
            record |= EXPRESSIONS_HAVING_ERROR;
    }
    else if (!strncasecmp(a.str(), "restrict ", 9))
    {
        extract(a.str(), temp_char.str(), 9, -1, NUL, 30);
        if (temp_char == "UNDEFINED COMMANDS")
            record &= ~UNDEFINED_COMMANDS;
        else if (temp_char == "NORMAL COMMANDS")
            record &= ~NORMAL_COMMANDS;
        else if (temp_char == "EXPRESSION COMMANDS")
            record &= ~EXPRESSION_COMMANDS;
        else if (temp_char == "EXPRESSIONS HAVING ERROR")
            record &= ~EXPRESSIONS_HAVING_ERROR;
    }
#endif
#ifdef CONST_CMDS
    /* commands for dealing with constants */
    else if (a == "load constant pi")
    {
#ifdef PI
        constant x = constant("pi", PI);
        cons.insert_const(x);
#else
        Error = "!!PI was not declared in program!!";
#endif // PI
    }
    else if (!strncasecmp(a.str(), "constant ", 9))
    {
        constant con;
        extract(a.str(), con.name, 9, -1, '=');
        if (ismath(con.name) != SUCCESS)
        {
            i = 0;
            while (a[i] != '=')
                i++;
            i++, con.value = 0;
            if (separate_ans(a.str(), i, d) == SUCCESS)
                con.value = l.get_ans_x(d).n;
            else if (atof(a.str(), i, con.value) != SUCCESS)
                Error = "!!RHS value is incorrect!!\n";
            if (!cons.insert_const(con))
                Error =
                    "!!Syntax error!!\nSyntax is \"constant <constant name>=<constant value>\"";
        }
        else
            sprintf(Error.str(), "!!%s already defined as a mathematical function!!", con.name);
    }
    else if (a == "show constants")
        cons.disp_const();
    else if (!strncasecmp(a.str(), "remove constant ", 16))
    {
        char name[15];
        extract(a.str(), name, strlen("remove constant "), 16 + 15);
        cons.delete_const(name);
    }
    else if (a == "remove constants")
    {
        fprintf(PRINTFAST, "\nDelete all constants?(Y for yes)");
        if (getch() == 'y')
            cons.delete_all_const();
    }
    /***************************************/
#endif // CONST_CMDS
#ifdef ANS_CMD
    /* commands for dealing with answers */
    else if (a == "show answers")
        l.show_all_ans();
    else if (!strncasecmp(a.str(), "show a", 6))
    {
        d = 0, i = 5;
        if (separate_ans(a.str(), i, d) == SUCCESS)
            l.show_ans_x(d);
        else
            Error = "!!Syntax Error!!\nSyntax is : show a<positive integer>";
    }
    else if (a == "delete answers")
    {
        if (!l.deallocate())
            fprintf(PRINTFAST, "!!Answers list empty!!");
    }
    else if (!strncasecmp(a.str(), "delete a", 8))
    {
        d = 0, i = 7;
        if (separate_ans(a.str(), i, d) == SUCCESS)
            l.del_ans_x(d);
        else
            Error = "!!Syntax Error!!\nSyntax is : show a<positive integer>";
    }
    /*************************************/
#endif // ANS_CMD
#ifdef CALC_HISTORY
    else if (a == "show history")
        h.display();
#endif
#ifdef SHELL_CMD
    /* commands to deal with shell */
    else if (!strncasecmp(a.str(), "shell ", 6))
    {
        extract(a.str(), temp_char.str(), 6);
        fprintf(PRINTFAST, "\nConnecting to shell...\n");
        system(temp_char.str());
    }
    else if (a == "shell")
    {
        char t[MAX_LEN] = "cd ";
#ifdef FILE_MANAGER
        strcat(t, pwd);
#endif // FILE_MANAGER
        strcat(t, " && bash");
        fprintf(PRINTFAST, "\nConnecting to shell...\n");
        if (system(t))
            Error = "!!Unable to connect to shell!!";
        else
            fprintf(PRINTFAST, "Shell disconnected...");
    }
    /*******************************/
#endif // SHELL_CMD
#ifdef PROMPT
    else if (!strncasecmp(a.str(), "prompt=", 7))
    {
        extract(a.str(), temp_char.str(), 7, -1, NUL, 500);
        strncpy(prompt, temp_char.str(), 500);
    }
#endif // PROMPT
#ifdef FILE_MANAGER
    else if (a == "show pwd" || a == "show path")
        printpwd = YES;
    else if (a == "hide pwd" || a == "hide path")
        printpwd = NO;
    /* commands to show/hide line numbers */
    else if (a == "show line numbers")
        line_no = YES;
    else if (a == "hide line numbers")
        line_no = NO;
    /**************************************/
    else if (!strncasecmp(a.str(), "edit ", 5))
    {
        strings t;
        t = pwd;
        extract(a.str(), temp_char.str(), 5);
        t += temp_char;
        edit_file(t.str());
    }
    else if (!strncasecmp(a.str(), "open ", 5))
    {
        extract(a.str(), temp_char.str(), 5);
        strings t;
        t = pwd;
        t += temp_char;
        if (open_file(t.str()) == FAILURE)
            edit_file(t.str());
    }
    else if (!strncmp(a.str(), "ls ", 3) || !strcmp(a.str(), "ls"))
    {
        if (a[3] == NUL)
        {
            a += " ";
            a += pwd;
        }
        else if (a[3] != '/')
        {
            strings t;
            extract(a.str(), temp_char.str(), 3, -1, '\0');
            t = pwd;
            t += temp_char;
            a.write(NUL, 3);
            a += t;
        }
        fprintf(PRINTFAST, "\n");
        system(a.str());
    }
    else if (!strncasecmp(a.str(), "cd ", 3))
    {
        extract(a.str(), temp_char.str(), 3);
        if (temp_char[0] != '/')
        {
            strings t = pwd;
            t += temp_char;
            temp_char = t;
        }
        strings t = "cd ";
        t += temp_char;
        if (!system(t.str()))
        {
            extract(t.str(), pwd, 3);
            if (pwd[strlen(pwd) - 1] != '/')
                strncat(pwd, "/", MAX_LEN);
        }
        else
            Error = "\nSystem Error : Directory not accessable";
        remove_dot(pwd);
    }
    else if (a == "pwd")
        fprintf(PRINTFAST, "\n%s", pwd);
    else if (!strncasecmp(a.str(), "rm ", 3))
    {
        extract(a.str(), temp_char.str(), 3);
        if (temp_char[0] != '/')
        {
            strings t;
            t = pwd;
            t += temp_char;
            temp_char = t;
        }
        if (remove(temp_char.str()) == ERROR)
            Error = "!!File does not exist!!";
    }
#endif // FILE_MANAGER


#ifdef CHANGE_PRECISION
    else if (!strncasecmp(a.str(), "precision=", 10) || !strncasecmp(a.str(), "precision ", 10))
    {
        long double x = 0;
        signed char check_calculate;
        check_calculate = calculate(a.str(), x, 10);
        if (check_calculate == SUCCESS)
        {
            unsigned short n = x;
            n %= 1000;
            sprintf(precision, "%%.%d%s", n, e);
#ifdef CALC_HISTORY
            if (!(record & EXPRESSION_COMMANDS))
                h.pop();
#endif
        }
        else if (check_calculate == ERROR)
#ifdef CALC_HISTORY
        {
#endif
            Error += " Error!!";
#ifdef CALC_HISTORY
            if (!(record & EXPRESSIONS_HAVING_ERROR))
                h.pop();
        }
#endif
        else if (check_calculate == FAILURE)
#ifdef CALC_HISTORY
        {
#endif
            Error = "!!Invalid Expression!!";
#ifdef CALC_HISTORY
            if (!(record & EXPRESSIONS_HAVING_ERROR))
                h.pop();
        }
#endif
    }
#endif // CHANGE_PRECISION


    else if (a == "show settings")
    {
#ifdef PROMPT
        fprintf(PRINTFAST, "\n");
        fprintf(PRINTFAST, "Prompt             =  \"%s\"", prompt);
#endif // PROMPT
#ifdef ANS_CMD
        fprintf(PRINTFAST, "\n");
        fprintf(PRINTFAST, "Storing Answers    =  %s", store == YES ? "YES" : "NO");
#endif // ANS_CMD
#ifdef CHANGE_PRECISION
        fprintf(PRINTFAST, "\n");
        fprintf(PRINTFAST, "Precision          =  \"%s\"", precision);
#endif // CHANGE_PRECISION
        fprintf(PRINTFAST, "\n");
        fprintf(PRINTFAST, "Show Exponential   =  %s", strcasecmp(e, "Lf") ? "NO" : "YES");
#ifdef FILE_MANAGER
        fprintf(PRINTFAST, "\n");
        fprintf(PRINTFAST, "Present Directory  =  %s\n", pwd);
        fprintf(PRINTFAST, "Path Prompt        =  %s\n", printpwd == YES ? "YES" : "NO");
        fprintf(PRINTFAST, "Show Line Number   =  %s", line_no == YES ? "YES" : "NO");
#endif // FILE_MANAGER
        fprintf(PRINTFAST, "\n");
        fprintf(PRINTFAST, "Angle Mode         =  %s", angle_type == DEG ? "DEGREE" : angle_type == GRAD ? "GRAD" : "RADIAN");
#ifdef STEPS_CMD
        fprintf(PRINTFAST, "\n");
        fprintf(PRINTFAST, "Steps              =  %s", steps == YES ? "YES" : "NO");
#endif // STEPS_CMD
#ifdef OPTR_DETAILS
        fprintf(PRINTFAST, "\n");
        fprintf(PRINTFAST, "Operator details   =  %s", oprator_detail == YES ? "YES" : "NO");
#endif // OPTR_DETAILS
#ifdef NUM_DETAILS
        fprintf(PRINTFAST, "\n");
        fprintf(PRINTFAST, "Number details     =  %s", num_detail == YES ? "YES" : "NO");
#endif // NUM_DETAILS
    }

#ifdef CALC_COLORS
    else if (!strncasecmp(a.str(), "input font color ", 17))
    {
        extract(a.str(), temp_char.str(), 17);
        bool flag = true;
        for (int d = 0; d < NO_OF_COLORS; d++)
            if (temp_char == calc_font_colors[d])
            {
                input_font.color = d, flag = false;
                input_font.update();
                break;
            }
        if (flag)
            sprintf(Error.str(), "Error: Color mismatch");
    }
    else if (!strncasecmp(a.str(), "output font color ", 18))
    {
        extract(a.str(), temp_char.str(), strlen("output font color "));
        bool flag = true;
        for (int d = 0; d < NO_OF_COLORS; d++)
            if (temp_char == calc_font_colors[d])
            {
                output_font.color = d, flag = false;
                output_font.update();
                break;
            }
        if (flag)
            sprintf(Error.str(), "Error: Color mismatch");
    }
    else if (!strncasecmp(a.str(), "error font color ", 17))
    {
        extract(a.str(), temp_char.str(), 17);
        bool flag = true;
        for (int d = 0; d < NO_OF_COLORS; d++)
            if (temp_char == calc_font_colors[d])
            {
                error_font.color = d, flag = false;
                error_font.update();
                break;
            }
        if (flag)
            sprintf(Error.str(), "Error: Color mismatch");
    }
    else if (!strncasecmp(a.str(), "prompt font color ", 18))
    {
        extract(a.str(), temp_char.str(), 18);
        bool flag = true;
        for (int d = 0; d < NO_OF_COLORS; d++)
            if (temp_char == calc_font_colors[d])
            {
                prompt_font.color = d, flag = false;
                prompt_font.update();
                break;
            }
        if (flag)
            sprintf(Error.str(), "Error: Color mismatch");
    }
    else if (!strncasecmp(a.str(), "input font background ", 22))
    {
        extract(a.str(), temp_char.str(), 23);
        bool flag = true;
        for (int d = 0; d < NO_OF_COLORS; d++)
            if (temp_char == calc_font_colors[d])
            {
                input_font.bagnd = d, flag = false;
                input_font.update();
                break;
            }
        if (flag)
            sprintf(Error.str(), "Error: Color mismatch");
    }
    else if (!strncasecmp(a.str(), "output font background ", 23))
    {
        extract(a.str(), temp_char.str(), 23);
        bool flag = true;
        for (int d = 0; d < NO_OF_COLORS; d++)
            if (temp_char == calc_font_colors[d])
            {
                output_font.bagnd = d, flag = false;
                output_font.update();
                break;
            }
        if (flag)
            sprintf(Error.str(), "Error: Color mismatch");
    }
    else if (!strncasecmp(a.str(), "error font background ", 22))
    {
        extract(a.str(), temp_char.str(), 22);
        bool flag = true;
        for (int d = 0; d < NO_OF_COLORS; d++)
            if (temp_char == calc_font_colors[d])
            {
                error_font.bagnd = d, flag = false;
                error_font.update();
                break;
            }
        if (flag)
            sprintf(Error.str(), "Error: Color mismatch");
    }
    else if (!strncasecmp(a.str(), "prompt font background ", 23))
    {
        extract(a.str(), temp_char.str(), 23);
        bool flag = true;
        for (int d = 0; d < NO_OF_COLORS; d++)
            if (temp_char == calc_font_colors[d])
            {
                prompt_font.bagnd = d, flag = false;
                prompt_font.update();
                break;
            }
        if (flag)
            sprintf(Error.str(), "Error: Color mismatch");
    }
    else if (!strncasecmp(a.str(), "input font style ", 17))
    {
        extract(a.str(), temp_char.str(), 17);
        bool flag = true;
        for (int d = 0; d < NO_OF_COLORS; d++)
            if (temp_char == calc_font_colors[d])
            {
                input_font.style = d, flag = false;
                input_font.update();
                break;
            }
        if (flag)
            sprintf(Error.str(), "Error: Font style not defined");
    }
    else if (!strncasecmp(a.str(), "output font style ", 18))
    {
        extract(a.str(), temp_char.str(), 18);
        bool flag = true;
        for (int d = 0; d < NO_OF_STYLES; d++)
            if (temp_char == calc_font_styles[d])
            {
                output_font.style = d, flag = false;
                output_font.update();
                break;
            }
        if (flag)
            sprintf(Error.str(), "Error: Font style not defined");
    }
    else if (!strncasecmp(a.str(), "error font style ", 17))
    {
        extract(a.str(), temp_char.str(), 17);
        bool flag = true;
        for (int d = 0; d < NO_OF_STYLES; d++)
            if (temp_char == calc_font_styles[d])
            {
                error_font.style = d, flag = false;
                error_font.update();
                break;
            }
        if (flag)
            sprintf(Error.str(), "Error: Font style not defined");
    }
    else if (!strncasecmp(a.str(), "prompt font style ", 18))
    {
        extract(a.str(), temp_char.str(), 18);
        bool flag = true;
        for (int d = 0; d < NO_OF_STYLES; d++)
            if (temp_char == calc_font_styles[d])
            {
                prompt_font.style = d, flag = false;
                prompt_font.update();
                break;
            }
        if (flag)
            sprintf(Error.str(), "Error: Font style not defined");
    }
#endif


#ifdef FACTORIZE
    else if (!strncasecmp(a.str(), "factorise ", 10) || !strncasecmp(a.str(), "factorize ", 10))
    {
        long double x = 0.0;
        signed char check_calculate = calculate(a.str(), x, i = 10);
        if (check_calculate == SUCCESS)
        {
            fprintf(PRINTFAST, "\nFactors : ");
            for (long double g = 1; g <= x / 2; g++)
                if (!fmodl(x, g))
                    fprintf(PRINTFAST, "%.0Lf, ", g);
            fprintf(PRINTFAST, "%.0Lf", x);
#ifdef CALC_HISTORY
            if (!(record & EXPRESSION_COMMANDS))
                h.pop();
#endif
        }
        else if (check_calculate == ERROR)
#ifdef CALC_HISTORY
        {
#endif
            Error += " Error!!";
#ifdef CALC_HISTORY
            if (!(record & EXPRESSIONS_HAVING_ERROR))
                h.pop();
        }
#endif
        else if (check_calculate == FAILURE)
#ifdef CALC_HISTORY
        {
#endif
            sprintf(Error.str(), "\nUndefined symbols in \'%s\'", a.str());
#ifdef CALC_HISTORY
            if (!(record & EXPRESSIONS_HAVING_ERROR))
                h.pop();
        }
#endif
        num.deallocate();
        optr.deallocate();
    }
#endif // FACTORIZE


#ifdef SUM
    /* Condition for calculating sum */
    else if (!strncasecmp(a.str(), "sum ", 4))
    {
        long double x = 0.0;
        i = 4;
        while (!isdigit(a[i]) && a[i])
            i++;
        if (atof(a.str(), i, x, INT) <= FAILURE)
#ifdef CALC_HISTORY
        {
#endif
            Error = "!!Limit should be integer!!";
#ifdef CALC_HISTORY
            if (!(record & EXPRESSIONS_HAVING_ERROR))
                h.pop();
        }
#endif
        else
        {
            long lower_limit = x;
            while (!isdigit(a[i]) && a[i])
                i++;
            if (atof(a.str(), i, x = 0.0, INT) <= FAILURE)
#ifdef CALC_HISTORY
            {
#endif
                Error = "!!Limit should be integer!!";
#ifdef CALC_HISTORY
                if (!(record & EXPRESSIONS_HAVING_ERROR))
                    h.pop();
            }
#endif
            else
            {
                long upper_limit = x;
                if (lower_limit > upper_limit)
#ifdef CALC_HISTORY
                {
#endif
                    Error = "!!Lower limit should not be greater than upper limit!!";
#ifdef CALC_HISTORY
                    if (!(record & EXPRESSIONS_HAVING_ERROR))
                        h.pop();
                }
#endif
                else
                {
                    while (!ismathchar(a[i]) && !isdigit(a[i]) && a[i])
                        i++;
                    long double sum = 0.0;
                    signed char check_calculate;
                    unsigned long p = (upper_limit - lower_limit) / 50;

                    fprintf(PRINTFAST, "\nSuming expression \"");
                    for (unsigned long m = i; a[m]; m++)
                        fprintf(PRINTFAST, "%c", a[m]);
                    fprintf(PRINTFAST, "\" from i = %ld to i = %ld\n", lower_limit, upper_limit);

                    /* Loop for summing expression from lower to upper limit */
                    for (; lower_limit <= upper_limit; lower_limit++)
                    {
                        unsigned long m = i;
                        check_calculate = calculate(a.str(), x, m, '\0', lower_limit);
                        if (check_calculate == SUCCESS)
                        {
                            sum += x;
                            oprator_detail = num_detail = NO;
                            if (p && (upper_limit - lower_limit) % p == 0)
                                fprintf(PRINTFAST, "-");
#ifdef CALC_HISTORY
                            if (!(record & EXPRESSION_COMMANDS))
                                h.pop();
#endif
                        }
                        else if (check_calculate == ERROR)
                        {
                            Error += " Error!! in expression";
#ifdef CALC_HISTORY
                            if (!(record & EXPRESSIONS_HAVING_ERROR))
                                h.pop();
#endif
                            break;
                        }
                        else if (check_calculate == FAILURE)
                        {
                            sprintf(Error.str(), "Failure to recognise expression in \"%s\"", a.str());
#ifdef CALC_HISTORY
                            if (!(record & EXPRESSIONS_HAVING_ERROR))
                                h.pop();
#endif
                            break;
                        }
                    }
                    /********************************************************/

                    /* For printing the sum and storing in answer list */
                    if (check_calculate == SUCCESS)
                    {
                        if (p)
                            fprintf(PRINTFAST, "\n");
                        fprintf(PRINTFAST, "Sum = ");
                        fprintf(PRINTFAST, precision, sum);
                        if (store == 1)
                            l.add_ans(sum);
                    }
                    /***************************************************/

                    /* Deallocating num and oprator stacks in case of errors */
                    num.deallocate();
                    optr.deallocate();
                    /*********************************************************/
                }
            }
        }
    }
    /**************************/
#endif // SUM


    else						// for calculating the expression
    {
        long double x = 0.0;
        signed char check_calculate = calculate(a.str(), x, i = 0);
        if (check_calculate == SUCCESS)
        {
            fprintf(PRINTFAST, " = ");
            fprintf(PRINTFAST, precision, x);
#ifdef ANS_CMD
            if (store == YES)
                l.add_ans(x);
#endif // ANS_CMD
#ifdef CALC_HISTORY
            if (!(record & EXPRESSION_COMMANDS))
                h.pop();
#endif
        }
        else if (check_calculate == ERROR)
#ifdef CALC_HISTORY
        {
#endif
            Error += " Error!!";
#ifdef CALC_HISTORY
            if (!(record & EXPRESSIONS_HAVING_ERROR))
                h.pop();
        }
#endif
        else if (check_calculate == FAILURE)
#ifdef CALC_HISTORY
        {
#endif
            sprintf(Error.str(), "\nUndefined command \"%s\"", a.str());
#ifdef CALC_HISTORY
            if (!(record & UNDEFINED_COMMANDS))
                h.pop();
        }
#endif
        num.deallocate();
        optr.deallocate();
    }

    if (Error == "")
    {
        fprintf(PRINTFAST, "\n");

#ifdef CALC_PROCESS_TIME

        time_taken = ((long double)(clock() - start)) / CLOCKS_PER_SEC;

        if (calc_time == YES)
            fprintf(PRINTFAST, "Expression Processing Time : %.8Lf seconds\n", time_taken);

        if (calc_time == YES && calc_avg_time == YES)
            expressions++, total_time += time_taken;
#endif // CALC_PROCESS_TIME
    }
}
