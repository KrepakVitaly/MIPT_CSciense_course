//Вариант 5 
//Задача 1 D
//Генерация разложений
//Крепак Виталий 016 гр ФРТК

#include <cstdlib>
#include <iostream>

//-----Constants-----------

int const NMAX = 30;

//-------------------------
//--Global_Variables------- 

int cache[NMAX] = {};

//-------------------------
//-Functions_Prototypes----

void Qu_2( int level );

void Init_Global_Cache();

//-------------------------



int main()
{     
    Init_Global_Cache();
    
	printf("The generation of decomposition natural N:\n");
    
    printf("Enter the N: \n");
    
    scanf("%d", &cache[0] );
    
	Qu_2( 0 );
    
/*		for( int x = 0; x < NMAX ; x++ )
			{
			if ( cache[x] != -1 )
						 printf("cache[%d] = %d \n",x, cache[x]);
			}*/
    
    system("PAUSE");
    return 0;
}



//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

void Qu_2( int level )
    {
	int n = cache[ level ];	
	int bufer_for_n = n;
		
	int print_result = 1;	
//	printf("Input value = %d Recursion Level = %d \n", n, level );
	
/*	if ( n == 1 ) 
		{
			    
		return;
		}*/
	
	for( int i = 1 ; i < n/2 + 1 ; i++ )
		{	
		cache[ level ]     = i;
		cache[ level + 1 ] = n - i;
		Qu_2 ( level + 1 );
			
		for( int i = 0 ; i < level + 1 ; i++ ) 
				if ( cache[i] > cache [i + 1] ) print_result = 0;
		
		
		if ( print_result ) 
		    {
			for( int i = level + 1 ; i >= 0 ; i-- ) printf("+%d ", cache[i] );
		    printf("\n");
			}	
				
		cache[ level ] = bufer_for_n;
		} 
    }
    
//------------------------------------------------------------------------------

void Init_Global_Cache()
	{
	  for ( int x = 0 ; x < NMAX ; x++ )
  			cache[x] = -1;	
	}

//------------------------------------------------------------------------------
