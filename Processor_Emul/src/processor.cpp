///  \brief           Virtual_Preprocessor v0.1
///
///  \description     This is program that simulate wokring of preprocessor
///
///  \author		    ������ zorroxied ������� 016 ����

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include "stack_functions.cpp"


//------------------------------------------------------------------------------
//------Constants---------------------------------------------------------------

int const CALC_STACK_SIZE   =   300;
int const ADDRS_STACK_SIZE  =   500;
int const PROG_MEMORY_SIZE  = 10000;
int const SIZE_OF_CMD       =     1;
// NOTE
//1.02.2011
//modification
//add the RAM and add memory instrument cmds

int const RAND_ACCESS_MEM_SIZE = 10000;


//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//---------Functions_Prototypes-------------------------------------------------

void Greeting();

void Simulate_of_Working();

void Progress_Bar     ( char* message );

int  Run_Processor    ( int Prog_Memory_Size, int Addrs_Stack_Size, int Calc_Stack_Size,
				            FILE* Machine_Code );
				    
int  Load_Program     ( FILE* Machine_Code, double Prog_Memory[] );
	
int  Execute_Program  ( double Prog_Memory[], Stack_t* CPU_Calc_Stack, 
								            Stack_t* CPU_Addrs_Stack );
								            
void Init_Prog_Memory ( double Prog_Memory[], int Prog_Memory_Size );	
			

#include "CPU_cmd.cpp"


//------------------------------------------------------------------------------


int main()
{
	Greeting();
	
	char Bin_File[]  = "binfile.zrx";
	
	FILE* Machine_Code = fopen ( Bin_File, "rb" );
	if ( !Machine_Code ) 
		return printf ("I can't find file with the machine code '%s'", Bin_File), 1;
	
	Simulate_of_Working();
	
	Run_Processor( PROG_MEMORY_SIZE, ADDRS_STACK_SIZE, CALC_STACK_SIZE,
				   Machine_Code );

	fclose ( Machine_Code );
	
	
	
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
	
	double Prog_Memory [ Prog_Memory_Size ]; //�������� ������ ��������
	
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
		
		//if (cmd_cache == _end) break;
		//printf("I'm at %d\n", cmd_counter);
		if ( ((int)cmd_cache - cmd_cache) ) {printf("I can't find cmd It's data.\n"); return 1;}
		
		
		switch ( (int)cmd_cache )
		{
			case _nop  : Nop_CPU     ( CPU_Calc_Stack ); break;
			
			case _push : Push        ( CPU_Calc_Stack, Prog_Memory[++cmd_counter] );  break;
			
	    	case _pop  : Pop_CPU     ( CPU_Calc_Stack ); break;
			 
	    	case _clr  : Stack_Clear ( CPU_Calc_Stack ); break;
			
	    	case _ok   : Check_Damage( CPU_Calc_Stack ); break;
			
	    	case _dump : Stack_Dump  ( CPU_Calc_Stack, WRITE_LIST_YES );
						 break;
			
	    	case _dup  : Dup_CPU     ( CPU_Calc_Stack ); break;
			
	    	case _swap : Swap_CPU    ( CPU_Calc_Stack ); break;
			
	    	case _add  : Add_CPU     ( CPU_Calc_Stack ); break;
			
	    	case _sub  : Sub_CPU     ( CPU_Calc_Stack ); break;
			
	    	case _div  : Div_CPU     ( CPU_Calc_Stack ); break;
	    	
	    	case _mul  : Mul_CPU     ( CPU_Calc_Stack ); break;
			
	    	case _pow  : Pow_CPU     ( CPU_Calc_Stack ); break;
			
	    	case _sqrt : Sqrt_CPU    ( CPU_Calc_Stack ); break;
			
	    	case _sin  : Sin_CPU     ( CPU_Calc_Stack ); break; 
			
	    	case _cos  : Cos_CPU     ( CPU_Calc_Stack ); break; 
	    	
	    	
    	    case _call : Call_CPU    ( &cmd_counter, CPU_Addrs_Stack, 
			                                         Prog_Memory[cmd_counter+1] );
						 cmd_counter++; 
						 break;
	    	
	    	case _ret  : Ret_CPU     ( &cmd_counter, CPU_Addrs_Stack ); break;
	    	
	    	
	    	case _jmp  : Jmp_CPU     ( &cmd_counter, Prog_Memory[cmd_counter+1] ); 
						 cmd_counter++;
						 break;
	    	
	    	case _ja   : Ja_CPU      ( &cmd_counter, CPU_Calc_Stack, 
									                 Prog_Memory[cmd_counter+1] ); 
						 cmd_counter++;
						 break;
	    	
	    	case _jb   : Jb_CPU      ( &cmd_counter, CPU_Calc_Stack, 
					                                 Prog_Memory[cmd_counter+1] ); 
						 cmd_counter++;
						 break;
	    	
	    	case _je   : Je_CPU      ( &cmd_counter, CPU_Calc_Stack, 
			 										 Prog_Memory[cmd_counter+1] ); 
						 cmd_counter++;
						 break;
	    	
	    	case _jne  : Jne_CPU     ( &cmd_counter, CPU_Calc_Stack, 
													 Prog_Memory[cmd_counter+1] );
						 cmd_counter++; 
						 break;
	    	
	    	
	    	case _end  : printf("FinitA\n"); return 0;
	    	
	    	default    : printf("I can't find cmd. Line %d\n",cmd_counter ); //��������� ���
						 return 1;
		}
		cmd_counter++;
	}
	

	
	return 0;
}
		
//------------------------------------------------------------------------------		
				    
int Load_Program ( FILE* Machine_Code, double Prog_Memory[] )
{
	unsigned char   cmd_cache   = 0;
	double  		d_cmd_cache = 0;
	double  		data_cache  = 0;
	
	int i = 0;
	
	while ( true )
	{
	fread ( &cmd_cache, sizeof(cmd_cache), 1, Machine_Code );	
	
		if (  feof( Machine_Code ) ) 
		{
			//printf("End of file\n");
			return 0;
		}
//It's debug part		fread �� ���� ����
//		printf("In progress\n");
//It's debug part

		if (  ferror( Machine_Code ) ) 
		{
			printf("Error of read\n");
			return 0;
		}

		d_cmd_cache = (double) cmd_cache;
		
	//It's debug part
	//	printf("I was found cmd = %lf\n", d_cmd_cache );
	//It's debug part
	
		Prog_Memory[i++] = d_cmd_cache;
		
		if (( d_cmd_cache == _push ) ||
			( d_cmd_cache == _call ) ||
			( d_cmd_cache == _jmp  ) ||
			( d_cmd_cache == _ja   ) ||
			( d_cmd_cache == _jb   ) ||
			( d_cmd_cache == _je   ) ||
			( d_cmd_cache == _jne  ) )
		{	
			fread ( &data_cache, sizeof(data_cache) , 1, Machine_Code );
			Prog_Memory[i++] = data_cache;
			
		//It's debug part
		//	printf("I was found data = %lf\n", data_cache );
		//It's debug part
		}

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
			"for me, saved the program in the file 'binfile.zrx'.\n"
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
	printf("\n");
	char* display_mes = "I'm search the bin...";  //����� ������ - 21 ������
	
	for ( int i = 0; i < 21; i++ )
	{
		printf("%c", *( display_mes + i ) );
		Sleep(80);
	}
	
	Sleep(1700);
	printf("\n\n");

	display_mes = "Searching..."; //����� ������ - 12 ������
	
	for ( int i = 0; i < 12; i++ )
	{
		printf("%c", *( display_mes + i ) );
		Sleep(80);
	}
	
	Sleep(1600);
	
	
	Progress_Bar(" ");
	Sleep(1600);
	
	printf("\n");
	display_mes = "Yes, the binfile was detected."; //����� ������ - 30 ������
	for ( int i = 0; i < 30; i++ )
	{
		printf("%c", *( display_mes + i ) );
		Sleep(80);
	}
	Sleep(1600);
	printf("\n\n");
	
	display_mes = "Executing of program:"; //����� ������ - 20 ������
	for ( int i = 0; i < 20; i++ )
	{
		printf("%c", *( display_mes + i ) );
		Sleep(80);
	}
	Sleep(1800);
	
	Progress_Bar(" ");
	Sleep(1400);
	printf("\n");
	
	display_mes = "Succesfully!"; //����� ������ - 12 ������
	for ( int i = 0; i < 12; i++ )
	{
		printf("%c", *( display_mes + i ) );
		Sleep(80);
	}
	Sleep(1900);
	printf("\n\n");

}

//------------------------------------------------------------------------------

