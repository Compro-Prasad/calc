#include <cal.hpp>
#include <calc_stacks/optr_stack.hpp>
#include <calc_stacks/num_stack.hpp>

#ifdef CALC_CAL_H
long double factorial(long double x)
{
    long double t = 1;
    for (long double i = 1; i <= x; i++)
        t *= i;
    return t;
}

signed char calculateit(const char *a, long double &ans, long double x, long double y)
{
    long double z = angle_type == DEG ? (x * PI / 180) : (angle_type == RAD ? x : (x * PI / 200));
    if (!strcmp(a, "+"))
        ans = x + y;
    else if (!strcmp(a, "-"))
        ans = x - y;
    else if (!strcmp(a, "*"))
        ans = x * y;
    else if (!strcmp(a, "/"))
    {
        if (y)
            ans = x / y;
        else
        {
            Error = "!!Divide";
            Err;
        }
    }
    else if (!strcmp(a, "!"))
    {
        if (x >= 0 && !(x - floorl(x)))
            ans = factorial(x);
        else
        {
            Error = "!!Factorial";
            Err;
        }
    }
    else if (!strcasecmp(a, "p"))
    {
        if (x >= 0 && y >= 0 && x >= y && !(x - floorl(x)) && !(y - floorl(y)))
            ans = factorial(x) / factorial(x - y);
        else
        {
            Error = "!!Factorial";
            Err;
        }
    }
    else if (!strcasecmp(a, "c"))
    {
        if (x >= 0 && y >= 0 && x >= y && !(x - floorl(x)) && !(y - floorl(y)))
            ans = factorial(x) / (factorial(y) * factorial(x - y));
        else
        {
            Error = "!!Factorial";
            Err;
        }
    }
    else if (!strcmp(a, ">>"))
        ans = (long)x >> (long)y;
    else if (!strcmp(a, "<<"))
        ans = (long)x << (long)y;
    else if (!strcmp(a, "~"))
        ans = ~(long)x;
    else if (!strcmp(a, "|"))
        ans = (long)x | (long)y;
    else if (!strcmp(a, "&"))
        ans = (long)x & (long)y;
    else if (!strcmp(a, "%"))
        ans = (long)x % (long)y;
    else if (!strcasecmp(a, "log"))
    {
        if (y > 0 && x >= 0)
            ans = logl(y) / logl(x);
        else
        {
            Error = "!!log";
            Err;
        }
    }
    else if (!strcasecmp(a, "abs"))
        ans = fabsl(x);
    else if (!strcasecmp(a, "ceil"))
        ans = ceill(x);
    else if (!strcasecmp(a, "floor"))
        ans = floorl(x);
    else if (!strcasecmp(a, "ln"))
    {
        if (x > 0)
            ans = logl(x);
        else
        {
            Error = "!!log";
            Err;
        }
    }
    else if (!strcasecmp(a, "logten"))
    {
        if (x > 0)
            ans = log10l(x);
        else
        {
            Error = "!!log";
            Err;
        }
    }
    else if (!strcasecmp(a, "sinh"))
        ans = sinhl(z);
    else if (!strcasecmp(a, "cosh"))
        ans = coshl(z);
    else if (!strcasecmp(a, "tanh"))
        ans = tanhl(z);
    else if (!strcasecmp(a, "sin"))
        ans = sinl(z);
    else if (!strcasecmp(a, "cos"))
        ans = cosl(z);
    else if (!strcasecmp(a, "tan"))
    {
        if (cosl(z))
            ans = tanl(z);
        else
        {
            Error = "!!tan Undefined";
            Err;
        }
    }
    else if (!strcasecmp(a, "cosec"))
    {
        if (sinl(z))
            ans = 1 / sinl(z);
        else
        {
            Error = "!!cosec undefined";
            Err;
        }
    }
    else if (!strcasecmp(a, "sec"))
    {
        if (cosl(z))
            ans = 1 / cosl(z);
        else
        {
            Error = "!!sec undefined";
            Err;
        }
    }
    else if (!strcasecmp(a, "cot"))
    {
        if (sinl(z))
            ans = 1 / tanl(z);
        else
        {
            Error = "!!cot undefined";
            Err;
        }
    }
    else if (!strcasecmp(a, "asin"))
    {
        if (x <= 1 && x >= -1)
            ans = angle_type == DEG ? (asinl(x) * 180 / PI) :
                  angle_type == GRAD ? (asinl(x) * 200 / PI) : (asinl(x));
        else
        {
            Error = "!!asin(x) domain";
            Err;
        }
    }
    else if (!strcasecmp(a, "acos"))
    {
        if (x <= 1 && x >= -1)
            ans = angle_type == DEG ? (acosl(x) * 180 / PI) :
                  angle_type == GRAD ? (acosl(x) * 200 / PI) : (acosl(x));
        else
        {
            Error = "!!acos(x) domain";
            Err;
        }
    }
    else if (!strcasecmp(a, "atan"))
        ans = angle_type == DEG ? (atanl(x) * 180 / PI) :
              angle_type == GRAD ? (atanl(x) * 200 / PI) : (atanl(x));
    else if (!strcasecmp(a, "acosec"))
    {
        if (x <= -1 && x >= 1)
            ans = angle_type == DEG ? (asinl(1 / x) * 180 / PI) :
                  angle_type == GRAD ? (asinl(1 / x) * 200 / PI) : (asinl(1 / x));
        else
        {
            Error = "!!acosec(x) domain";
            Err;
        }
    }
    else if (!strcasecmp(a, "asec"))
    {
        if (x <= -1 && x >= 1)
            ans = angle_type == DEG ? (acosl(1 / x) * 180 / PI) :
                  angle_type == GRAD ? (acosl(1 / x) * 200 / PI) : (acosl(1 / x));
        else
        {
            Error = "!!asec(x) domain";
            Err;
        }
    }
    else if (!strcasecmp(a, "acot"))
        ans = angle_type == DEG ? (atanl(1 / x) * 180 / PI) :
              angle_type == GRAD ? (atanl(1 / x) * 200 / PI) : (atanl(1 / x));
    else if (!strcmp(a, "^"))
        ans = powl(x, y);
    else
    {
        Error = "!!Calculateit";
        return FAILURE;
    }
    return SUCCESS;
}

signed char insert(const char *s)
{
    if (s)
    {
        long double x, y, z;
        char *top_optr = optr.get();
        if (check_priority(top_optr, s) == HIGH)
        {
#ifdef OPTR_DETAILS
            if (oprator_detail == YES)
                fprintf(PRINTFAST, "\nPriority of \'%s\' is higher than \'%s\'", top_optr, s);
#endif
            while (check_priority(top_optr, s) == HIGH
                   && (strcmp(s, ")") || strcmp(top_optr, "(")))
            {
                if (!top_optr)
                {
                    Error = Operator;
                    Err;
                }
                if (isbinary(top_optr))
                {
                    if (num.get(y) != SUCCESS || num.get(x) != SUCCESS)
                    {
                        Error = Number;
                        Err;
                    }
                    if (calculateit(top_optr, z, x, y) != SUCCESS)
                        Err;
#ifdef STEPS_CMD
                    else if (steps == YES)
                        fprintf(PRINTFAST, "\n-> %.3LG %s %.3LG = %.3LG", x, top_optr, y, z);
#endif
                }
                else if (isunary(top_optr))
                {
                    if (num.get(x) != SUCCESS)
                    {
                        Error = Number;
                        Err;
                    }
                    if (calculateit(top_optr, z, x) != SUCCESS)
                        Err;
#ifdef STEPS_CMD
                    else if (steps == YES)
                        fprintf(PRINTFAST, "\n-> %s(%.3LG) = %.3LG", top_optr, x, z);
#endif
                }
                if (optr.pop() != SUCCESS)
                {
                    Error = "!!Operator pop";
                    Err;
                }
                if (num.push(z) != SUCCESS)
                {
                    Error = "!!Number push";
                    Err;
                }
                top_optr = optr.get();
            }
            if (strcmp(s, ")"))
            {
                if (optr.push(s) == ERROR)
                    return 5;
            }
            else
                optr.pop();
        }
        else if (!top_optr || check_priority(top_optr, s) == LOW)
        {
#ifdef OPTR_DETAILS
            if (oprator_detail == YES)
                fprintf(PRINTFAST, "\nPriority of \'%s\' is lower than \'%s\'", top_optr, s);
#endif
            if (optr.push(s) == ERROR)
                return 5;
        }
        else
        {
            Error = "!!Priority";
            Err;
        }
        return SUCCESS;
    }
  Err;
}

signed char calculate(char *a, long double &n, unsigned long i, const char ch, const long var)
{
    unsigned char check_extract;
#ifdef ANS_CMD
    unsigned long ans_no;
#endif
    long double x, y;
    char c[10];
    for (; a[i] != ch;)
    {
        SKIP_SPACE(a, i);

        /******************Factorial******************/
        /* It is a special kind of unary operator which
           stands after the number whose factorial is to be calculated */
        if (a[i] == '!')
        {
            num.get(x);
            if (calculateit("!", y, x) != SUCCESS)
                Err;
            num.push(y);
            i++;
            continue;
            SKIP_SPACE(a, i);
        }
        /***********************************************/

        if (a[i] == '+' || a[i] == '-')
        {
            // condition to tackle continuous random + and/or -
            int t = 1;
            if (i == 0)
                num.push(0);
            while (a[i] == '+' || a[i] == '-')
                if (a[i++] == '-')
                    t = t * (-1);
#ifdef OPTR_DETAILS
            if (oprator_detail == YES)
                fprintf(PRINTFAST, "\nPushing \'%c\' from special area", t < 0 ? '-' : '+');
#endif
            /*if (t < 0)
            {*/
                if (insert(t < 0 ? "-" : "+") == ERROR)
                    Err;/*
            }
            else if (insert("+") == ERROR)
                Err;*/
            SKIP_SPACE(a, i);
        }
        if (a[i] == 'i')
        {
            i++;
            num.push(var);
            while (a[i] == ' ')
                i++;
            if (!a[i])
                break;
            SKIP_SPACE(a, i);
        }
        x = 0.0;
        check_extract = extract_math(a, i, x, c);
        if (!check_extract)
            return FAILURE;
        else if (check_extract == 1)
        {
            num.push(x);
            x = 0.0;
            SKIP_SPACE(a, i);
#ifdef CONST_CMDS
            unsigned long j = i;
#endif
            if ((isalpha(a[i])
                    && (
#ifdef CONST_CMDS
                        cons.get_const(a, j) ||
#endif
                        (a[i] != 'P' && tolower(a[i]) != 'l' && a[i] != 'C')))
                    || a[i] == '(')
                if (insert("*") == ERROR)
                    Err;
        }
#ifdef ANS_CMD
        else if (check_extract == 4)
        {
            if (separate_ans(a, i, ans_no) == ERROR)
            {
                Error = "!!Answer";
                Err;
            }
            if (num.push(l.get_ans_x(ans_no).n) == ERROR)
            {
                Error = "!!Number linker";
                Err;
            }
        }
#endif
        else if (check_extract == 3)
        {
            if (insert(c) == ERROR)
                Err;
            else
            {
                SKIP_SPACE(a, i);
                if ((a[i] == '-' || a[i] == '+') && isdigit(a[i + 1]))
                {
                    atof(a, i, x);
                    num.push(x);
                }
            }
        }
        else if (check_extract == 2)
        {
            if (!strcmp(c, "("))
            {
                if (optr.push(c) == ERROR)
                    return 5;
                if (a[i] == '-' || a[i] == '+')
                    num.push(0);
            }
            else
            {
                if (!optr.check_brac())
                {
                    Error = "!!Bracket";
                    Err;
                }
                if (insert(c) == ERROR)
                    Err;
                SKIP_SPACE(a, i);
#ifdef CONST_CMDS
                unsigned long j = i;
#endif
                if ((isalpha(a[i])
                        && (
#ifdef CONST_CMDS
                            cons.get_const(a, j) ||
#endif
                            (a[i] != 'P' && tolower(a[i]) != 'l'
                             && a[i] != 'C'))) || a[i] == '('
                        || isdigit(a[i]))
                    if (insert("*") == ERROR)
                        Err;
            }
        }
    }							// loop ends
    while (optr.get())
        if (insert(")") == ERROR)
            Err;
    if (num.get(n) != SUCCESS)
        return FAILURE;
    if (num.get(y) == SUCCESS)
    {
        Error = Operator;
        Err;
    }
    if (optr.get())
    {
        Error = Number;
        Err;
    }
#if defined(STEPS_CMD) || defined(OPTR_DETAILS) || defined(NUM_DETAILS)
    if (
#ifdef STEPS_CMD
        steps == YES
#else
        0
#endif
#ifdef OPTR_DETAILS
        || oprator_detail == YES
#endif
#ifdef NUM_DETAILS
        || num_detail == YES
#endif
    )
        fprintf(PRINTFAST, "\n");
#endif
    return SUCCESS;
}
#endif // CALC_CAL_H
