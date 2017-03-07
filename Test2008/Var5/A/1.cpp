//Вариант 5 
//Задача 1 A
//Сумма цифр неотрицательного числа N
//Крепак Виталий 016 гр ФРТК
#include <stdio.h>
#include <stdlib.h>

int Sum_Digits( int a );

//------------------------------------------------------------------------------

int main()
{
 	
    printf("Hello!\n"
		   "I am program for finding the sum of digits of the natural number.\n"
           "(c)zorroxied \n"
	       "Date - " __DATE__ " " __TIME__ "\n\n");
    
	printf( "Enter the number, please:\n" );
	int a = 0;
	scanf( "%d", &a );
	
	int sum = Sum_Digits( a );
	
	printf( "The sum of digits: \n%d \n\n", sum );
    
    system("PAUSE");
    return 0;
}

//------------------------------------------------------------------------------

int Sum_Digits( int a )
{
	int sum = 0;
	
	while ( a%10 )
	{
		sum += a % 10;
		a /= 10;
	//	printf("Sum = %d a = %d \n", sum, a);
	}

return sum;
}

//------------------------------------------------------------------------------
