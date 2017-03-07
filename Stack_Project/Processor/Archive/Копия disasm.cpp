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


//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//---------Functions_Prototypes-------------------------------------------------

void Greeting();

int Go_Disassemle( FILE* Machine_Code );

//------------------------------------------------------------------------------


int main()
{
	Greeting();
	
	char Bin_File[]  = "memory.txt";
	
	FILE* Machine_Code = fopen ( Bin_File, "r" );
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
	printf ("\n------------------------------------------------------------\n");
	printf ("Hello! I'm a disassembler by Zorroxied(c)\n"
	        "Date of compilation - " __DATE__ "   " __TIME__ "\n\n"
			"If you want to work with me, you must save\n"
			"save the program in the file 'memory.txt'.\n"
			"And put it at the directory, where is situated 'disasm.exe'.\n\n");
}

//------------------------------------------------------------------------------

int Go_Disassemle( FILE* Machine_Code )
{
	char DisAsm_Result[] = "DisAsm_Result.txt";
	
	FILE* DisAsm_out = fopen ( DisAsm_Result, "w+" );
	
	double cmd_cache   =  0;
	int    cmd_counter =  0;
	
	while ( !(fscanf ( Machine_Code, "%lf", &cmd_cache ) == EOF) )
	{
		
		if ( ((int)cmd_cache - cmd_cache) ) {printf("I can't find cmd It's data.\n"); return 1;}
		
		switch ( (int)cmd_cache )
		{
			case _nop  : fprintf ( DisAsm_out, "%d: nop;\n", cmd_counter);
//						 fscanf( Machine_Code, "%lf", &cmd_cache ); 
//						 fprintf ( DisAsm_out, "%lf\n", cmd_cache);
						 break;
						 
			case _push : fprintf ( DisAsm_out, "%d: push ", cmd_counter );
						 fscanf( Machine_Code, "%lf", &cmd_cache );
						 cmd_counter++; 
						 fprintf ( DisAsm_out, "%lf;\n", cmd_cache);
						 break;
						 
	    	case _pop  : fprintf ( DisAsm_out, "%d: pop;\n", cmd_counter );
				//		 fscanf( Machine_Code, "%lf", &cmd_cache ); 
				//		 fprintf ( DisAsm_out, "%lf\n", cmd_cache);break;
			 			 break;
			 			 
	    	case _clear: fprintf ( DisAsm_out, "%d: clear;\n", cmd_counter );
				//		 fscanf( Machine_Code, "%lf", &cmd_cache ); 
				//		 fprintf ( DisAsm_out, "%lf\n", cmd_cache);
						 break;
			
	    	case _ok   : fprintf ( DisAsm_out, "%d: ok;\n", cmd_counter );
				//		 fscanf( Machine_Code, "%lf", &cmd_cache ); 
				//		 fprintf ( DisAsm_out, "%lf\n", cmd_cache);
						 break;
			
	    	case _dump : fprintf ( DisAsm_out, "%d: dump;\n", cmd_counter );
				//		 fscanf( Machine_Code, "%lf", &cmd_cache ); 
				//		 fprintf ( DisAsm_out, "%lf\n", cmd_cache);
						 break;
			
	    	case _dup  : fprintf ( DisAsm_out, "%d: dup;\n", cmd_counter );
				//		 fscanf( Machine_Code, "%lf", &cmd_cache ); 
				//		 fprintf ( DisAsm_out, "%lf\n", cmd_cache);
					   	 break;
			
	    	case _swap : fprintf ( DisAsm_out, "%d: swap;\n", cmd_counter );
				//		 fscanf( Machine_Code, "%lf", &cmd_cache ); 
				//		 fprintf ( DisAsm_out, "%lf\n", cmd_cache);
						 break;
			
	    	case _add  : fprintf ( DisAsm_out, "%d: add;\n", cmd_counter );
				//		 fscanf( Machine_Code, "%lf", &cmd_cache ); 
				//		 fprintf ( DisAsm_out, "%lf\n", cmd_cache);
					  	 break;
			
	    	case _sub  : fprintf ( DisAsm_out, "%d: sub;\n", cmd_counter );
				//		 fscanf( Machine_Code, "%lf", &cmd_cache ); 
				//		 fprintf ( DisAsm_out, "%lf\n", cmd_cache);
						 break;
			
	    	case _div  : fprintf ( DisAsm_out, "%d: div;\n", cmd_counter );
				//		 fscanf( Machine_Code, "%lf", &cmd_cache ); 
				//		 fprintf ( DisAsm_out, "%lf\n", cmd_cache);
						 break;
			
	    	case _pow  : fprintf ( DisAsm_out, "%d: pow;\n", cmd_counter );
				//		 fscanf( Machine_Code, "%lf", &cmd_cache ); 
				//		 fprintf ( DisAsm_out, "%lf\n", cmd_cache);
						 break;
			
	    	case _sqrt : fprintf ( DisAsm_out, "%d: sqrt;\n", cmd_counter );
				//   	 fscanf( Machine_Code, "%lf", &cmd_cache ); 
				//		 fprintf ( DisAsm_out, "%lf\n", cmd_cache);
						 break;
			
	    	case _sin  : fprintf ( DisAsm_out, "%d: sin;\n", cmd_counter );
				//		 fscanf( Machine_Code, "%lf", &cmd_cache ); 
				//		 fprintf ( DisAsm_out, "%lf\n", cmd_cache);
				 		 break;
			
	    	case _cos  : fprintf ( DisAsm_out, "%d: cos;\n", cmd_counter );
				//		 fscanf( Machine_Code, "%lf", &cmd_cache ); 
				//		 fprintf ( DisAsm_out, "%lf\n", cmd_cache);
						 break;
	    	
	    	
    	    case _call : fprintf ( DisAsm_out, "%d: call ", cmd_counter );
						 fscanf( Machine_Code, "%lf", &cmd_cache );
						 cmd_counter++;  
						 fprintf ( DisAsm_out, "%lf;\n", cmd_cache);
						 break;
						 
	    	case _ret  : fprintf ( DisAsm_out, "%d: ret;\n", cmd_counter );
				//		 fscanf( Machine_Code, "%lf", &cmd_cache ); 
				//		 fprintf ( DisAsm_out, "%lf\n", cmd_cache);
						 break;
	    	
	    	case _jmp  : fprintf ( DisAsm_out, "%d: jmp;\n", cmd_counter );
						 fscanf( Machine_Code, "%lf", &cmd_cache );
						 cmd_counter++;  
						 fprintf ( DisAsm_out, "%lf;\n", cmd_cache);
						 break;
						 
	    	case _ja   : fprintf ( DisAsm_out, "%d: ja;\n", cmd_counter );
				//		 fscanf( Machine_Code, "%lf", &cmd_cache ); 
				//		 fprintf ( DisAsm_out, "%lf\n", cmd_cache);
						 break;
						 
	    	case _jb   : fprintf ( DisAsm_out, "%d: jb;\n", cmd_counter );
				//		 fscanf( Machine_Code, "%lf", &cmd_cache ); 
				//		 fprintf ( DisAsm_out, "%lf\n", cmd_cache);
						 break;
						 
	    	case _je   : fprintf ( DisAsm_out, "%d: je;\n", cmd_counter );
				//		 fscanf( Machine_Code, "%lf", &cmd_cache ); 
				//		 fprintf ( DisAsm_out, "%lf\n", cmd_cache);
				 		 break;
						 
	    	case _jne  : fprintf ( DisAsm_out, "%d: jne;\n", cmd_counter );
				//		 fscanf( Machine_Code, "%lf", &cmd_cache ); 
				//		 fprintf ( DisAsm_out, "%lf\n", cmd_cache);
						 break;
						 
	    	case _end  : fprintf ( DisAsm_out, "%d: end;\n", cmd_counter );
				//		 fscanf( Machine_Code, "%lf", &cmd_cache ); 
				//		 fprintf ( DisAsm_out, "%lf\n", cmd_cache);
						 break;

		}
		cmd_counter++;
	}
	

	
	return 0;

}

//------------------------------------------------------------------------------
