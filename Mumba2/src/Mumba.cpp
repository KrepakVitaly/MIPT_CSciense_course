///  \brief
///
///  \description
///  \author		    Крепак zorroxied Виталий 016 ФРТК

#include <stdio.h>
#include <string.h>
#include <malloc.h>

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
	char output_label[] = "output.txt";


	FILE* input  = fopen ( input_label , "r" );
	FILE* output = fopen ( output_label, "w+" );

//-------------- TODO -- closing file
	if ( output == NULL ) { printf("Output file not opened.\n"); fclose(input); return -1; }
	if ( input  == NULL ) { printf("Input  file not opened.\n"); fclose(output); return -1; }


//-------List initialization
	list_t origin_list   = {};
	Init_List( &origin_list );

	iter_t iter_origin = {};
	Init_Iterator ( &iter_origin );
	iter_origin.linked_list = &origin_list;
//------------------------------


	//---------------_Target_of_work_---------------
	Loading_Dictionary  ( input,  &origin_list, &iter_origin );

	Rebuilding_Dictionary   ( &origin_list, &iter_origin );

	Printing_New_Dictionary ( output, &origin_list, &iter_origin );
	//----------------------------------------------

	fclose(input);
	fclose(output);
	return 0;
}



//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

void 	Loading_Dictionary		 ( FILE* input , list_t* origin_list   )
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
	char* last_word   = (char*) container;
	char* origin_word = (char*) container;

	while ( *cur_char != '\0' )
	{
		//-------------------------------------------------
		//    пїЅпїЅпїЅпїЅ "пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ" пїЅпїЅпїЅпїЅпїЅ
		if ( *cur_char == ':')
			{
			*cur_char = '\0';
			origin_word = last_word;
			printf("Origin word   = %s\n", origin_word);
			cur_char++;
			last_word = cur_char;

			}
		//-------------------------------------------------

		//-------------------------------------------------
		//---   пїЅпїЅпїЅпїЅ "пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ" пїЅпїЅпїЅпїЅпїЅ
		if ( *cur_char == ',' || *cur_char == '\n'  )
			{
			*cur_char = '\0';
			cur_char++;
			printf("Last word   = %s\n", last_word);
			last_word = cur_char;
			}

		if ( *(cur_char + 1) == '\0' )
			{
			printf("Last word   = %s\n", last_word);
			}
		//--------------------------------------------------

		//   пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ
		if ( last_word != origin_word )
			{

			}


		cur_char++;
	}

	return;
}

//------------------------------------------------------------------------------

void 	Printing_New_Dictionary  ( FILE* output, list_t* re_alloc_list )
{

	return;
}

//------------------------------------------------------------------------------

void 	Rebuilding_Dictionary 	 ( list_t* origin_list , list_t* re_alloc_list )
{

	return;
}

