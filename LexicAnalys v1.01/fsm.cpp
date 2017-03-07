/*
 * fsm.cpp
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

//====================================================================================
//=== Function's Implementations ============================================================================
//====================================================================================

int LexicalAnalysis ()
{
    FiniteStateMachine_t           fsm = {};
    FSMInitialize (&fsm);


    char str[MAXSTR] = "5 + 6";

    printf ("<%s>\n", str);

    if (int ret = SpacesAndBracketsAnalysis (&str[0]))
    {
        Error(str, ret, 0);
        return stError;
    }

    printf ("<%s>\n", str);

    AllRulesInit       (&fsm);

    if (!FSMProcessing (&fsm, str))
        return stError;

    return 0;
}

char*   GetExpr             (char* expr)
{
    return expr;
}

// 49 lines of horror right now. Don't look into breackets.
void AllRulesInit    (FiniteStateMachine_t* fsm)
{
    //Rules
    RuleInit    (fsm, stOpen,  stBinOp,  0, Error);
    RuleInit    (fsm, stClose, stOpen,   1, Error);
    RuleInit    (fsm, stClose, stDigit,  2, Error);
    RuleInit    (fsm, stClose, stAlpha,  3, Error);
    RuleInit    (fsm, stBinOp, stClose,  4, Error);
    RuleInit    (fsm, stBinOp, stBinOp,  5, Error);
    RuleInit    (fsm, stBinOp, stMinus,  6, Error);
    RuleInit    (fsm, stMinus, stClose,  7, Error);
    RuleInit    (fsm, stMinus, stBinOp,  8, Error);
    RuleInit    (fsm, stMinus, stMinus,  9, Error);
    RuleInit    (fsm, stDigit, stOpen,  10, Error);
    RuleInit    (fsm, stDigit, stAlpha, 11, Error);
    RuleInit    (fsm, stAlpha, stBinOp, 12, Error);
    RuleInit    (fsm, stAlpha, stMinus, 13, Error);
    RuleInit    (fsm, stAlpha, stDigit, 14, Error);
    RuleInit    (fsm, stAlpha, stClose, 15, Error);

    RuleInit    (fsm, stSpace, stSpace, 0, DoNothing);
    RuleInit    (fsm, stSpace, stOpen,  0, DoNothing);
    RuleInit    (fsm, stSpace, stClose, 0, DoNothing);
    RuleInit    (fsm, stSpace, stBinOp, 0, DoNothing);
    RuleInit    (fsm, stSpace, stMinus, 0, DoNothing);

    RuleInit    (fsm, stOpen,  stSpace, 0, DoNothing);
    RuleInit    (fsm, stClose, stSpace, 0, DoNothing);
    RuleInit    (fsm, stBinOp, stSpace, 0, DoNothing);
    RuleInit    (fsm, stMinus, stSpace, 0, DoNothing);
    RuleInit    (fsm, stSpace, stDigit, 0, DoNothing);
    RuleInit    (fsm, stSpace, stAlpha, 0, DoNothing);

    RuleInit    (fsm, stOpen,  stOpen,  tkOpen,    AddToken);
    RuleInit    (fsm, stOpen,  stClose, tkClose,   AddToken);
    RuleInit    (fsm, stOpen,  stMinus, tkUnMinus, AddToken);

    RuleInit    (fsm, stClose, stClose, tkClose,   AddToken);
    RuleInit    (fsm, stClose, stBinOp, tkBinOper, AddToken);
    RuleInit    (fsm, stClose, stMinus, tkBinOper, AddToken);

    RuleInit    (fsm, stBinOp, stOpen,  tkOpen,    AddToken);
    RuleInit    (fsm, stMinus, stOpen,  tkOpen,    AddToken);

    RuleInit    (fsm, stOpen,  stDigit, -1, NumConcat);//конкат
    RuleInit    (fsm, stBinOp, stDigit, -1, NumConcat);
    RuleInit    (fsm, stMinus, stDigit, -1, NumConcat);
    RuleInit    (fsm, stDigit, stDigit, -1, NumConcat);

    RuleInit    (fsm, stDigit, stSpace, -2,         NumConcat); //nothing
    RuleInit    (fsm, stDigit, stClose,  tkOpen,    NumConcat);
    RuleInit    (fsm, stDigit, stBinOp,  tkBinOper, NumConcat);
    RuleInit    (fsm, stDigit, stMinus,  tkBinOper, NumConcat);

    RuleInit    (fsm, stOpen,  stAlpha, -1, NameConcat);//конкат
    RuleInit    (fsm, stBinOp, stAlpha, -1, NameConcat);
    RuleInit    (fsm, stMinus, stAlpha, -1, NameConcat);
    RuleInit    (fsm, stAlpha, stAlpha, -1, NameConcat);

    RuleInit    (fsm, stAlpha, stSpace, -2,        NameConcat); //nothing
    RuleInit    (fsm, stAlpha, stOpen,  tkOpen,    NameConcat);
}

int IsIncludedInList (char* cur, int* list)
{
    for (int i = 0; i < MAXSTATES; i++)
    {
        if (list[i] == GetType(cur))
            return 1;
    }
    return 0;
}

int FSMProcessing    (FiniteStateMachine_t* fsm, char* str)
{
    char* cur = str;

    if (IsIncludedInList (cur, fsm->nonFirstStates_))
    {
        Error(cur, 16, 0);
        return stError;
    }

    char expr [MAXSTR] = "(";
    strcat (expr, str);
    strcat (expr, ")");
    cur =   expr;

    fsm->prevState_ = stOpen;

    int strlength   = strlen (expr);

    for (int count  = 0; count < strlength; count++)
    {
        if (!FSM_IsOk)
            return stError;

        int  curtype	= GetType (cur);
        if (curtype == stError)
        {
            Error(cur, 18, 0);
            return stError;
        }

        fsm->curState_	= curtype;
        rule_t* curRule = &(fsm->statesMatrix_[fsm->prevState_][fsm->curState_]);

        if  ((*(curRule->Action_p)) (cur, curRule->code_, count) == stError)
            return stError;
        else
            fsm->prevState_ = curtype;

        cur++;
    }

    return 1;
}

void  RuleInit      (FiniteStateMachine_t* fsm, int line,   int column, int code,
                      int (*Action) (char* cur, int param,  int count))
{
    fsm->statesMatrix_ [line][column].code_    = code;
    fsm->statesMatrix_ [line][column].Action_p = Action;
}

int FSM_IsOk        (FiniteStateMachine_t* fsm)
{
    if (fsm->prevState_ == stError)
        return 0;
    else
        return 1;
}

void FSMInitialize  (FiniteStateMachine_t* fsm)
{
    memset (fsm, 0, sizeof (fsm));
    fsm->nonFirstStates_ [0] = stError;
    fsm->nonFirstStates_ [1] = stClose;
    fsm->nonFirstStates_ [2] = stBinOp;

    fsm->nonFinalStates_ [0] = stBinOp;
    fsm->nonFinalStates_ [1] = stOpen;
    fsm->nonFinalStates_ [2] = stAlpha;
    fsm->nonFinalStates_ [3] = stMinus;
}

void StatesMatrixInitialize  (FiniteStateMachine_t* fsm, int line,  int column,
                                int code, int (*Action) (char* cur, int param, int count))
{
    fsm->statesMatrix_[line][column].code_    = code;
    fsm->statesMatrix_[line][column].Action_p = Action;
}
