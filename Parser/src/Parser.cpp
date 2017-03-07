///  \brief          Распознаватель выражений

///
///  \description
///  \author		   Крепак zorroxied Виталий 016 ФРТК

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <windows.h>
#include <assert.h>


//------------------------------------------------------------------------------
//------Constants---------------------------------------------------------------


//Коды ошибок
int const  NO_ERR      =    0;
int const  ERR_FIND    =   -1;
int const  MISS_BRC    =   -2;
int const  UNKNOW_SYMB =   -9;
int const  FILE_NOTFND =   -5;
int const  CUR_NULL    = -666;


//------------------------------------------------------------------------------
//------Global_Variables--------------------------------------------------------

char* Cur = NULL;

int err_code = NO_ERR;

//------------------------------------------------------------------------------
//------My_Types----------------------------------------------------------------



//------------------------------------------------------------------------------
//---------Functions_Prototypes-------------------------------------------------

double  GetG ();

double  GetE ();

double  GetT ();

double  GetP ();

double  GetN ();

void  error ( int const _err_code );

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

int main()
{
	char* in_expr = "input_expression.txt";
	FILE* input_expr = fopen( in_expr, "r" );
	if ( input_expr == NULL )
		{
			error( FILE_NOTFND );
			system ( "PAUSE" );
			return -1;
		}

	fseek ( input_expr, 0, SEEK_END );
	int length = ftell ( input_expr );

	Cur = (char*) calloc ( length, sizeof(char) );
	if ( Cur == NULL)
		{
			error( CUR_NULL );
			system ( "PAUSE" );
			return -1;
		}

	char* Beginning = Cur;
	char* temp = Beginning + length*sizeof(char);
	*temp = '\0';

	fseek ( input_expr, 0, SEEK_SET );
	fread ( Cur , sizeof(char), length, input_expr );

	double value = GetG();

	free( Beginning );
	fclose( input_expr );

	if ( err_code != NO_ERR )
		{
			system ( "PAUSE" );
			return ERR_FIND;
		}

	printf( "Solve =  %f \n", value );

	system ( "PAUSE" );
	return 0;
}

//------------------------------------------------------------------------------

//WITH_DEFINE_PART_BEGIN--------------------------------------------------------
//------------------------------------------------------------------------------
#define ERROR_( err_code )		\
			{					\
			error( err_code );  \
			return err_code;	\
			}					\
//------------------------------------------------------------------------------

double GetG ()
{
	//printf("I'm at GetG, %p, 'Cur' = %c \n", Cur, *Cur );
	double value = GetE();

	if ( err_code != NO_ERR ) return ERR_FIND;
	if (    *Cur == '\0'    ) return value;

	ERROR_( UNKNOW_SYMB );
}

//------------------------------------------------------------------------------

double GetE ()
{
	if (     Cur == NULL    ) ERROR_( CUR_NULL );
	if ( err_code != NO_ERR ) return ERR_FIND;

	double value = GetT();

	while (  *Cur == '+' ||  *Cur == '-' )
	{
		if ( *Cur == '+' ) { Cur++; value = value + GetT(); }
		if ( *Cur == '-' ) { Cur++; value = value - GetT(); }
		//printf("I'm at GetE, %p, 'Cur' = %c \n", Cur, *Cur );
	}
	return value;
}

//------------------------------------------------------------------------------

double GetT ()
{
	if (      Cur == NULL   ) ERROR_( CUR_NULL );
	if ( err_code != NO_ERR ) return ERR_FIND;

	double value = GetP();
	if ( err_code != NO_ERR ) return ERR_FIND;

	while ( *Cur == '*' ||  *Cur == '/' )
	{
		//printf("I'm at GetT before iter, %p, 'Cur' = %c \n", Cur, *Cur );
		if ( *Cur == '*' ) { Cur++; value = value*GetP(); }
		if ( *Cur == '/' ) { Cur++; value = value/GetP(); }//TODO division by zero
		//printf("I'm at GetT after iter, %p, 'Cur' = %c \n", Cur, *Cur );

		if ( err_code != NO_ERR ) return ERR_FIND;
	}

	return value;
}

//------------------------------------------------------------------------------

double GetP ()
{
	if (      Cur == NULL   ) ERROR_( CUR_NULL );
	if ( err_code != NO_ERR ) return ERR_FIND;

	double value = 0;
	//printf("I'm at beginning GetP, %p, 'Cur' = %c \n", Cur, *Cur );

	if ( *Cur == '(' )
		{
			Cur++;
			value = GetE();
			if ( err_code != NO_ERR ) return ERR_FIND;
			//printf("I'm at GetP(), %p, 'Cur' = %c \n", Cur, *Cur );
			if ( *Cur != ')' ) ERROR_( MISS_BRC );
			Cur++;
		}
	else
		{
			//printf("I'm at GetP before GetN, %p, 'Cur' = %c \n", Cur, *Cur );
			value = GetN();
			//printf("I'm at GetP after GetN, %p, 'Cur' = %c \n", Cur, *Cur );
			if ( err_code != NO_ERR ) return ERR_FIND;
		}

	return value;
}

//------------------------------------------------------------------------------

double GetN ()
{
	if ( Cur == NULL        ) ERROR_( CUR_NULL );
	if ( err_code != NO_ERR ) ERROR_( err_code );
	double value = 0;

	int sign = 1;
	if ( *Cur == '+' ) { sign =  1; Cur++; }
	if ( *Cur == '-' ) { sign = -1; Cur++; }

	while ( '0' <= *Cur && *Cur <= '9' )
	{
		//printf("I'm at GetN, %p, 'Cur' = %c \n", Cur, *Cur );
		value = value*10 + *Cur++ - '0';
	}

	return sign*value;
}

//------------------------------------------------------------------------------
//WITH_DEFINE_PART_END----------------------------------------------------------
//------------------------------------------------------------------------------
#undef ERROR_

//------------------------------------------------------------------------------
void error( int const _err_code )
{
	err_code = _err_code;

	switch ( _err_code )
	{
		case CUR_NULL:    printf("=================================================\n"
							     "Error of pointer.\n"
							     " 'Cur' = NULL \n"); break;

		case MISS_BRC:    printf("=================================================\n"
							     "Expected ')'\n"
							     "     'Cur' = '%c'\n"
								 "Addr  Cur  = %p\n", *Cur, Cur ); break;
		case UNKNOW_SYMB: printf("=================================================\n"
			                     "I found undefined symbol:\n"
			                     "     'Cur' = '%c'\n"
								 "Addr  Cur  = %p\n", *Cur, Cur ); break;

		default: 	      printf("=================================================\n"
							     "Undefined error_code = %d.\n", err_code);
	}
}

