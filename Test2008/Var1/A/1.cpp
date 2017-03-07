//@ @brief Вариант 1         doxygen.org     ded32.net.ru   TX Library     TXLib.h 
///        Задача 1 A
///
/// \description Поиск наименьшего общего кратного
/// \author      Крепак Виталий 016 гр ФРТК

#include <stdio.h>
#include <stdlib.h>

int Common_Multiple( int a, int b );

//------------------------------------------------------------------------------

int main()
{
 	
    printf ("Hello! I am program for finding 'least common multiple'.\n"
            "(c)zorroxied \n"
	        "Date - " __DATE__ " " __TIME__ "\n\n");
    
    printf ("Please, enter the first number:\n");
    unsigned int a = 0;
    scanf ( "%i", &a );
    
    printf ("Please, enter the second number:\n");
    unsigned int b = 0;
    scanf ( "%i", &b );    
    
    printf ("This is 'least common multiple' for your couple of number:\n");
    int multiple = Common_Multiple ( a, b );
    printf ("%d \n", multiple );
    
    system ("PAUSE");
    return 0;
}

//------------------------------------------------------------------------------

int Common_Multiple ( int a, int b )   // divisor
{
 	int numerator = a*b;    // next version or Terminator. (c) SkyNet
	
	while ( a % b )
	{
		int t = b;
		    b = a % b;
		    a = t;
	}	
	
	return numerator/b;   
}

//------------------------------------------------------------------------------
