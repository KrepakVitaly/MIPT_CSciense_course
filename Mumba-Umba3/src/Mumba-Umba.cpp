///  \brief
///
///  \description
///  \author		    Крепак zorroxied Виталий 016 ФРТК

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>

#include "double_list.h"

//------------------------------------------------------------------------------
//------Constants---------------------------------------------------------------


//------------------------------------------------------------------------------
//---------Functions_Prototypes-------------------------------------------------

void 	Loading_Dictionary		 ( FILE* input , list_t* list_origin, iter_t* iter_origin );

void 	Printing_New_Dictionary  ( FILE* output, list_t* list_origin, iter_t* iter_origin );

void 	Rebuilding_Dictionary 	 ( list_t* list_origin , iter_t* iter_origin );

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
	Loading_Dictionary  ( input,  &origin_list, &iter_origin );

	Rebuilding_Dictionary   ( &origin_list, &iter_origin );

	//Printing_New_Dictionary ( output, &origin_list, &iter_origin );
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
	*((char*)container+sizeof(char)*(size)-3) = '\0';

	printf( "%s\n", (char*)container );

	char* cur_char    = (char*) container;
	char* cur_word    = (char*) container;
	char* origin_word = (char*) container;
	char* last_word   = (char*) container;

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
			last_word = cur_word;
			printf("Origin word   = %s  Last word   =  %s\n", origin_word, cur_word);
			}
		//--------------------------------------------------

		if ( strcmp(last_word,origin_word) != 0 )
		{
			Add_Element(iter_origin);
			iter_origin->cur_element->data = last_word;
			printf("In list = %s\n",iter_origin->cur_element->data);
		}



		cur_char++;
	}

	return;
}

//------------------------------------------------------------------------------


void 	Printing_New_Dictionary  ( FILE* output, list_t* list_origin, iter_t* iter_origin )
{
	Rewind_List(iter_origin);
	while ( iter_origin->cur_element->next != NULL )
		{
		printf("%s\n", iter_origin->cur_element->data );
		Iter_PP(iter_origin);
		}
	return;
}

//------------------------------------------------------------------------------

void 	Rebuilding_Dictionary 	 ( list_t* list_origin , iter_t* iter_origin )
{

	return;
}

