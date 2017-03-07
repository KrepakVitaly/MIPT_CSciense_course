/*
 * main.cpp
 *
 *  Created on: 19.12.2010
 *      Author: Serov Artem, Penkin Ivan, Krepak Vitaliy, Kovalkov Konstantin, Smirnov Igor
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "spaces_analysis.h"
#include "rule_functions.h"
#include "consts.h"
#include "get_types.h"
#include "fsm.h"


int main()
{
    printf ("\nResult of LA is %d.\n", !LexicalAnalysis());
    return 0;
}
