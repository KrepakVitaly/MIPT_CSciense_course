/*
 * get_types.h
 *
 *  Created on: 19.12.2010
 *      Author: Serov Artem, Penkin Ivan, Krepak Vitaliy, Kovalkov Konstantin, Smirnov Igor
 */

#ifndef CONSTS_H_INCLUDED
#define CONSTS_H_INCLUDED

const int MAXSTATES    = 8;
const int MAXREALST    = 7;
const int MAXSTR       = 4096;
const int MAXNAME      = 8;
const int MAXNERRORS   = 24;
const int MAXNKEYWORDS = 4;

const char ErrorsDescription [MAXNERRORS][MAXSTR] =

/*  0 */       {"There is a binary operation after the open bracket.",
/*  1 */        "There is an opening bracket after the closing bracket.",
/*  2 */        "There is a number after the closing bracket.",
/*  3 */        "There is a letter after the closing bracket.",
/*  4 */        "There is a closing bracket after the binary operation.",
/*  5 */        "There is a binary operation after the binary operation.",
/*  6 */        "There is a minus sign after the binary operation.",
/*  7 */        "There is a closing bracket after the minus.",
/*  8 */        "There is a binary operation after the minus.",
/*  9 */        "There is a minus after the minus.",
/* 10 */        "There is an opening bracket after the number.",
/* 11 */        "There is a letter after the number.",
/* 12 */        "There is a binary operation after the letter.",
/* 13 */        "There is a minus sign after the letter.",
/* 14 */        "There is a number after the letter.",
/* 15 */        "There is a closing bracket after the letter.",
/* 16 */        "The expression begins with a nonpermissible symbol.",
/* 17 */        "The expression ends with a nonpermissible symbol.",
/* 18 */        "A nonpermissible symbol was found.",
/* 19 */        "Null-address was received by spaces_analysis.",
/* 20 */        "Empty string was received by spaces_analysis.",
/* 21 */        "An unexpectable space was found.",
/* 22 */        "The expression include a wrong bracket sub-expression",
/* 23 */        "An unknown command was found."
               };


const char KeyWords [MAXNKEYWORDS][MAXNAME] =
/*  0 */       {"sin",
/*  1 */        "cos",
/*  2 */        "sqrt",
/*  3 */        "ln"
               };

enum Tokens//Token Types (оцень холосо)
{
    tkOpen    = 0,
    tkClose   = 1,
    tkBinOper = 2,
    tkUnMinus = 3,
    tkUnOper  = 4,
    tkNumber  = 5
};

enum States//GetType
{
    stError = 0,
    stSpace = 1,
    stOpen  = 2,
    stClose = 3,
    stBinOp = 4,
    stMinus = 5,
    stDigit = 6,
    stAlpha = 7,
};

#endif // CONSTS_H_INCLUDED
