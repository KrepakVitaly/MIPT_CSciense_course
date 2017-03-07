///  \brief           Stack_Functions
///
///  \description     Release of Stack
///  \author		    Крепак zorroxied Виталий 016 ФРТК


int const SIZE_OF_STACK   = 1000;
int const WRITE_LIST_YES  =    1;
int const WRITE_LIST_NO   =    0;
int const BEGIN_OF_STACK  =    0;
int const TERMINATE       = -666;

//------------------------------------------------------------------------------
//------My_Types----------------------------------------------------------------

struct Stack_t
	{
		int*  Begin_Stack;
		int*  Current_Element;
		int   pointer;
		int   Size_of_Stack;
	};
	
//------------------------------------------------------------------------------
//---------Functions_Prototypes-------------------------------------------------

void Stack_Construct ( Stack_t* Ordering_Stack , int Stack_Size, int size_of_element );

void            push ( Stack_t* Stack , int input_value );

int              pop ( Stack_t* Stack );

void     Stack_Clear ( Stack_t* Stack );

int        Stack_Top ( Stack_t* Stack );

int     Check_Damage ( Stack_t* Stack );
 
void  Stack_Destruct ( Stack_t* Stack );

void      Stack_Dump ( Stack_t* Stack, FILE* output, int With_List_of_Elements );

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

int Check_Damage ( Stack_t* Stack )
{
	if ( ( Stack->pointer <  BEGIN_OF_STACK       ) ||
	     ( Stack->pointer >= Stack->Size_of_Stack ))   
					return printf("Error of pointer\n"),1;
	    
	return 0;
}

//------------------------------------------------------------------------------

void Stack_Construct ( Stack_t* Ordering_Stack , int Stack_Size , int size_of_element )
{
	
	Ordering_Stack->Begin_Stack = (int*) malloc ( Stack_Size * size_of_element );
	

	Ordering_Stack->Current_Element = Ordering_Stack->Begin_Stack;
	
	Ordering_Stack->Size_of_Stack   = Stack_Size;
	
	Ordering_Stack->pointer         = BEGIN_OF_STACK;
	
	return;
}

//------------------------------------------------------------------------------

void Stack_Destruct ( Stack_t* Stack )
{	
	free ( Stack->Begin_Stack );
	Stack->pointer = TERMINATE;
	return;
}

//------------------------------------------------------------------------------

void push ( Stack_t* Stack , int input_value )
{	
	if ( Check_Damage (Stack) ) { printf("Error of pointer\n"); return;}
	
	*( Stack->Current_Element + Stack->pointer ) = input_value;
	   Stack->pointer++;
}

//------------------------------------------------------------------------------

int pop ( Stack_t* Stack )
{	
	
	if ( Check_Damage (Stack) ) return  printf("Error of pointer\n");
	
	Stack->pointer--;
	
//	int output_value = ;
	
	return *( Stack->Current_Element + Stack->pointer );
}

//------------------------------------------------------------------------------

void Stack_Clear ( Stack_t* Stack )
{
	if ( Check_Damage (Stack) )  { printf("Error of pointer\n"); return;}
	
	Stack->pointer = BEGIN_OF_STACK;
	return;
}

//------------------------------------------------------------------------------

void Stack_Dump ( Stack_t* Stack, FILE* output, int With_List_of_Elements )
{
	fprintf ( output, "Hello! I'm dump of your stack.\n"
					  "If you called me, then you in a trouble.\n"
					  "I hope, I can help you, my master...\n\n"
					  
					  "Stack parameters:\n\n");
					  
	fprintf	( output, "The number of elements     =  %d;\n" ,  Stack->Size_of_Stack );
	fprintf	( output, "Pointer value in this time =  %d;\n" ,  Stack->pointer );
	fprintf	( output, "The last element           =  %d;\n" , *Stack->Current_Element );
	fprintf	( output, "The address of beginning   =  %d;\n" ,  Stack->Begin_Stack );
	
	if (With_List_of_Elements)
		{ 
		fprintf ( output, "\nThis elements contains in stack this time:\n");
		
		for( int i = 0; i < Stack->Size_of_Stack ; i++ )
		      fprintf ( output, "%d\n", *(Stack->Begin_Stack + i) );
		}
					  
	return;
}

//------------------------------------------------------------------------------

int Stack_Top ( Stack_t* Stack )
{
	int top = pop ( Stack );
	push ( Stack, top );
	return top;
}

//------------------------------------------------------------------------------















