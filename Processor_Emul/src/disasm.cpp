///  \brief           Disassembler for Virtual_Preprocessor v0.1
///
///  
///  \author		    Крепак zorroxied Виталий 016 ФРТК

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "instr_set.cpp"


//------------------------------------------------------------------------------
//------Constants---------------------------------------------------------------

int const NULLS  = 2;

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//---------Functions_Prototypes-------------------------------------------------

void Greeting();

int Go_Disassemle( FILE* Machine_Code );

//------------------------------------------------------------------------------


int main()
{
	Greeting();
	
	char Bin_File[]  = "binfile.zrx";
	
	FILE* Machine_Code = fopen ( Bin_File, "rb" );
	if ( !Machine_Code ) 
		return printf ("I can't find file with the machine code '%s'", Bin_File), 1;
	
	Go_Disassemle( Machine_Code );

	fclose ( Machine_Code );

	system("PAUSE");	
	return 0;
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

void Greeting()
{
	printf ("\n------------------------------------------------------------------\n");
	printf ("Hello! I'm a disassembler by Zorroxied(c)\n"
	        "Date of compilation - " __DATE__ "   " __TIME__ "\n\n"
			"If you want to work with me, you must save\n"
			"save the program in the file 'memory.txt'.\n\n");
		//	"And put it at the directory, where is situated 'disasm.exe'.\n\
}

//------------------------------------------------------------------------------

int Go_Disassemle( FILE* Machine_Code )
{
	char DisAsm_Result[] = "DisAsm_Result.txt";
	
	FILE* DisAsm_out = fopen ( DisAsm_Result, "w+" );
	
	unsigned char cmd_cache   = 0;
	int    cmd_counter = 0;
	double data_cache  = 0;
	
	while ( fread ( &cmd_cache , sizeof(cmd_cache), 1, Machine_Code ) )
	{
		
		
		switch ( cmd_cache )
		{
			case _nop  : fprintf ( DisAsm_out, "%0*d:  nop\n" , NULLS, cmd_counter );
						 break;

			case _push : fprintf ( DisAsm_out, "%0*d:  push " , NULLS, cmd_counter );
						 fread ( &data_cache , sizeof(data_cache), 1, Machine_Code );
						 cmd_counter++; 
						 fprintf ( DisAsm_out, "%lf\n", data_cache);
						 break;
						 
	    	case _pop  : fprintf ( DisAsm_out, "%0*d:  pop\n" , NULLS, cmd_counter );
			 			 break;
			 			 
	    	case _clr  : fprintf ( DisAsm_out, "%0*d:  clear\n",NULLS, cmd_counter );
						 break;
			
	    	case _ok   : fprintf ( DisAsm_out, "%0*d:  ok\n",   NULLS, cmd_counter );
						 break;
			
	    	case _dump : fprintf ( DisAsm_out, "%0*d:  dump\n", NULLS, cmd_counter );
						 break;
			
	    	case _dup  : fprintf ( DisAsm_out, "%0*d:  dup\n",  NULLS, cmd_counter );
					   	 break;
			
	    	case _swap : fprintf ( DisAsm_out, "%0*d:  swap\n", NULLS, cmd_counter );
						 break;
			
	    	case _add  : fprintf ( DisAsm_out, "%0*d:  add\n",  NULLS, cmd_counter );
					  	 break;
			
			case _mul  : fprintf ( DisAsm_out, "%0*d:  mul\n",  NULLS, cmd_counter );
						 break;
			
	    	case _sub  : fprintf ( DisAsm_out, "%0*d:  sub\n",  NULLS, cmd_counter );
						 break;
			
	    	case _div  : fprintf ( DisAsm_out, "%0*d:  div\n",  NULLS, cmd_counter );
						 break;
			
	    	case _pow  : fprintf ( DisAsm_out, "%0*d:  pow\n",  NULLS, cmd_counter );
						 break;
			
	    	case _sqrt : fprintf ( DisAsm_out, "%0*d:  sqrt\n", NULLS, cmd_counter );
						 break;
			
	    	case _sin  : fprintf ( DisAsm_out, "%0*d:  sin\n",  NULLS, cmd_counter );
				 		 break;
			
	    	case _cos  : fprintf ( DisAsm_out, "%0*d:  cos\n",  NULLS, cmd_counter );
						 break;
	    	
	    	
    	    case _call : fprintf ( DisAsm_out, "%0*d:  call ",  NULLS, cmd_counter );
						 fread ( &data_cache , sizeof(data_cache), 1, Machine_Code );
						 cmd_counter++;  
						 fprintf ( DisAsm_out, "%lf\n", data_cache);
						 break;
						 
	    	case _ret  : fprintf ( DisAsm_out, "%0*d:  ret\n",  NULLS, cmd_counter );
						 break;
	    	
	    	case _jmp  : fprintf ( DisAsm_out, "%0*d:  jmp ",   NULLS, cmd_counter );
						 fread ( &data_cache , sizeof(data_cache), 1, Machine_Code );
						 cmd_counter++;  
						 fprintf ( DisAsm_out, "%lf\n", data_cache);
						 break;
						 
	    	case _ja   : fprintf ( DisAsm_out, "%0*d:  ja   ",  NULLS, cmd_counter );
						 fread ( &data_cache , sizeof(data_cache), 1, Machine_Code );
						 cmd_counter++;  
						 fprintf ( DisAsm_out, "%lf\n", data_cache);
						 break;
						 
	    	case _jb   : fprintf ( DisAsm_out, "%0*d:  jb ",    NULLS, cmd_counter );
						 fread ( &data_cache , sizeof(data_cache), 1, Machine_Code );
						 cmd_counter++ 
						 fprintf ( DisAsm_out, "%lf\n", data_cache);
						 break;
						 
	    	case _je   : fprintf ( DisAsm_out, "%0*d:  je ",    NULLS, cmd_counter );
						 fread ( &data_cache , sizeof(data_cache), 1, Machine_Code );
						 cmd_counter++;  
						 fprintf ( DisAsm_out, "%lf\n", data_cache);
						 break;
						 
	    	case _jne  : fprintf ( DisAsm_out, "%0*d:  jne ",   NULLS, cmd_counter );
						 fread ( &data_cache , sizeof(data_cache), 1, Machine_Code );
						 cmd_counter++;  
						 fprintf ( DisAsm_out, "%lf\n", data_cache);
						 break;
						 
	    	case _end  : fprintf ( DisAsm_out, "%0*d:  end\n",  NULLS, cmd_counter );
						 break;
		}
		cmd_counter++;
	}

	return 0;

}

//------------------------------------------------------------------------------
