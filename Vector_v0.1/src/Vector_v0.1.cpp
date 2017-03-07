//============================================================================
// Name        : Vector_v0.1.cpp
// Author      : Крепак zorroxied Виталий ФРТК 016
// Version     :
// Copyright   : 
// Description : Vector -- Self-Exapansible Array
//============================================================================

#include <iostream>
#include "vector_class.h"
#include <malloc.h>
#include <windows.h>




using namespace std;

int main()
{
	Vector_t vect1, vect2;

	for ( int i = 0; i < vect1.size; i++ )
		{
		*(vect1.data + i) = 12;
		}

	Printf_Vector( vect1 );
	printf("Cur Poison data addr = %d \n", (vect1.data));
	Printf_Vector( vect1 );

	system ( "PAUSE" );
	return 0;
}
