//Вариант 3 
//Задача 1 A
//НОД трех чисел
//Крепак Виталий 016 гр ФРТК
#include <stdio.h>
#include <stdlib.h>

int Common_Divisor( int a, int b, int c );

//------------------------------------------------------------------------------

int main()
{
 	
    printf("Hello!\n"
		   "I am program for finding the 'greatest common divisor' for three numbers.\n"
           "(c)zorroxied \n"
	       "Date - " __DATE__ " " __TIME__ "\n\n");
    
    printf("Please, enter the first number:\n");
    unsigned int a = 0;
    scanf( "%i", &a );
    
    printf("Please, enter the second number:\n");
    unsigned int b = 0;
    scanf( "%i", &b );    
    
    printf("Please, enter the third number:\n");
    unsigned int c = 0;
    scanf( "%i", &c );  
    
    printf("\n This is the 'greatest common divisor' for your couple of number:\n");
    int divisor = Common_Divisor( a, b, c );
    printf("%d \n\n", divisor );
    
    system("PAUSE");
    return 0;
}

//------------------------------------------------------------------------------
//НОД(a,b,c) = НОД(НОД(a,b),c)

int Common_Divisor( int a, int b, int c )
{
 	int bufer = 0;
 	int numerator = a*b;
	
	while ( a % b )
	{
		bufer = b;
		b = a % b;
//	printf(" OK \n");
	}	
	
	while ( b % c )
	{
		bufer = c;
		c = b % c;
		b = bufer;
	}
	
return c;
}

//------------------------------------------------------------------------------
