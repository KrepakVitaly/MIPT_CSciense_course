//Вариант 10
//Задача 1 A
//Таблица степеней по модулю N
//Крепак Виталий 016 гр ФРТК
#include <stdio.h>
#include <stdlib.h>



void Print_the_Table( int n );

int Powering( int a, int k );



//------------------------------------------------------------------------------

int main()
{
 	
    printf("Hello!\n"
		   "I am program for writing the table of power modulo N.\n"
           "(c)zorroxied \n"
	       "Date - " __DATE__ " " __TIME__ "\n\n");
    
    printf("Please, enter the N:\n");
    unsigned int n = 0;
    scanf( "%i", &n );
    
    printf("\nThis is the the table of power modulo N:\n");
	Print_the_Table( n );
    
    system("PAUSE");
    return 0;
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

void Print_the_Table( int n )
{

for( int k = 0 ; k < n ; k++)
	{
		for( int a = 1 ; a < n ; a++)
		{
			printf("%d ", Powering(a,k)%n );
		//printf("Powering = %d  k = %d  a = %d \n", Powering(a,k) , k , a);
		}
		printf("\n");
	}
	
return;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

int Powering( int a, int k )
{
	if ( !k ) return 1;
	
	int Bufer = a;
	
	for( int i = 1; i < k ; i++ )
	  {
		a *= Bufer;
	  }
	return a;
}

//------------------------------------------------------------------------------
