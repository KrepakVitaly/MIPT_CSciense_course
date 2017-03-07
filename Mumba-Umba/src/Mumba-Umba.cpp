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

void 	Printing_New_Dictionary  ( FILE* output,  iter_t* iter_origin );


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
	if ( output == NULL ) { printf("Output file not opened.\n"); fclose(input);  return -1; }
	if ( input  == NULL ) { printf("Input  file not opened.\n"); fclose(output); return -1; }


//-------List initialization
	list_t origin_list = {};
	Init_List( &origin_list );

	iter_t iter_origin = {};
	Init_Iterator ( &iter_origin );
	iter_origin.linked_list = &origin_list;

//------------------------------


//---------------_Target_of_work_---------------
	Loading_Dictionary      ( input,  &origin_list, &iter_origin );

	Printing_New_Dictionary ( output, &iter_origin );
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

//ssacnf(%[]%n);
//strtok(  );
void Loading_Dictionary		 ( FILE* input , list_t* list_origin, iter_t* iter_origin )
{
	int size = 0;

	fseek(input, 0, SEEK_END);
	size = ftell(input);
	fseek(input, 0, SEEK_SET);

	void* container = malloc(sizeof(char)*size);

	fread ( container, sizeof(char)*(size), 1, input );
	*((char*)container+sizeof(char)*(size) - 2) = '\0';

	printf( "%s\n\n\n", (char*)container );

	char* cur_char      = (char*) container;
	char* cur_word      = (char*) container;
	char* origin_word   = (char*) container;
	char* last_word     = (char*) container;

	int   word_written  = 0;
	int   change_words  = 0;

	while ( *cur_char != '\0' )
	{
		//-------------------------------------------------
		//
		if ( *cur_char == ':')
			{
			change_words = 1;
			*cur_char = '\0';
			origin_word = cur_word;
			//printf("Origin word   = %s  Last word   = %s\n", origin_word, cur_word);
			cur_char++;
			last_word = cur_word;
			cur_word = cur_char;
			}
		//-------------------------------------------------

		//-------------------------------------------------
		//---
		if ( *cur_char == ',' || *cur_char == '\n'  )
			{
			change_words = 1;
			*cur_char = '\0';
			cur_char++;
			//printf("Origin word   = %s  Last word   = %s\n", origin_word, cur_word);
			last_word = cur_word;
			cur_word = cur_char;
			}

		if ( *(cur_char + 1) == '\0' )
			{
			change_words = 1;
			//printf("Origin word   = %s  Last word   = %s\n", origin_word, cur_word);
			last_word = cur_word;
			}


	if (change_words)
	{
		change_words = 0;
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
			//printf("Create sub list. In sublist %s = %s\n", last_word, origin_word);

			Add_Element( (iter_t*)iter_origin->cur_element->sub_iter );
			((iter_t*)iter_origin->cur_element->sub_iter)->cur_element->data = origin_word;

			//printf("In list = %s, In sublist = %s\n",iter_origin->cur_element->data, ((iter_t*)iter_origin->cur_element->sub_iter)->cur_element->data);
		}
		else
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

					//Rewind_to_end_List( (iter_t*)iter_origin->cur_element->sub_iter );
					Add_Element( (iter_t*)iter_origin->cur_element->sub_iter );
					((iter_t*)iter_origin->cur_element->sub_iter)->cur_element->data = origin_word;
					//printf("In sublist = %s\n",((iter_t*)iter_origin->cur_element->sub_iter)->cur_element->data);
					//printf("End In sublist %s = %s\n", last_word, ((iter_t*)iter_origin->cur_element->sub_iter)->linked_list->end->data);
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
				//printf("End In sublist %s = %s\n", last_word, ((iter_t*)iter_origin->cur_element->sub_iter)->linked_list->end->data);
				//printf("In sublist = %s\n",((iter_t*)iter_origin->cur_element->sub_iter)->cur_element->data);
				}


				if ( word_written == 0 ) //не нашли такого слова
				{
					Rewind_to_end_List(iter_origin);
					Add_Element(iter_origin);
					iter_origin->cur_element->data = last_word;
					//printf("End = %s \n", iter_origin->cur_element->data );

					iter_origin->cur_element->sub_iter = malloc(sizeof(iter_t));
					iter_origin->cur_element->sub_list = malloc(sizeof(list_t));

					Init_List	  ( (list_t*)iter_origin->cur_element->sub_list );
					Init_Iterator ( (iter_t*)iter_origin->cur_element->sub_iter );

					((iter_t*)iter_origin->cur_element->sub_iter)->linked_list = (list_t*)iter_origin->cur_element->sub_list;
					Add_Element((iter_t*)iter_origin->cur_element->sub_iter);
					((iter_t*)iter_origin->cur_element->sub_iter)->cur_element->data = origin_word;
					//printf("Create sub list. In sublist %s = %s\n", last_word, origin_word);
					//printf("Prev of sublist = %s    ", ((iter_t*)iter_origin->cur_element->sub_iter)->cur_element->prev->data );
					//printf("End of sublist = %s\n", ((iter_t*)iter_origin->cur_element->sub_iter)->cur_element->data );
				}
			word_written = 0;
		}
	}
		cur_char++;
	}

	return;
}

//------------------------------------------------------------------------------


void 	Printing_New_Dictionary  ( FILE* output, iter_t* iter_origin )
{
	Rewind_List(iter_origin);
	while ( iter_origin->cur_element->next != NULL )
		{
		printf("%s:", iter_origin->cur_element->data );


		Rewind_List((iter_t*)iter_origin->cur_element->sub_iter);
		while ( ((iter_t*)iter_origin->cur_element->sub_iter)->cur_element->next != NULL )
				{
				printf("%s,", ((iter_t*)iter_origin->cur_element->sub_iter)->cur_element->data );
				Iter_PP((iter_t*)iter_origin->cur_element->sub_iter);

				free( ((iter_t*)iter_origin->cur_element->sub_iter)->cur_element->prev );
				}
			printf("%s\n", ((iter_t*)iter_origin->cur_element->sub_iter)->cur_element->data );

			free( ((iter_t*)iter_origin->cur_element->sub_iter)->cur_element );
			free( ((iter_t*)iter_origin->cur_element->sub_iter)->linked_list);
			free( iter_origin->cur_element->sub_iter );

			Iter_PP(iter_origin);

		free( iter_origin->cur_element->prev->sub_iter );
		free( iter_origin->cur_element->prev->sub_list );
		free( iter_origin->cur_element->prev );

		}

	printf("%s:", iter_origin->cur_element->data );

	Rewind_List((iter_t*)iter_origin->cur_element->sub_iter);
	while ( ((iter_t*)iter_origin->cur_element->sub_iter)->cur_element->next != NULL )
		{
		printf("%s,", ((iter_t*)iter_origin->cur_element->sub_iter)->cur_element->data );
		Iter_PP((iter_t*)iter_origin->cur_element->sub_iter);

		free( ((iter_t*)iter_origin->cur_element->sub_iter)->cur_element->prev );
		}

	printf("%s\n", ((iter_t*)iter_origin->cur_element->sub_iter)->cur_element->data );
	free( ((iter_t*)iter_origin->cur_element->sub_iter)->cur_element );

	free( ((iter_t*)iter_origin->cur_element->sub_iter)->linked_list);
	free( iter_origin->cur_element->sub_iter );

	free( iter_origin->cur_element->sub_iter );
	free( iter_origin->cur_element->sub_list );
	free( iter_origin->cur_element );


	return;
}

//------------------------------------------------------------------------------
