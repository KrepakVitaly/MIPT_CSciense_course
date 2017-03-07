///  \brief           Command for Virtual Preprocessor v0.1
///
///  
///  \author		    Крепак zorroxied Виталий 016 ФРТК


#include "instr_set.cpp"


//------------------------------------------------------------------------------
//------Constants---------------------------------------------------------------

int const NO_CALLING_FUNC  = -2;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


void Nop_CPU ( Stack_t* CPU_Calc_Stack )
{
	return;
}

//------------------------------------------------------------------------------

double Pop_CPU ( Stack_t* CPU_Calc_Stack, int fun_code = NO_CALLING_FUNC )
{
		
	if ( Check_Damage (CPU_Calc_Stack) || CPU_Calc_Stack->pointer ==  0 ) 
	    printf ("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"
				"##Attention! Warning! The danger of total extermination!\n\n"
	    
				"##Error of pointer in Pop. I can't pop anything.\n" 
				"##Calling function is: %d\n"
	            "----------------------------------------------------------------\n"
				, fun_code ); //exit (18);
	 
    assert( !(Check_Damage (CPU_Calc_Stack) || CPU_Calc_Stack->pointer ==  0) );	
	
	double _out_value = Pop( CPU_Calc_Stack );
	if (fun_code == NO_CALLING_FUNC) return printf("%lf", _out_value);

	return _out_value;
}

//------------------------------------------------------------------------------
void Push_CPU ( Stack_t* CPU_Calc_Stack )
{
	return;
}

//------------------------------------------------------------------------------


void   Dup_CPU ( Stack_t* CPU_Calc_Stack )
{
	double t = Pop ( CPU_Calc_Stack );
	
	Push (CPU_Calc_Stack, t);
	Push (CPU_Calc_Stack, t);
	
	return;
}

//------------------------------------------------------------------------------

void   Swap_CPU ( Stack_t* CPU_Calc_Stack )
{
	double one = Pop ( CPU_Calc_Stack );
	double two = Pop ( CPU_Calc_Stack );
	
	Push (CPU_Calc_Stack, one);
	Push (CPU_Calc_Stack, two);
	
	return;
}

//------------------------------------------------------------------------------

void   Add_CPU ( Stack_t* CPU_Calc_Stack )
{
	double one = Pop ( CPU_Calc_Stack );
	double two = Pop ( CPU_Calc_Stack );
	
	Push (CPU_Calc_Stack, one+two );
	
	return;
}

//------------------------------------------------------------------------------

void   Sub_CPU ( Stack_t* CPU_Calc_Stack )
{
	double one = Pop ( CPU_Calc_Stack );
	double two = Pop ( CPU_Calc_Stack );
	
	Push (CPU_Calc_Stack, one-two );
	
	return;
}

//------------------------------------------------------------------------------

void   Div_CPU ( Stack_t* CPU_Calc_Stack )
{
	double one = Pop ( CPU_Calc_Stack );
	double two = Pop ( CPU_Calc_Stack );
	
	Push (CPU_Calc_Stack, one/two );
	
	return;
}

//------------------------------------------------------------------------------

void   Pow_CPU ( Stack_t* CPU_Calc_Stack )
{
	double base  = Pop ( CPU_Calc_Stack );
	double exp   = Pop ( CPU_Calc_Stack );

	base = pow ( base, exp );
	Push (CPU_Calc_Stack, base );	
	
	return;
}

//------------------------------------------------------------------------------

void   Sqrt_CPU ( Stack_t* CPU_Calc_Stack )
{
	double one = Pop ( CPU_Calc_Stack );
	
	Push (CPU_Calc_Stack, sqrt(one) );
	
	return;
}

//------------------------------------------------------------------------------

void   Sin_CPU ( Stack_t* CPU_Calc_Stack )
{
	double one = Pop ( CPU_Calc_Stack );
	
	Push (CPU_Calc_Stack, sin(one) );
	
	return;
}

//------------------------------------------------------------------------------

void   Cos_CPU ( Stack_t* CPU_Calc_Stack )
{
	double one = Pop ( CPU_Calc_Stack );
	
	Push (CPU_Calc_Stack, cos(one) );
	
	return;
}

//------------------------------------------------------------------------------

void Call_CPU ( int* cmd_counter, Stack_t* CPU_Addrs_Stack, double addr )
{
//	printf("I was called at %d to %lf\n", *cmd_counter, addr);
	Push ( CPU_Addrs_Stack, (double) (*cmd_counter + 1) );
//	printf("I was saved addr = %d\n", *cmd_counter + 1);
	
	
	*cmd_counter = (int) addr - 1;
	return;
}

//------------------------------------------------------------------------------

void Ret_CPU ( int* cmd_counter, Stack_t* CPU_Addrs_Stack)
{
	*cmd_counter = (int) Pop ( CPU_Addrs_Stack );
//	printf("I was restored cmd_count to %d\n", *cmd_counter );
	return;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

void Jmp_CPU ( int* cmd_counter, double addr )
{
	*cmd_counter = (int) addr - 1;
//	printf( "cmd_counter = %d\n", *cmd_counter+1 );
	
	if ( *cmd_counter < -1 || *cmd_counter >= PROG_MEMORY_SIZE ) 
	    printf ("Error of cmd_counter in Jmp. Incorrect addr.\n"
	            "----------------------------------------------------------------\n");
    assert( !(*cmd_counter < -1) );
		
	return;
}

//------------------------------------------------------------------------------
	    	
void Ja_CPU  ( int* cmd_counter, Stack_t* CPU_Calc_Stack, double addr )
{
	double  Oper_1 = Pop_CPU ( CPU_Calc_Stack, _ja );
	double  Oper_2 = Pop_CPU ( CPU_Calc_Stack, _ja );
	
	*cmd_counter = (int) addr - 1;
//	printf( "cmd_counter = %d\n", *cmd_counter+1 );
	
	if ( *cmd_counter < -1 || *cmd_counter >= PROG_MEMORY_SIZE ) 
	    printf ("Error of cmd_counter in Ja. Incorrect addr.\n"
	            "----------------------------------------------------------------\n");
    assert( !(*cmd_counter < -1) );
		
	return;
}

//------------------------------------------------------------------------------
	    		    	
void Jb_CPU  ( int* cmd_counter, Stack_t* CPU_Calc_Stack, double addr )
{
	
	double Oper_1 = Pop_CPU ( CPU_Calc_Stack, _jb );
	double Oper_2 = Pop_CPU ( CPU_Calc_Stack, _jb );	
	
	*cmd_counter = (int) addr - 1;
//	printf( "cmd_counter = %d\n", *cmd_counter+1 );
	
	if ( *cmd_counter < -1 || *cmd_counter >= PROG_MEMORY_SIZE ) 
	    printf ("Error of cmd_counter in Jb. Incorrect addr.\n"
	            "----------------------------------------------------------------\n");
    assert( !(*cmd_counter < -1) );
		
	return;
}

//------------------------------------------------------------------------------
	    		    	    		    	
void Je_CPU  ( int* cmd_counter, Stack_t* CPU_Calc_Stack, double addr )
{
	
	double Oper_1 = Pop_CPU ( CPU_Calc_Stack, _je );
	double Oper_2 = Pop_CPU ( CPU_Calc_Stack, _je );	
	
	*cmd_counter = (int) addr - 1;
//	printf( "cmd_counter = %d\n", *cmd_counter+1 );
	
	if ( *cmd_counter < -1 || *cmd_counter >= PROG_MEMORY_SIZE ) 
	    printf ("Error of cmd_counter in Je. Incorrect addr.\n"
	            "----------------------------------------------------------------\n");
    assert( !(*cmd_counter < -1) );
		
	return;
}

//------------------------------------------------------------------------------
	    		    		    	
void Jne_CPU ( int* cmd_counter, Stack_t* CPU_Calc_Stack, double addr )
{
	
	double Oper_1 = Pop_CPU ( CPU_Calc_Stack, _jne );
	double Oper_2 = Pop_CPU ( CPU_Calc_Stack, _jne );	
	
	*cmd_counter = (int) addr - 1;
//	printf( "cmd_counter = %d\n", *cmd_counter+1 );
	
	if ( *cmd_counter < -1 || *cmd_counter >= PROG_MEMORY_SIZE ) 
	    printf ("Error of cmd_counter in Jne. Incorrect addr.\n"
	            "----------------------------------------------------------------\n");
    assert( !(*cmd_counter < -1) );
		
	return;
}

//------------------------------------------------------------------------------
	    	
/*
void   Nop_CPU    ( Stack_t* CPU_Calc_Stack );

void   Dup_CPU    ( Stack_t* CPU_Calc_Stack );

void   Swap_CPU   ( Stack_t* CPU_Calc_Stack );

void   Add_CPU    ( Stack_t* CPU_Calc_Stack );

void   Sub_CPU    ( Stack_t* CPU_Calc_Stack );

void   Div_CPU    ( Stack_t* CPU_Calc_Stack );

void   Pow_CPU    ( Stack_t* CPU_Calc_Stack );

void   Sqrt_CPU   ( Stack_t* CPU_Calc_Stack );

void   Sin_CPU    ( Stack_t* CPU_Calc_Stack );

void   Cos_CPU    ( Stack_t* CPU_Calc_Stack );

//void   End_CPU    ( Stack_t* CPU_Calc_Stack );

void Call_CPU ( double Prog_Memory[], Stack_t* CPU_Addrs_Stack );
*/
