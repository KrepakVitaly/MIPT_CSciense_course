#include <cstdlib>
#include <iostream>

using namespace std;

int Qu_2( int num, int k);

int main()
{     
    printf("Solve of the task D var.1 \n");
    
    printf("Enter the N: \n");
    
    int num = 1;
    scanf("%d \n", &num );
    
    int solve = Qu_2( num, num );
    
    printf ( "%d \n", solve );
    
    system("PAUSE");
    return 0;
}

//------------------------------------------------------------------------------

int Qu_2( int n, int k)
    {
    if ( n < 0 ) return 0;
    if ( (n == 0) && (k >= 0) ) return 1;
    if ( (n >  0) && (k == 0) ) return 0;
    
    
    
    return Qu_2( n - 2*k, k - 1) + 
           Qu_2( n - k,   k - 1) +
           Qu_2( n,       k - 1);
    }
    
//------------------------------------------------------------------------------

