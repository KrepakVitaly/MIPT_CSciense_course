///  \brief           Virtual_Preprocessor v0.1
///
///  \description     This is program that simulate wokring of preprocessor
///
///  \author		    Крепак zorroxied Виталий 016 ФРТК

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include "stack_functions.cpp"


//------------------------------------------------------------------------------
//------Constants---------------------------------------------------------------

int const CALC_STACK_SIZE   =  100;
int const ADDRS_STACK_SIZE  =   20;
int const PROG_MEMORY_SIZE  = 1000;

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//---------Functions_Prototypes-------------------------------------------------

void Greeting();

void Progress_Bar( char* message );

void Simulate_of_Working();

int Run_Processor   ( int Prog_Memory_Size, int Addrs_Stack_Size, int Calc_Stack_Size,
				          FILE* Machine_Code );
				    
int Load_Program    ( FILE* Machine_Code, double Prog_Memory[] );
	
int Execute_Program ( double Prog_Memory[], Stack_t* CPU_Calc_Stack, 
								            Stack_t* CPU_Addrs_Stack );
								            
void Init_Prog_Memory( double Prog_Memory[], int Prog_Memory_Size );						

#include "CPU_cmd.cpp"


//------------------------------------------------------------------------------


int main()
{
	Greeting();
	
	char Bin_File[]  = "memory.txt";
	
	FILE* Machine_Code = fopen ( Bin_File, "r" );
	if ( !Machine_Code ) 
		return printf ("I can't find file with the machine code '%s'", Bin_File), 1;
	
	
	Run_Processor( PROG_MEMORY_SIZE, ADDRS_STACK_SIZE, CALC_STACK_SIZE,
				   Machine_Code );

	fclose ( Machine_Code );
	
	Simulate_of_Working();
	
	system("PAUSE");	
	return 0;
}


//------------------------------------------------------------------------------

int Run_Processor ( int Prog_Memory_Size, int Addrs_Stack_Size, int Calc_Stack_Size, 
				    FILE* Machine_Code )
{
	struct Stack_t CPU_Calc_Stack  = {};
	struct Stack_t CPU_Addrs_Stack = {};
	
	Stack_Construct ( &CPU_Calc_Stack,  Calc_Stack_Size,  sizeof(double) );
	Stack_Construct ( &CPU_Addrs_Stack, Addrs_Stack_Size, sizeof(double) );
	
	double Prog_Memory [ Prog_Memory_Size ];
	
	Init_Prog_Memory( Prog_Memory, Prog_Memory_Size );
	
	Load_Program ( Machine_Code, Prog_Memory );
	
	Execute_Program ( Prog_Memory, &CPU_Calc_Stack, &CPU_Addrs_Stack );
	
	Stack_Destruct ( &CPU_Calc_Stack );
	Stack_Destruct ( &CPU_Addrs_Stack);
	
	return 0;
}

//------------------------------------------------------------------------------

int Execute_Program ( double Prog_Memory[], Stack_t* CPU_Calc_Stack, 
					                        Stack_t* CPU_Addrs_Stack )
{
	double cmd_cache   =  0;
	int    cmd_counter =  0;
	while ( true )
	{
		cmd_cache = Prog_Memory[cmd_counter];
		
		if (cmd_cache == _end) break;
		
		if ( ((int)cmd_cache - cmd_cache) ) {printf("I can't find cmd It's data.\n"); return 1;}
		
		
		switch ( (int)cmd_cache )
		{
			case _nop  : Nop_CPU     ( CPU_Calc_Stack ); break;
			
			case _push : Push        ( CPU_Calc_Stack, Prog_Memory[++cmd_counter] );  break;
			
	    	case _pop  : Pop_CPU     ( CPU_Calc_Stack ); break;
			 
	    	case _clear: Stack_Clear ( CPU_Calc_Stack ); break;
			
	    	case _ok   : Check_Damage( CPU_Calc_Stack ); break;
			
	    	case _dump : Stack_Dump  ( CPU_Calc_Stack, WRITE_LIST_NO );
						 break;
			
	    	case _dup  : Dup_CPU     ( CPU_Calc_Stack ); break;
			
	    	case _swap : Swap_CPU    ( CPU_Calc_Stack ); break;
			
	    	case _add  : Add_CPU     ( CPU_Calc_Stack ); break;
			
	    	case _sub  : Sub_CPU     ( CPU_Calc_Stack ); break;
			
	    	case _div  : Div_CPU     ( CPU_Calc_Stack ); break;
			
	    	case _pow  : Pow_CPU     ( CPU_Calc_Stack ); break;
			
	    	case _sqrt : Sqrt_CPU    ( CPU_Calc_Stack ); break;
			
	    	case _sin  : Sin_CPU     ( CPU_Calc_Stack ); break; 
			
	    	case _cos  : Cos_CPU     ( CPU_Calc_Stack ); break; 
	    	
	    	
    	    case _call : Call_CPU    ( &cmd_counter, CPU_Addrs_Stack, 
			                                         Prog_Memory[cmd_counter+1] ); 
						 break;
	    	
	    	case _ret  : Ret_CPU     ( &cmd_counter, CPU_Addrs_Stack ); break;
	    	
	    	
	    	case _jmp  : Jmp_CPU     ( &cmd_counter, Prog_Memory[cmd_counter+1] ); 
						 break;
	    	
	    	case _ja   : Ja_CPU      ( &cmd_counter, CPU_Calc_Stack, 
									                 Prog_Memory[cmd_counter+1] ); 
						 break;
	    	
	    	case _jb   : Jb_CPU      ( &cmd_counter, CPU_Calc_Stack, 
					                                 Prog_Memory[cmd_counter+1] ); 
						 break;
	    	
	    	case _je   : Je_CPU      ( &cmd_counter, CPU_Calc_Stack, 
			 										 Prog_Memory[cmd_counter+1] ); 
						 break;
	    	
	    	case _jne  : Jne_CPU     ( &cmd_counter, CPU_Calc_Stack, 
													 Prog_Memory[cmd_counter+1] ); 
						 break;
	    	
	    	case _end  : printf("FinitA\n"); return 0;
	    	
	    	default    : printf("I can't find cmd It's data.\n"); return 1;
		}
		cmd_counter++;
	}
	

	
	return 0;
}
		
//------------------------------------------------------------------------------		
				    
int Load_Program ( FILE* Machine_Code, double Prog_Memory[] )
{
	double cmd_cache = 0;
	int i = 0;
	
	while ( true )
	{
		
		if ( fscanf ( Machine_Code, "%lf", &cmd_cache ) == EOF ) 
			{
			return 0;
			}
		
	//	if (cmd_cache == _end) break;
		
		Prog_Memory[i++] = cmd_cache;
	}
	
	return 0;
}

//------------------------------------------------------------------------------

void Greeting()
{
	printf ("\n------------------------------------------------------------\n");
	printf ("Hello! I'm a virtual preprocessor by Zorroxied(c)\n"
	        "Date of compilation - " __DATE__ "   " __TIME__ "\n\n"
			"If you want to work with me, you must write the program\n"
			"for me, saved the program in the file 'memory.txt'.\n"
			"And put it at the directory, where is situated  '.exe'.\n\n");
}

//------------------------------------------------------------------------------

void   Init_Prog_Memory( double Prog_Memory[], int Prog_Memory_Size )
{
    for ( int i = 0 ; i < Prog_Memory_Size ; i++ )
     { 
		Prog_Memory[i]  = 0.0;
     }
}
//------------------------------------------------------------------------------

void Progress_Bar( char* message )
{
	printf ("\n%s\n", message);

	for (int i = 0 ; i < 20 ; i++ ) {Sleep (100); printf ("#");};
	printf ("\n");
 
}

//------------------------------------------------------------------------------

void Simulate_of_Working()
{
	char* display_mes = "I'm search the bin...";  //длина строки - 21 символ
	
	for ( int i = 0; i < 21; i++ )
	{
		printf("%c", *( display_mes + i ) );
		Sleep(80);
	}
	Sleep(1700);
	printf("\n");

	display_mes = "Searching..."; //длина строки - 12 символ
	
	for ( int i = 0; i < 12; i++ )
	{
		printf("%c", *( display_mes + i ) );
		Sleep(80);
	}
	Sleep(1600);
	
	
	Progress_Bar(" ");
	Sleep(1600);
	
	printf("\n");
	display_mes = "Yes, the binfile was detected."; //длина строки - 30 символ
	for ( int i = 0; i < 30; i++ )
	{
		printf("%c", *( display_mes + i ) );
		Sleep(80);
	}
	Sleep(1600);
	printf("\n\n");
	
	display_mes = "Executing of program:"; //длина строки - 20 символ
	for ( int i = 0; i < 20; i++ )
	{
		printf("%c", *( display_mes + i ) );
		Sleep(80);
	}
	Sleep(1800);
	
	Progress_Bar(" ");
	Sleep(1400);
	
	display_mes = "Succesfully!"; //длина строки - 12 символ
	for ( int i = 0; i < 12; i++ )
	{
		printf("%c", *( display_mes + i ) );
		Sleep(80);
	}
	Sleep(1900);
	printf("\n\n");

}

//------------------------------------------------------------------------------
