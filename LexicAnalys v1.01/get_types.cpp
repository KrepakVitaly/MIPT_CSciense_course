/*
 * get_types.cpp
 *
 *  Created on: 19.12.2010
 *      Author: Serov Artem, Penkin Ivan, Krepak Vitaliy, Kovalkov Konstantin, Smirnov Igor
 */

#include <ctype.h>
#include <string.h>
#include <stdio.h>

#include "consts.h"

int IsKeyWord (char* name)
{
    int result = 1;
    for (int i = 0; i < MAXNKEYWORDS; i++)
    {
        if (!strcmp(name, KeyWords[i]))
        {
            result = 0;
            break;
        }
    }
    return result;
}


int GetType (char* cur)
{
    if (*cur == ' ')
        return stSpace;
    else
    if (*cur == '(')
        return stOpen;
    if (*cur == ')')
        return stClose;
    else
    if (isdigit((int)*cur))
        return stDigit;
    else
    if (isalpha((int)*cur))
        return stAlpha;
    else
    if (*cur == '+'|| *cur == '*' || *cur == '/' || *cur == '^' )
        return stBinOp;
    else
    if (*cur == '-')
        return stMinus;
    else
        return stError;
}

int GetTokenType (char* cur)
{
    if (*cur == '(')
        return tkOpen;
    if (*cur == ')')
        return tkClose;
    else
    if (*cur == '+'|| *cur == '*' || *cur == '/' || *cur == '^' || *cur == '-' )
        return tkBinOper;
}
