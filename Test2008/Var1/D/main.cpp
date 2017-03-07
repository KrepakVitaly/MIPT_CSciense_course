#include <cstdlib>
#include <iostream>
int const NMAX = 100;


int Qu_2( int num, int k);

int main()
{     
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

int Qu_2( int n, int k)
    {
    static int level = 0;
    static int a[NMAX][NMAX]={};
    level++;
    
    int res = 0;
    
    if (  n <  0 )              {level--; return res = 0;}
    if ( (n == 0) && (k >= 0) ) {level--; return res = 1;}
    if ( (n >  0) && (k == 0) ) {level--; return res = 0;}
    
    else res = Qu_2( n - 2*k, k - 1 ) + 
               Qu_2( n - k  , k - 1 ) +
               Qu_2( n      , k - 1 );
            
    printf("%*s Qu_2( %d , %d ) : %d \n", level, "", n, k, res);
    level--;
    return res;
    }
    
//------------------------------------------------------------------------------

