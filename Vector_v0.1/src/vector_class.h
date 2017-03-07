///  \brief          Vector_v0.1
///
///
///  \description      
///  \author		   Крепак zorroxied Виталий 016 ФРТК
///
/// vector_class.h
///
///  Created on: 29.03.2011
///

#ifndef VECTOR_CLASS_H_
#define VECTOR_CLASS_H_

struct Vector_t
{
	int  size;
	int  maxsize;
	int* data;

	int Dump();

	explicit Vector_t ();       										 //explicit
	         Vector_t (const Vector_t& that);
	         ~Vector_t ();
private:
	bool OK();
};

int  Printf_Vector(Vector_t v);

#endif /* VECTOR_CLASS_H_ */
