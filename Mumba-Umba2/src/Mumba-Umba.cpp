///  \brief
///
///  \description
///  \author		     репак zorroxied ¬италий 016 ‘–“ 

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>

#include "double_list.h"

//------------------------------------------------------------------------------
//------Constants---------------------------------------------------------------

int const NUMBER_WORDS = 400;

//------------------------------------------------------------------------------
//---------Functions_Prototypes-------------------------------------------------

void 	Loading_Dictionary		 ( FILE* input , list_t* list_origin, iter_t* iter_origin );

void 	Printing_New_Dictionary  ( FILE* output, list_t* list_origin, iter_t* iter_origin );


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


int main()
{
	char input_label []  = "input.txt";
	char output_label[]  = "output.txt";


	FILE* input  = fopen ( input_label , "r" );
	FILE* output = fopen ( output_label, "w+" );

//-------------- TODO -- closing file
	if ( output == NULL ) { printf("Output file not opened.\n"); fclose(input); return -1; }
	if ( input  == NULL ) { printf("Input  file not opened.\n"); fclose(output); return -1; }


//-------List initialization
	list_t origin_list;
	Init_List( &origin_list );

	iter_t iter_origin;
	Init_Iterator ( &iter_origin );
	iter_origin.linked_list = &origin_list;

//------------------------------


//---------------_Target_of_work_---------------
	Loading_Dictionary      ( input,  &origin_list, &iter_origin );

	Printing_New_Dictionary ( output, &origin_list, &iter_origin );
//----------------------------------------------

	system ("PAUSE");
	fclose(input);
	fclose(output);
	return 0;
}



//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

void Loading_Dictionary		 ( FILE* input , list_t* list_origin, iter_t* iter_origin )
{
	int size;

	fseek(input, 0, SEEK_END);
	size = ftell(input);
	fseek(input, 0, SEEK_SET);

	void* container = malloc(sizeof(char)*size);

	fread ( container, sizeof(char)*(size), 1, input );
	*((char*)container+sizeof(char)*(size) - 2) = '\0';

	printf( "%s\n", (char*)container );

	char* cur_char      = (char*) container;
	char* cur_word      = (char*) container;
	char* origin_word   = (char*) container;
	char* last_word     = (char*) container;

	char* origin_words[400] = {};
	char* mumbus_words[400] = {};

	int   i = 0;

	int   word_written  = 0;

	while ( *cur_char != '\0' )
	{
		//-------------------------------------------------
		//
		if ( *cur_char == ':')
			{
			*cur_char = '\0';
			origin_word = cur_word;
			printf("Origin word   = %s  Last word   = %s\n", origin_word, cur_word);
			cur_char++;
			last_word = cur_word;
			cur_word = cur_char;

			}
		//-------------------------------------------------

		//-------------------------------------------------
		//---
		if ( *cur_char == ',' || *cur_char == '\n'  )
			{
			*cur_char = '\0';
			cur_char++;
			printf("Origin word   = %s  Last word   = %s\n", origin_word, cur_word);
			last_word = cur_word;
			cur_word = cur_char;
			}

		if ( *(cur_char + 1) == '\0' )
			{
			printf("Origin word   = %s  Last word   = %s\n", origin_word, cur_word);
			last_word = cur_word;
			}
		//--------------------------------------------------
		//≈сли последнее считанное слово - не "английское" и список - пустой,
		//то создаем элемент списка, в него пишем слово
		//также создаем св€занный с ним подсписок и в него пишем текущее "английское" слово
		if ( last_word != origin_word  && Is_List_Empty(iter_origin))
		{
			Add_Element(iter_origin);
			iter_origin->cur_element->data = last_word;

			iter_origin->cur_element->sub_list = malloc (sizeof(list_t));
			iter_origin->cur_element->sub_iter = malloc (sizeof(iter_t));
			Init_List	  ( (list_t*)iter_origin->cur_element->sub_list );
			Init_Iterator ( (iter_t*)iter_origin->cur_element->sub_iter );
			((iter_t*)iter_origin->cur_element->sub_iter)->linked_list = (list_t*)iter_origin->cur_element->sub_list;
			//printf("In sublist = %s\n",origin_word);

			Add_Element( (iter_t*)iter_origin->cur_element->sub_iter );
			((iter_t*)iter_origin->cur_element->sub_iter)->cur_element->data = origin_word;

			printf("In list = %s, In sublist = %s\n",iter_origin->cur_element->data, ((iter_t*)iter_origin->cur_element->sub_iter)->cur_element->data);
		}

		//≈сли последнее считанное слово - не "английское" и список - не пустой,
		//то провер€ем, не записано ли уже у нас считанное слово, если записано,
		//то пишем в его подсписок текущее "английское" слово
		//иначе -- создаем элемент списка, в него пишем слово,
		//также создаем св€занный с ним подсписок и в него пишем текущее "английское" слово
		if ( last_word != origin_word  && !Is_List_Empty(iter_origin))
		{
			Rewind_List(iter_origin);

			while ( iter_origin->cur_element->next != NULL )
				{
				if ( strcmp( iter_origin->cur_element->data, last_word) == 0 ) //если нашли
					{
					word_written = 1;

					Rewind_to_end_List( (iter_t*)iter_origin->cur_element->sub_iter );
					Add_Element( (iter_t*)iter_origin->cur_element->sub_iter );
					((iter_t*)iter_origin->cur_element->sub_iter)->cur_element->data = origin_word;
					printf("In sublist = %s\n",((iter_t*)iter_origin->cur_element->sub_iter)->cur_element->data);
					break;
					}
				Iter_PP(iter_origin);
				}


				if ( iter_origin->cur_element->next == NULL &&
				 strcmp( iter_origin->cur_element->data, last_word ) == 0 )
				{
				word_written = 1;

				Add_Element( (iter_t*)iter_origin->cur_element->sub_iter );
				((iter_t*)iter_origin->cur_element->sub_iter)->cur_element->data = origin_word;
				printf("In sublist = %s\n",((iter_t*)iter_origin->cur_element->sub_iter)->cur_element->data);
				}

				/*if (word_written == 0) //если не нашли
				{
				Add_Element(iter_origin);
				iter_origin->cur_element->data = last_word;

				iter_origin->cur_element->sub_list = malloc (sizeof(list_t));
				iter_origin->cur_element->sub_iter = malloc (sizeof(iter_t));
				Init_List	  ( (list_t*)iter_origin->cur_element->sub_list );
				Init_Iterator ( (iter_t*)iter_origin->cur_element->sub_iter );

				((iter_t*)iter_origin->cur_element->sub_iter)->linked_list = (list_t*)iter_origin->cur_element->sub_list;

				Add_Element( (iter_t*)iter_origin->cur_element->sub_iter );
				((iter_t*)iter_origin->cur_element->sub_iter)->cur_element->data = origin_word;
				printf("In list = %s, In sublist = %s\n",iter_origin->cur_element->data, ((iter_t*)iter_origin->cur_element->sub_iter)->cur_element->data);
				}
			word_written = 0;*/
		}



		cur_char++;
		i++;
	}

	return;
}

//------------------------------------------------------------------------------


void 	Printing_New_Dictionary  ( FILE* output, list_t* list_origin, iter_t* iter_origin )
{
	Rewind_List(iter_origin);
	while ( iter_origin->cur_element->next != NULL )
		{
		printf("%s:", iter_origin->cur_element->data );
		Iter_PP(iter_origin);
		Rewind_List((iter_t*)iter_origin->cur_element->sub_iter);
		while ( ((iter_t*)iter_origin->cur_element->sub_iter)->cur_element->next != NULL )
				{
				printf("%s,", ((iter_t*)iter_origin->cur_element->sub_iter)->cur_element->data );
				Iter_PP((iter_t*)iter_origin->cur_element->sub_iter);
				}
			printf("%s\n", ((iter_t*)iter_origin->cur_element->sub_iter)->cur_element->data );

		}
	printf("%s:", iter_origin->cur_element->data );

	Rewind_List((iter_t*)iter_origin->cur_element->sub_iter);
	while ( ((iter_t*)iter_origin->cur_element->sub_iter)->cur_element->next != NULL )
					{
					printf("%s,", ((iter_t*)iter_origin->cur_element->sub_iter)->cur_element->data );
					Iter_PP((iter_t*)iter_origin->cur_element->sub_iter);
					}
				printf("%s\n", ((iter_t*)iter_origin->cur_element->sub_iter)->cur_element->data );
	return;
}

//------------------------------------------------------------------------------
