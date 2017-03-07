///  \brief           Stack_Functions
///
///  \description     Release of Stack
///  \author		    Крепак zorroxied Виталий 016 ФРТК


#include <assert.h>


//------------------------------------------------------------------------------
//------Constants---------------------------------------------------------------

int const SIZE_OF_STACK   = 1000;
int const WRITE_LIST_YES  =    1;
int const WRITE_LIST_NO   =    0;
int const BEGIN_OF_STACK  =    0;
int const TERMINATE       = -666;

//------------------------------------------------------------------------------
//------My_Types----------------------------------------------------------------

struct Stack_t
	{
		double*     Begin_Stack;
	//	double*     Current_Element;
		int         pointer;
		int         Size_of_Stack;
	};
	
//------------------------------------------------------------------------------
//---------Functions_Prototypes-------------------------------------------------

void Stack_Construct ( Stack_t* Ordering_Stack , int Stack_Size, int size_of_element );

void            Push ( Stack_t* Stack , double input_value );

double           Pop ( Stack_t* Stack );

void     Stack_Clear ( Stack_t* Stack );

double     Stack_Top ( Stack_t* Stack );

int     Check_Damage ( Stack_t* Stack );
 
void  Stack_Destruct ( Stack_t* Stack );

int       Stack_Dump ( Stack_t* Stack, int With_List_of_Elements );

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

int Check_Damage ( Stack_t* Stack )
{
	if ( ( Stack->pointer <  BEGIN_OF_STACK       ) ||
	     ( Stack->pointer >= Stack->Size_of_Stack ))   
					return printf("Error of pointer in Check_Damage.\n"),1;
	return 0;
}

//------------------------------------------------------------------------------

void Stack_Construct ( Stack_t* Ordering_Stack , int Stack_Size , int size_of_element )
{
	
	Ordering_Stack->Begin_Stack     = (double*) malloc ( Stack_Size * size_of_element );
	
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

void Push ( Stack_t* Stack , double input_value )
{	
//	if ( Check_Damage (Stack) ) { printf("Error of pointer\n"); return;}
	
	if ( Check_Damage (Stack) ) 
	    printf ("I was cheked damage of stack in Push \n"
	            "----------------------------------------------------------------\n");
    assert( !Check_Damage(Stack) );		
	
	*( Stack->Begin_Stack + Stack->pointer ) = input_value;
	   Stack->pointer++;
}

//------------------------------------------------------------------------------

double Pop ( Stack_t* Stack )
{	
	
	if ( Check_Damage (Stack) || Stack->pointer ==  0 ) 
	    printf ("I was cheked damage of stack in Pop.\n"
	            "----------------------------------------------------------------\n");
	 
    assert( !(Check_Damage (Stack) || Stack->pointer ==  0) );	
	
	
	Stack->pointer--;
	
	return *( Stack->Begin_Stack + Stack->pointer );
}

//------------------------------------------------------------------------------

void Stack_Clear ( Stack_t* Stack )
{
//	if ( Check_Damage (Stack) )  { printf("Error of pointer\n"); return;}
	
	if ( Check_Damage (Stack) ) 
	    printf ("I was cheked damage of stack in Stack_Clear\n"
	            "----------------------------------------------------------------\n");
    assert( !Check_Damage(Stack) );		
	
	
	Stack->pointer = BEGIN_OF_STACK;
	return;
}

//------------------------------------------------------------------------------

int Stack_Dump ( Stack_t* Stack, int With_List_of_Elements )
{
	char Dump[]   = "dump.txt";
	
	FILE* output  = fopen ( Dump, "a" );
	
	
	fprintf ( output, "Hello! I'm dump of your stack.\n"
					  "If you called me, then you in a trouble.\n"
					  "I hope, I can help you, my master...\n\n"
					  
					  "Date of call me: " __DATE__"  " __TIME__"\n\n"
					  
					  "Stack parameters:\n\n");
					  
	fprintf	( output, "The number of elements     =  %d;\n"  ,   Stack->Size_of_Stack );
	fprintf	( output, "Pointer value in this time =  %d;\n"  ,   Stack->pointer );
	fprintf	( output, "The last element           =  %lf;\n" , *(Stack->Begin_Stack + Stack->pointer - 1) );
															  
	fprintf	( output, "The address of beginning   =  %d;\n"  ,   Stack->Begin_Stack );
	
	if (With_List_of_Elements)
		{ 
		fprintf ( output, "\nThis elements contains in stack this time:\n");
		
		for( int i = 0; i < Stack->Size_of_Stack ; i++ )
		      fprintf ( output, "%lf\n", *(Stack->Begin_Stack + i) );
		}
	fclose ( output );			  
	return 0;
}

//------------------------------------------------------------------------------

double Stack_Top ( Stack_t* Stack )
{
	double top = Pop ( Stack );
	Push ( Stack, top );
	return top;
}

//------------------------------------------------------------------------------

