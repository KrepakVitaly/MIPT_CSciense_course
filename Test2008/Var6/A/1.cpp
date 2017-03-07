//Вариант 6
//Задача 1 A
//Заполнение матрицы по спирали
//Крепак Виталий 016 гр ФРТК
#include <stdio.h>
#include <stdlib.h>

int const MAX_SIZE = 100;

void Fill_the_Matrix( int Matrix[0], int n, int m );



//------------------------------------------------------------------------------

int main()
{
 	
    printf("Hello!\n"
		   "I am program for filling the matrix by spiral.\n"
           "(c)zorroxied \n"
	       "Date - " __DATE__ " " __TIME__ "\n\n");
    
	printf( "Enter the number of column (n), please:\n" );
	int column = 0;
	scanf( "%d", &column );
	
	printf( "Enter the number of row (m), please:\n" );
	int row = 0;
	scanf( "%d", &row );
	
	int Matrix[MAX_SIZE][MAX_SIZE] = {};
	
	Fill_the_Matrix( Matrix[0], column, row );
	
	printf( "\nThe sum of digits:\n");
    
    
for(int x = 0; x < row ; x++ )
	{
	for(int y = 0; y < column ; y++)
		{
		printf("%d ", Matrix[x][y]);
		}
		
	printf("\n");
	}
    
    system("PAUSE");
    return 0;
}

//------------------------------------------------------------------------------

void Fill_the_Matrix(int Matrix[0], int column, int row )
{
	int i = 0;
	for(int y = 0; y < column ; y++)
	{
	  for(int x = 0; x < row ; x++ )	
		{
		i++;
//		printf("Matrix-n %d    i = %d\n", y + 100*x, i );
		Matrix[y + 100*x] = i;
		}
	}
	
	
//	printf( "%d", Matrix[1+MAX_SIZE] );
	return;
}

//------------------------------------------------------------------------------
