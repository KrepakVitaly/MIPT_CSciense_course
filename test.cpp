
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

const int number_of_elmnt = 10;
const int sizeof_elmnt    = sizeof (int);

int main (int argc, char** argv)
{
	int a[10] = {};
	int* begin_of_stack = (int*) malloc ( number_of_elmnt*sizeof_elmnt );
    free (begin_of_stack);
	for (int i = 0; i < 10; i++)
	   {	
       a[i] = i;
       *(begin_of_stack + i) = i;
	   }
	
	printf ("Dinamic a[7] = %d\n"
	        "Static  a[7] = %p\n", *begin_of_stack, a);
	system ("PAUSE");
	return 0;
}
