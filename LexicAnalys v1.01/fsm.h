/*
 * fsm.h
 *
 *  Created on: 19.12.2010
 *      Author: Serov Artem, Penkin Ivan, Krepak Vitaliy, Kovalkov Konstantin, Smirnov Igor
 */

#ifndef FSM_H_INCLUDED
#define FSM_H_INCLUDED

struct rule_t
{
    int code_;
    int (*Action_p) (char* cur, int code, int count);
};

struct FiniteStateMachine_t
{
    int    curState_;
    int    prevState_;
    rule_t statesMatrix_    [MAXSTATES][MAXSTATES];
    int    nonFirstStates_  [MAXSTATES];
    int    nonFinalStates_  [MAXSTATES];
};

int   LexicalAnalysis       ();
int   FSMProcessing      	(FiniteStateMachine_t* fsm, char* expr);
void  AllRulesInit       	(FiniteStateMachine_t* fsm);
void  FSMInitialize      	(FiniteStateMachine_t* fsm);
void  RuleInit           	(FiniteStateMachine_t* fsm, int line,  int column, int code,
                         	 int (*Action) (char* cur,  int param, int count));

int   IsIncludedInList   	(char* cur, int* list);
int   FSM_IsOk           	(FiniteStateMachine_t* fsm);

#endif // FSM_H_INCLUDED
