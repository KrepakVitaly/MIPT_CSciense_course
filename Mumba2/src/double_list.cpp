///  \brief           ���������� ������
///
///  \description      doubly-linked list
///  \author		    ������ zorroxied ������� 016 ����
///

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <assert.h>



//------------------------------------------------------------------------------
//------Constants---------------------------------------------------------------

int const NONCONST = 0;

//------------------------------------------------------------------------------
//------My_Types----------------------------------------------------------------


struct list_elem_t
	{
		double data;  /*!< ���������� �������� ������ */

		list_elem_t* prev;  /*!< ��������� �� ���������� ������� ������
							     ���� �������� �� ����������, �� NULL */
							     
		list_elem_t* next;  /*!< ��������� �� ��������� ������� ������
								 ���� �������� �� ����������, �� NULL */
	};
	

/*! \struct list_t

    \brief �������.
           �������� � ���� ��������� �� ��������� � �������� ��������.
           ��������! ����� ���������� ���������� ����������������
*/
struct list_t
	{
		list_elem_t* begin;  /*!< ��������� �� ������ ������
							     ���� �������� �� ����������, �� NULL */
							     
		list_elem_t* end;    /*!< ��������� �� ����� ������
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
		list_t*  	  linked_list; /*!< ��������� �� "����" ������
							            ���� �������� �� ����������, �� NULL */
							     
		list_elem_t*  cur_element; /*!< ��������� �� ������� �������
							            ���� �������� �� ����������, �� NULL */
	};
	
//------------------------------------------------------------------------------
//---------Functions_Prototypes-------------------------------------------------

void  Delete_Element     ( iter_t* Iterator );

void  Add_Element        ( iter_t* Iterator );

void  Init_Iterator      ( iter_t* Iterator );

void  Init_List          ( list_t* List     );

void  Rewind_to_end_List ( iter_t* Iterator );

void  Iter_PP            ( iter_t* Iterator );

void  Iter_MM            ( iter_t* Iterator );

void  Rewind_List        ( iter_t* Iterator );

int   Filling_Test       ( iter_t* Iterator );

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
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
	if ( Iterator->cur_element == NULL )
				printf("-----------------------------------------------------\n"
					   "You tried to delete element from empty list. Error.\n");
	assert( !(Iterator->cur_element == NULL) );
	

//���� ������� ������������ � ������
	if ( Iterator->cur_element->prev == NULL  &&
		 Iterator->cur_element->next == NULL     )
		{
		//	printf("That's all. I'm died.\n");
			
			Iterator->linked_list->begin = NULL;
			Iterator->linked_list->end   = NULL;
			
			free ( Iterator->cur_element );
			Iterator->cur_element = NULL;
			
			return;
		}
	
//���� ������� ������ � ������
	if ( Iterator->cur_element->prev == NULL  &&
	     Iterator->cur_element->next != NULL     )
		{
		//	printf("I felt a headache.\n");
			
			Iterator->linked_list->begin      = Iterator->cur_element->next;
			Iterator->cur_element->next->prev = NULL;
			
			free ( Iterator->cur_element );
			Iterator->cur_element = Iterator->linked_list->begin;
			
			return;
		}
		
//���� ������� ��������� � ������
	if ( Iterator->cur_element->prev != NULL  &&  Iterator->cur_element->next == NULL )
		{
		//	printf("I've hurt my legs.\n");
			list_elem_t* temp = Iterator->cur_element->prev;
			
			Iterator->linked_list->end        = Iterator->cur_element->prev;
			Iterator->cur_element->prev->next = NULL;
			
			free(Iterator->cur_element);
			
			Iterator->cur_element = temp;
			return;
		}
	
//������� ��������	
//-- ��� �����������, ��������� ������ ��������� ����� ��������		
	 Iterator->cur_element->prev->next = Iterator->cur_element->next;
		
//-- ��� ����������, ���������� ������ ���������� ����� �������	
	 Iterator->cur_element->next->prev = Iterator->cur_element->prev;
	
	
	free(Iterator->cur_element);
	
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
	
	if ( Iterator->cur_element != NULL )
				Iterator->cur_element->next  = New_Element_Adr;
				
	if ( Iterator->cur_element == NULL )
				Iterator->linked_list->begin = New_Element_Adr;

	New_Element_Adr->prev = Iterator->cur_element;
	New_Element_Adr->next = NULL;
	
	Iterator->linked_list->end = New_Element_Adr;
	Iterator->cur_element      = New_Element_Adr;
	
	return;
}

//------------------------------------------------------------------------------
/*!
    \brief Init_Iterator

    ������������� ���� iter_t NULL'���
    
*/
void  Init_Iterator ( iter_t* Iterator )
{
	Iterator->linked_list = NULL;
	Iterator->cur_element = NULL;
	
	return;
}

//------------------------------------------------------------------------------
/*!
    \brief Init_List

    ������������� ���� list_t NULL'���
*/
void  Init_List ( list_t* List )
{
	List->begin = NULL;
	List->end   = NULL;
	
	return;
}

//------------------------------------------------------------------------------
/*!
    \brief Rewind_List

    ������� � ������ ������
*/
void Rewind_List ( iter_t* Iterator )
{
	Iterator->cur_element = Iterator->linked_list->begin;
	return;
}

//------------------------------------------------------------------------------

void Iter_MM ( iter_t* Iterator )
{
	if ( Iterator->cur_element->prev == NULL )
			printf("-----------------------------------------------------\n"
			       "You tried to decrement list below the beginnig. Error.\n");
			
	assert( !(Iterator->cur_element->prev == NULL) );
	
	Iterator->cur_element = Iterator->cur_element->prev;
	return;
}

//------------------------------------------------------------------------------

void Iter_PP ( iter_t* Iterator )
{
	if ( Iterator->cur_element->next == NULL )
			printf("-----------------------------------------------------\n"
			       "You tried to increment list over the end. Error.\n");
	assert( !(Iterator->cur_element->next == NULL) );
	
	Iterator->cur_element = Iterator->cur_element->next;
	return;
}

//------------------------------------------------------------------------------

void Rewind_to_end_List ( iter_t* Iterator )
{
	//if ( Iterator->cur_element->next ) return;
	
	Iterator->cur_element = Iterator->linked_list->end;
	return;
}

//------------------------------------------------------------------------------

int  Is_List_Empty ( iter_t* Iterator )
{
	
	if ( Iterator->linked_list->begin == Iterator->linked_list->end )
	return 1;
	return 0;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------







