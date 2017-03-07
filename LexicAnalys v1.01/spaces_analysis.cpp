/*
 * spaces_analysis.cpp
 *
 *  Created on: 21.12.2010
 *      Author: Penkin Ivan, Krepak Vitaliy, Kovalkov Konstantin
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

///////////////////////////////////
//связать с кодами ошибок программы
const int ErrNullAdr  			= 19;
const int ErrEmptyStr 			= 20;
const int ErrUnexpSpace		    = 21;
const int ErrUnexpCloseBrckt	= 22;
const int ErrWrongExpression	= ErrUnexpCloseBrckt;

///////////////////////////////////



int SpacesAndBracketsAnalysis ( char* inp_string )
{
	//MAIN_CHECKING
	if ( inp_string == NULL ) return ErrNullAdr;
	//

	//SUB_MAIN_CHECKING
	if ( *inp_string == '\0') return ErrEmptyStr;
	//

	char* current 	= inp_string;
	char* next 		= current + 1;
	char* after_next 	= next + 1;

	char* write_i	= current;

	int unclosed_brackets = 0;

	if ( *current == ' ' )
	{
		current++;
		next++;
		after_next++;
	}

	while ( *after_next != '\0' )
	{
		//SITUATION_IS_BAD
		if (	( isdigit (*current) && *next == ' ' && isdigit ( *after_next ) ) ||
				( isalpha (*current) && *next == ' ' && isalpha ( *after_next ) ) ||
				( isdigit (*current) && *next == ' ' && isalpha ( *after_next ) ) ||
				( isalpha (*current) && *next == ' ' && isdigit ( *after_next ) ) 		) return ErrUnexpSpace;
		//

		//SITUATION_IS_"cos__________________(0)"
		if ( 	( isdigit (*current) && *next == ' ' && *after_next == ' ' ) ||
				( isalpha (*current) && *next == ' ' && *after_next == ' ' )		)
			{
				next++;
				after_next++;
				continue;
			}
		//

		//SITUATION_IS_PREV_OK
		if ( *current == '(' ) unclosed_brackets++;
		if ( *current == ')' ) unclosed_brackets--;

		if (  unclosed_brackets == -1 	) return ErrUnexpCloseBrckt;
		//

		//SITUATION_IS_OK
		if ( *current != ' ' )
			{
				*write_i = *current;
				write_i++;
			}

		current 	 = next;
		next = after_next;
		after_next++;
		//
	}

	for ( int i = 1; i <= 2; i++ )
		if ( *current != ' ' )
		{
			*write_i = *current;
			write_i++;
			current++;
		}

	*write_i = '\0';

	if ( unclosed_brackets != 0 ) return ErrWrongExpression;

	return 0;
}
