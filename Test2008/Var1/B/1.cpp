//Вариант 1
//Задача B
//Удаление повторяющихся чисел
//Крепак Виталий 016 гр ФРТК

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#pragma please
#include <windows.h>
#else
#error Oohh... you can't do it in Linux... (((
#endif

#ifdef MY_SIDE
#define OUT        printf
#else
#define OUT if (0) printf
#endif

const int NO_REPEATS      =   -1;
const int MAX_SIZE        = 1001;
const int REPEAT_DETECTED =   -1;
const int INIT_VALUE 	  =   -2;
const int ONE_IN		  =   -1;

void Init_Array ( int Numbers[] );

void Write_Numbers ( int Numbers[] , int amount );

int Entering_the_Numbers ( int Numbers[], int n );


//------------------------------------------------------------------------------


int main ()
{
 	int Numbers[MAX_SIZE] = {};
 	
 	Init_Array ( Numbers );
 	
    OUT   ("Hello!\n"
		   "I am program for deleting the repeating numbers.\n"
           " (c)zorroxied \n"
	       "Date - " __DATE__ " " __TIME__ "\n\n");
    
    printf ("Please, enter the amount, N:\n");
    int n = 0;
	scanf ( "%i", &n );
    
    printf ("Please, enter the numbers over gaps:\n"); 
    
    
    int max_n = Entering_the_Numbers ( Numbers, n );
    
    
    printf ("\nProcess progress:\n\n");

	for (int i = 0 ; i < 20 ; i++ ) {Sleep (100); printf ("#");};
	printf ("\n\nCongratulations!\n");
	
	
 
    if (max_n != NO_REPEATS)    Write_Numbers ( Numbers , max_n ); 
	             else           printf ("%d\n", NO_REPEATS);

    system ("PAUSE");
    return 0;
}








//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

void Init_Array ( int Numbers[] )
{
    for ( int i = 0; i <= MAX_SIZE ; i++ )
	{
		Numbers[i] = INIT_VALUE;
	}	
}

//------------------------------------------------------------------------------

void Write_Numbers ( int Numbers[] , int amount )
{
	printf ("\nYeah! I made it!\n"
		   "The numbers which repeats:\n\n");
		   
	for ( int i = 0; i <= amount ; i++ )
		{
		if ( ( Numbers[i] != -1 ) && 
		     ( Numbers[i] != -2 )  )  printf ( "%i ", Numbers[i] );
		}
	printf ("\n\n");
}

//------------------------------------------------------------------------------

int Entering_the_Numbers ( int Numbers[], int n )
{
	int buf_n        =   0,
		repeat_check =  NO_REPEATS,   
	    max_n        =  -1;
	
	for ( int i = 0; i < n ; i++ )
		{
		scanf ( " %i", &buf_n );
		
		if ( Numbers[buf_n] == buf_n ) repeat_check = REPEAT_DETECTED;
		
				
		if ( Numbers[buf_n] == ONE_IN ) { repeat_check   = REPEAT_DETECTED;
		                                  Numbers[buf_n] = buf_n;          }
		
		
		if ( Numbers[buf_n] == -2     )   Numbers[buf_n] = ONE_IN;

	
	//   Numbers[buf_n] = buf_n;
	    if ( max_n < Numbers[buf_n] ) max_n = Numbers[buf_n];
		}
		
	if ( !repeat_check ) return NO_REPEATS;
	
return max_n;    
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
