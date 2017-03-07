///  \brief           Assembler for Virtual_Preprocessor v0.1
///
///  
///  \author		    Крепак zorroxied Виталий 016 ФРТК

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "instr_set.cpp"


//------------------------------------------------------------------------------
//------Constants---------------------------------------------------------------

int const UNIT_RECORD = 1;

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//---------Functions_Prototypes-------------------------------------------------

void Greeting();

int Go_Assemle( FILE* Source_Code );

//------------------------------------------------------------------------------


int main()
{
	Greeting();
	
	char Source[]  = "source.txt";
	
	FILE* Source_Code = fopen ( Source, "r" );
	if ( !Source_Code ) 
		return printf ("I can't find file with the source code '%s'", Source), 1;
	
	
	Go_Assemle( Source_Code );

	fclose ( Source_Code );


	system("PAUSE");	
	return 0;
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

void Greeting()
{
	printf ("\n------------------------------------------------------------\n");
	printf ("Hello! I'm a assembler by Zorroxied(c)\n"
	        "Date of compilation - " __DATE__ "   " __TIME__ "\n\n"
			"If you want to work with me, you must save\n"
			"save the program in the file 'memory.txt'.\n"
			"And put it at the directory, where is situated 'disasm.exe'.\n\n");
}

//------------------------------------------------------------------------------

int Go_Assemle( FILE* Source_Code )
{
	char Bin_Out[] = "binfile.zrx";
	
	FILE* Binary_Out = fopen ( Bin_Out, "wb+" );
	
	char   cmd_cache[5]   = "";
	double data_cache     =  0;
	int    cmd_code       =  0;

	
	while ( !(fscanf ( Source_Code, "%s", &cmd_cache ) == EOF) )
	{

		//----------------------------------------------------------------------
		if( !(strcmp( cmd_cache, "nop" )) )
		{
			cmd_code = _nop;
			fwrite( &cmd_code , sizeof( cmd_code ) , 1, Binary_Out );
			
		}
		//----------------------------------------------------------------------
		if( !(strcmp( cmd_cache, "push" )) )
		{
			cmd_code = _push;
			fwrite( &cmd_code ,   sizeof( cmd_code ), 1, Binary_Out );
			fscanf ( Source_Code, "%lf", &data_cache );
			fwrite( &data_cache , sizeof(data_cache), 1, Binary_Out );
		}
		//----------------------------------------------------------------------
		if( !(strcmp( cmd_cache, "pop" )) )
		{
			cmd_code = _pop;
			fwrite( &cmd_code , sizeof( cmd_code ) , 1, Binary_Out );
			
		}	
		//----------------------------------------------------------------------		 
		if( !(strcmp( cmd_cache, "end" )) )
		{
			cmd_code = _end;
			fwrite( &cmd_code , sizeof( cmd_code ) , 1, Binary_Out );
		//	printf("%d\n", ferror(Binary_Out));
		}	 
		//----------------------------------------------------------------------
		if( !(strcmp( cmd_cache, "dump" )) )
		{
			cmd_code = _dump;
			fwrite( &cmd_code , sizeof( cmd_code ) , 1, Binary_Out );
		}   		
		//----------------------------------------------------------------------

	}
//	printf("%s\n", &cmd_cache );
		
		fclose ( Binary_Out  );
}

//------------------------------------------------------------------------------
