///  \brief          Vector_v0.1
///
///
///  \description      
///  \author		   Крепак zorroxied Виталий 016 ФРТК
///
/// vector_class.cpp
///
///  Created on: 29.03.2011
///


#include <malloc.h>
#include <iostream>


//-------------------------------------------------------------
// Описание класса Vector

struct Vector_t
{
	int  size;
	int  maxsize;
	int* data;


explicit	Vector_t ();       										 //explicit
		    Vector_t (const Vector_t& that);
		   ~Vector_t ();

};
//-------------------------------------------------------------

Vector_t::Vector_t ()
{
	this->size	  = 10;
	this->data    = static_cast < int* > (malloc( sizeof(int)*this->size ));
	this->maxsize = 10;
	for ( int i = 0; i < size; i++ )
		{
		//*(this->data + i) = 0;
		}
};

Vector_t::Vector_t (const Vector_t& that)
{
	this->data    = static_cast <int*> (malloc( sizeof(int)*that.size ));
	this->maxsize = that.maxsize;
	this->size	  = that.size;
	for ( int i = 0; i < size; i++ )
		{
		*(this->data + i) = *(that.data + i);
		}
};


Vector_t::~Vector_t ()
{
	for ( int i = 0; i < size; i++ )
		{
		*(this->data + i) = -666;
		}

	printf("\n Object has been destructed with parameters:\n"
		   "	Null elmnt = %d \n"
	       "	Null addr = %p \n", *(this->data), (this->data));

	free(this->data);

//--------toxic block----------------
	{
	this->data = 0;
	this->maxsize = -666;
	this->size    = -666;
	}
//-----------------------------------

	printf("	Null addr has been poisoned by value = %p \n"
	       "	Max size  has been poisoned by value = %d \n"
	       "	Null addr has been poisoned by value = %d \n\n", (this->data),
	       	   	   	   	   	   	   	   	   	   	   	   	   	   	 (this->maxsize),
	       	   	   	   	   	   	   	   	   	   	   	   	   	   	 (this->size));
}



int  Printf_Vector(Vector_t v)
{
	printf("Cur Poison null addr = %p \n", (v.data));

	for ( int i = 0; i < v.maxsize; i++ )
		{
		printf("%d ", *(v.data + i) );
		}

	printf("\n");
	return 0;
};

