///  \brief          Mumba
///
///
///  \description      
///  \author		   Крепак zorroxied Виталий 016 ФРТК
///
/// double_list.h
///
///  Created on: 23.12.2010
///

#ifndef DOUBLE_LIST_H_
#define DOUBLE_LIST_H_

int const SIZE_OF_WORD = 15;

struct list_elem_t
	{
		char* data;
		void* sub_list;
		void* sub_iter;
		list_elem_t* prev;
		list_elem_t* next;
	};


struct list_t
	{
		list_elem_t* begin;
		list_elem_t* end;
	};


struct iter_t
	{
		list_t*  	  linked_list;
		list_elem_t*  cur_element;
	};

void  Delete_Element     ( iter_t* Iterator );

void  Add_Element        ( iter_t* Iterator );

void  Init_Iterator      ( iter_t* Iterator );

void  Init_List          ( list_t* List     );

void  Rewind_to_End_List ( iter_t* Iterator );

void  Iter_PP            ( iter_t* Iterator );

void  Iter_MM            ( iter_t* Iterator );

void  Rewind_List        ( iter_t* Iterator );

int   Is_List_Empty      ( iter_t* Iterator );

#endif /* DOUBLE_LIST_H_ */
