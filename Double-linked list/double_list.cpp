///  \brief           Двусвязный список
///
///  \description      doubly-linked list
///  \author		    Крепак zorroxied Виталий 016 ФРТК
///

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <windows.h>
#include <assert.h>



//------------------------------------------------------------------------------
//------Constants---------------------------------------------------------------

int const NONCONST = 0;

//------------------------------------------------------------------------------
//------My_Types----------------------------------------------------------------

/*! \struct list_elem_t

    \brief Элемент списка
	       структура является элементом списка
*/
struct list_elem_t
	{
		double data;  /*!< Содержимое элемента списка */

		list_elem_t* Prev;  /*!< Указатель на предыдущий элемент списка
							     если такового не существует, то NULL */
							     
		list_elem_t* Next;  /*!< Указатель на следующий элемент списка 
								 если такового не существует, то NULL */
	};
	

/*! \struct list_t

    \brief Спискок.
           Содержит в себе указатели на начальный и конечный элементы.
           Внимание! После объявления необходимо инициализировать
*/
struct list_t
	{
		list_elem_t* Begin;  /*!< Указатель на начало списка
							     если такового не существует, то NULL */
							     
		list_elem_t* End;    /*!< Указатель на конец списка
							     если такового не существует, то NULL */
	};

	
/*! \struct iter_t

    \brief Итератор.
           Приспособление для ориентирования по списку.
           Содержит в себе указатель на список, по которому "ходит";
           а также указатель на текущий просматриваемый элемент
           Внимание! После объявления необходимо инициализировать!!!!
*/
struct iter_t
	{
		list_t*  	  Linked_List; /*!< Указатель на "свой" список
							            если такового не существует, то NULL */
							     
		list_elem_t*  Cur_Element; /*!< Указатель на текущий элемент
							            если такового не существует, то NULL */
	};
	
//------------------------------------------------------------------------------
//---------Functions_Prototypes-------------------------------------------------

void  Delete_Element     ( iter_t* Iterator );

void  Add_Element        ( iter_t* Iterator );

void  Init_Iterator      ( iter_t* Iterator );

void  Init_List          ( list_t* List     );

void  Rewind_to_End_List ( iter_t* Iterator );

void  Iter_PP            ( iter_t* Iterator );

void  Iter_MM            ( iter_t* Iterator );

void  Rewind_List        ( iter_t* Iterator );

int   Is_List_Empty      ( iter_t* Iterator );

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

int main()
{
	list_t My_List;
	Init_List ( &My_List );
	
	iter_t My_Iterator;
	Init_Iterator ( &My_Iterator ); 
	
	My_Iterator.Linked_List = &My_List;
	
	
	Add_Element ( &My_Iterator );
	My_Iterator.Cur_Element->data = 123.6;
 	printf("%f\n", My_Iterator.Cur_Element->data );
	
	
	Add_Element ( &My_Iterator );
	My_Iterator.Cur_Element->data = 123.2;
 	printf("%f\n", My_Iterator.Cur_Element->data );
	
	
	Add_Element ( &My_Iterator ); 
	My_Iterator.Cur_Element->data = 123.1;
 	printf("%f\n", My_Iterator.Cur_Element->data );


    Rewind_List ( &My_Iterator );		
 	printf("%f\n", My_Iterator.Cur_Element->data );
 	
 	Delete_Element( &My_Iterator );
	Delete_Element( &My_Iterator );
	Delete_Element( &My_Iterator );
 	
 	
	system ( "PAUSE" );
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*!
    \brief Delete_Element

    Функция, удаляющая текущий элемент из списка.
    Внимание! Если осуществлена попытка удалить элемент из пустого списка
    (элемент, указатель на который NULL), то assert.
    
*/
 
void  Delete_Element ( iter_t* Iterator )
{
//Нет элементов в списке
	if ( Iterator->Cur_Element == NULL ) 
				printf("-----------------------------------------------------\n"
					   "You tried to delete element from empty list. Error.\n");
	assert( !(Iterator->Cur_Element == NULL) );
	

//Если элемент единственный в списке
	if ( Iterator->Cur_Element->Prev == NULL  &&  
		 Iterator->Cur_Element->Next == NULL     ) 
		{
		//	printf("That's all. I'm died.\n");
			
			Iterator->Linked_List->Begin = NULL;
			Iterator->Linked_List->End   = NULL;
			
			free ( Iterator->Cur_Element );
			Iterator->Cur_Element = NULL;
			
			return;
		}
	
//Если элемент первый в списке
	if ( Iterator->Cur_Element->Prev == NULL  &&  
	     Iterator->Cur_Element->Next != NULL     ) 
		{
		//	printf("I felt a headache.\n");
			
			Iterator->Linked_List->Begin      = Iterator->Cur_Element->Next;
			Iterator->Cur_Element->Next->Prev = NULL;
			
			free ( Iterator->Cur_Element );
			Iterator->Cur_Element = Iterator->Linked_List->Begin;
			
			return;
		}
		
//Если элемент последний в списке
	if ( Iterator->Cur_Element->Prev != NULL  &&  Iterator->Cur_Element->Next == NULL ) 
		{
		//	printf("I've hurt my legs.\n");
			list_elem_t* temp = Iterator->Cur_Element->Prev;
			
			Iterator->Linked_List->End        = Iterator->Cur_Element->Prev;
			Iterator->Cur_Element->Prev->Next = NULL;
			
			free(Iterator->Cur_Element);
			
			Iterator->Cur_Element = temp;
			return;
		}
	
//Штатная ситуация	
//-- Для предыдущего, следующий теперь следующий после текущего		
	 Iterator->Cur_Element->Prev->Next = Iterator->Cur_Element->Next;
		
//-- Для следующего, предыдущий теперь предыдущий перед текущим	
	 Iterator->Cur_Element->Next->Prev = Iterator->Cur_Element->Prev; 
	
	
	free(Iterator->Cur_Element);
	
	return;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*!
    \brief Add_Element

    Функция, добавляющая новый элемент в список.
    
    Внимание! Функция работает только с концом списка!
    
*/
void  Add_Element ( iter_t* Iterator )
{
	list_elem_t* New_Element_Adr = (list_elem_t*) malloc ( sizeof(list_elem_t) );
	
	if ( Iterator->Cur_Element != NULL ) 
				Iterator->Cur_Element->Next  = New_Element_Adr;
				
	if ( Iterator->Cur_Element == NULL ) 
				Iterator->Linked_List->Begin = New_Element_Adr;

	New_Element_Adr->Prev = Iterator->Cur_Element;
	New_Element_Adr->Next = NULL;
	
	Iterator->Linked_List->End = New_Element_Adr;
	Iterator->Cur_Element      = New_Element_Adr;
	
	return;
}

//------------------------------------------------------------------------------
/*!
    \brief Init_Iterator

    Инициализация типа iter_t NULL'ами
    
*/
void  Init_Iterator ( iter_t* Iterator )
{
	Iterator->Linked_List = NULL;
	Iterator->Cur_Element = NULL;
	
	return;
}

//------------------------------------------------------------------------------
/*!
    \brief Init_List

    Инициализация типа list_t NULL'ами
*/
void  Init_List ( list_t* List )
{
	List->Begin = NULL;
	List->End   = NULL;
	
	return;
}

//------------------------------------------------------------------------------
/*!
    \brief Rewind_List

    Переход к началу списка
*/
void Rewind_List ( iter_t* Iterator )
{
	Iterator->Cur_Element = Iterator->Linked_List->Begin;
	return;
}

//------------------------------------------------------------------------------

void Iter_MM ( iter_t* Iterator )
{
	if ( Iterator->Cur_Element->Prev == NULL ) 
			printf("-----------------------------------------------------\n"
			       "You tried to decrement list below the beginnig. Error.\n");
			
	assert( !(Iterator->Cur_Element->Prev == NULL) );
	
	Iterator->Cur_Element = Iterator->Cur_Element->Prev;
	return;
}

//------------------------------------------------------------------------------

void Iter_PP ( iter_t* Iterator )
{
	if ( Iterator->Cur_Element->Next == NULL ) 
			printf("-----------------------------------------------------\n"
			       "You tried to increment list over the end. Error.\n");
	assert( !(Iterator->Cur_Element->Next == NULL) );
	
	Iterator->Cur_Element = Iterator->Cur_Element->Next;
	return;
}

//------------------------------------------------------------------------------

void Rewind_to_End_List ( iter_t* Iterator )
{
	//if ( Iterator->Cur_Element->Next ) return;
	
	Iterator->Cur_Element = Iterator->Linked_List->End;
	return;
}

//------------------------------------------------------------------------------

int  Is_List_Empty ( iter_t* Iterator )
{

	if ( Iterator->linked_list->begin == NULL  Iterator->linked_list->end )
	    return 1;
	return 0;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------









