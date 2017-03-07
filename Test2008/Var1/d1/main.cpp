#include <cstdlib>
#include <iostream>

//-----Constants---------

int const NMAX = 100;

//-----------------------
//--Global_Variables----- 

int cache[100][100] = {};

//------------------------
//Functions_Prototypes----

int Qu_2( int num, int k);

void Init_Global_Cache();

//------------------------



int main()
{     
    Init_Global_Cache();
    
	printf("Solve of the task D var.1 \n");
    
    printf("Enter the N: \n");
    
    int num = 1;
    scanf("%d", &num );
    
    int solve = Qu_2( num, num );
    
    printf ( "%d \n", solve );
    
    system("PAUSE");
    return 0;
}



//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

int Qu_2( int n, int k)
    {
//    static int level = 0;
//    static int a[NMAX][NMAX]={};
//    level++;
    
    int res = 0;
    
    if (  n <  0 )              {/*level--;*/ return res = 0;}
    if ( (n == 0) && (k >= 0) ) {/*level--;*/ return res = 1;}
    if ( (n >  0) && (k == 0) ) {/*level--;*/ return res = 0;}
    
    if ( cache[ n - 1 ][ k - 1 ] == -1 )
				{
	            res = Qu_2( n - 2*k, k - 1 ) + 
                      Qu_2( n - k  , k - 1 ) +
                      Qu_2( n      , k - 1 );
                      
                cache[ n - 1 ][ k - 1 ] = res; }  
				    
    else        res = cache[ n - 1 ][ k - 1 ];        
            
            
//    printf("%*s Qu_2( %d , %d ) : %d \n", level, "", n, k, res);
//    level--;
    return res;
    }
    
//------------------------------------------------------------------------------

void Init_Global_Cache()
	{
	for ( int x = 0 ; x < 100 ; x++ )
    	for ( int y = 0 ; y < 100 ; y++ )    cache[x][y] = -1;	
	}

//------------------------------------------------------------------------------
