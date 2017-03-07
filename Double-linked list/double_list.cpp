///  \brief           ���������� ������
///
///  \description      doubly-linked list
///  \author		    ������ zorroxied ������� 016 ����
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

    \brief ������� ������
	       ��������� �������� ��������� ������
*/
struct list_elem_t
	{
		double data;  /*!< ���������� �������� ������ */

		list_elem_t* Prev;  /*!< ��������� �� ���������� ������� ������
							     ���� �������� �� ����������, �� NULL */
							     
		list_elem_t* Next;  /*!< ��������� �� ��������� ������� ������ 
								 ���� �������� �� ����������, �� NULL */
	};
	

/*! \struct list_t

    \brief �������.
           �������� � ���� ��������� �� ��������� � �������� ��������.
           ��������! ����� ���������� ���������� ����������������
*/
struct list_t
	{
		list_elem_t* Begin;  /*!< ��������� �� ������ ������
							     ���� �������� �� ����������, �� NULL */
							     
		list_elem_t* End;    /*!< ��������� �� ����� ������
							     ���� �������� �� ����������, �� NULL */
	};

	
/*! \struct iter_t

    \brief ��������.
           �������������� ��� �������������� �� ������.
           �������� � ���� ��������� �� ������, �� �������� "�����";
           � ����� ��������� �� ������� ��������������� �������
           ��������! ����� ���������� ���������� ����������������!!!!
*/
struct iter_t
	{
		list_t*  	  Linked_List; /*!< ��������� �� "����" ������
							            ���� �������� �� ����������, �� NULL */
							     
		list_elem_t*  Cur_Element; /*!< ��������� �� ������� �������
							            ���� �������� �� ����������, �� NULL */
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

    �������, ��������� ������� ������� �� ������.
    ��������! ���� ������������ ������� ������� ������� �� ������� ������
    (�������, ��������� �� ������� NULL), �� assert.
    
*/
 
void  Delete_Element ( iter_t* Iterator )
{
//��� ��������� � ������
	if ( Iterator->Cur_Element == NULL ) 
				printf("-----------------------------------------------------\n"
					   "You tried to delete element from empty list. Error.\n");
	assert( !(Iterator->Cur_Element == NULL) );
	

//���� ������� ������������ � ������
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
	
//���� ������� ������ � ������
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
		
//���� ������� ��������� � ������
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
	
//������� ��������	
//-- ��� �����������, ��������� ������ ��������� ����� ��������		
	 Iterator->Cur_Element->Prev->Next = Iterator->Cur_Element->Next;
		
//-- ��� ����������, ���������� ������ ���������� ����� �������	
	 Iterator->Cur_Element->Next->Prev = Iterator->Cur_Element->Prev; 
	
	
	free(Iterator->Cur_Element);
	
	return;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*!
    \brief Add_Element

    �������, ����������� ����� ������� � ������.
    
    ��������! ������� �������� ������ � ������ ������!
    
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

    ������������� ���� iter_t NULL'���
    
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

    ������������� ���� list_t NULL'���
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

    ������� � ������ ������
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









