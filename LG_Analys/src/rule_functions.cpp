/*
 * rule_functions.cpp
 *
 *  Created on: 19.12.2010
 *      Author: Serov Artem, Penkin Ivan, Krepak Vitaliy, Kovalkov Konstantin, Smirnov Igor
 */

#include <stdio.h>
#include <string.h>

#include "consts.h"
#include "get_types.h"
#include "rule_functions.h"
#include "fsm.h"

FILE* Output = fopen ("tokens.txt", "w");

int NameConcat  (char* cur, int code, int count)
{
    static char name[MAXNAME] = {};
    if (code == -1)
    {
        char      tempstr [MAXSTR] = "";
        strncpy  (tempstr, cur, 1);
        strcat   (name, tempstr);
    }
    else
    {
        if (IsKeyWord (name))
        {
            Error (cur, 23, count);
            //printf ("s = <%s>\n", name);
            return stError;
        }
        fprintf  (Output, "%d %s\n", tkUnOper, name);
        strcpy   (name, "");
        AddToken (cur, GetTokenType (cur), count);
    }
    return 1;
}

int DoNothing   (char* cur, int code, int count)
{
    return 1;
}

int AddToken    (char* cur, int code, int count)
{
    fprintf (Output, "%d %c\n", code, *cur);

    return 1;
}

int NumConcat   (char* cur, int code, int count)
{
    static int num = 0;
    if (code == -1)
    {
        num = num * 10 + *cur - '0';

    }
    else
    {
        fprintf (Output, "%d %d\n", tkNumber, num);
        num = 0;
        AddToken (cur, GetTokenType (cur), count);
    }
    return 1;
}

int Error      (char* cur, int code, int count)
{
    printf ("%s\n", cur - count);
    printf ("\nError! Position %d. %s\n", count, ErrorsDescription[code]);
    return stError;
}

void Close_Token_File ()
{
	fclose(Output);
	return;
}
