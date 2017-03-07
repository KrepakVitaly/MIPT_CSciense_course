///----------------------------------------------------------------
///----------------------------------------------------------------
///														===========
///  \brief												===========
///		Created on: 19.12.2010							===========
///  \description										===========
///  \author		   	Krepak Vitaliy,					===========
///----------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <windows.h>

char Cur_Token[100];
int  Cur_Type_Token = -1;

//----------------------------------------------------------------------------------------
//---------Constants----------------------------------------------------------------------



//----------------------------------------------------------------------------------------
//---------Functions_Prototypes-----------------------------------------------------------

double 	GetG( FILE* expr_file );

double 	GetE( FILE* expr_file );

double 	GetT( FILE* expr_file );

double 	GetS( FILE* expr_file );

double 	GetP( FILE* expr_file );

double 	GetU( FILE* expr_file );

double 	GetN( FILE* expr_file );

//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------



int main()
{
	//printf ( "Enter the expression \n" );
 //   printf ("\nResult of LA is %d.\n", !LexicalAnalysis());

  //  Close_Token_File();

   // printf("OK\n");
    char* input = "tokens.txt";
   // FILE* expr_file = fopen ( input, "r" );

  //  if ( expr_file == NULL ) { printf("I can't open '%s'", input); return -1; }


//	fscanf( expr_file, "%d %s", &Cur_Type_Token, &Cur_Token );
//	fscanf( expr_file, "%d %s", &Cur_Type_Token, &Cur_Token );


   // double value = GetG(expr_file);

//	printf("Type = %d Token = %s", Cur_Type_Token, Cur_Token);

    //printf("Result %f\n", value);
	//fclose(expr_file);
	system ( "PAUSE" );
    return 0;
}




//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
#define CUR_TOKEN_PP_    \
	fscanf( expr_file, "%d %s", &Cur_Type_Token, &Cur_Token )


double 	GetG( FILE* expr_file )
{
	CUR_TOKEN_PP_;
	printf("Type = %d Token = %s\n", Cur_Type_Token, Cur_Token);
	double value = GetE ( expr_file );
	printf("I'm at GetG\n");
	return value;
}

//-----------------------------------------------------------------------------------------


double 	GetE( FILE* expr_file )
{
	printf("I'm at GetE\n");
	printf("Type = %d Token = %s\n", Cur_Type_Token, Cur_Token);
	double value = GetT(expr_file);



		while (  *Cur_Token == '+' ||  *Cur_Token == '-' )
		{
			if ( *Cur_Token == '+' )  { CUR_TOKEN_PP_; value = value + GetT(expr_file); }
			if ( *Cur_Token == '-' )  { CUR_TOKEN_PP_; value = value - GetT(expr_file); }
		}
	printf("%f\n", value);
	return value;
}

//-----------------------------------------------------------------------------------------

double 	GetT( FILE* expr_file )
{
	printf("I'm at GetT\n");
	printf("Type = %d Token = %s\n", Cur_Type_Token, Cur_Token);
	double value = GetS(expr_file);


	while ( *Cur_Token == '*' ||  *Cur_Token == '/' )
	{
		if ( *Cur_Token == '*' ) { CUR_TOKEN_PP_; value = value*GetS(expr_file); }
		if ( *Cur_Token == '/' ) { CUR_TOKEN_PP_; value = value/GetS(expr_file); }//TODO division by zero

		//fscanf( expr_file, "%d %s", &Cur_Type_Token, Cur_Token );
	}
	printf("%f\n", value);
	return value;
}

//-----------------------------------------------------------------------------------------

double 	GetS( FILE* expr_file )
{
	printf("I'm at GetS\n");
	printf("Type = %d Token = %s\n", Cur_Type_Token, Cur_Token);
	double value = GetP(expr_file);

	while ( *Cur_Token == '^' )
	{
		CUR_TOKEN_PP_;
		value = pow(value, GetP(expr_file) );
	}
	printf("%f\n", value);
	return value;
}

//-----------------------------------------------------------------------------------------

double 	GetP( FILE* expr_file )
{

	printf("I'm at GetP\n");
	printf("Type = %d Token = %s\n", Cur_Type_Token, Cur_Token);
	double value = 0;
	int    sign  = 1;

	if ( *Cur_Token == '-' )
		{
			sign = -1;
			CUR_TOKEN_PP_;
		}

	if ( *Cur_Token == '(' )
		{
			CUR_TOKEN_PP_;
			value = sign*GetE(expr_file);
			//считывание закрывающей скобки
			CUR_TOKEN_PP_;
		}
	else
		{
			value = sign*GetU(expr_file);
		}
	printf("%f\n", value);
	return value;
}

//-----------------------------------------------------------------------------------------

double 	GetU( FILE* expr_file )
{
	printf("I'm at GetU\n");
	printf("Type = %d Token = %s\n", Cur_Type_Token, Cur_Token);
	double value = 0;

	if ( Cur_Type_Token == tkUnOper )
		{
			if ( strcmp( Cur_Token, "cos" ) ) { CUR_TOKEN_PP_; value = cos ( GetE(expr_file) ); }
			if ( strcmp( Cur_Token, "sin" ) ) { CUR_TOKEN_PP_; value = sin ( GetE(expr_file) ); }
			if ( strcmp( Cur_Token, "sqrt") ) { CUR_TOKEN_PP_; value = sqrt( GetE(expr_file) ); }
			if ( strcmp( Cur_Token, "ln"  ) ) { CUR_TOKEN_PP_; value = log ( GetE(expr_file) ); }
		}
	else
		{
			value = GetN(expr_file);
		}
	printf("%f\n", value);
	return value;
}

//-----------------------------------------------------------------------------------------

double 	GetN ( FILE* expr_file )
{
	printf("I'm at GetN\n");
	printf("Type = %d Token = %s\n", Cur_Type_Token, Cur_Token);
	double value = atoi(Cur_Token);
	CUR_TOKEN_PP_;

	printf("%f\n", value);
	return value;
}

#undef CUR_TOKEN_PP_



























