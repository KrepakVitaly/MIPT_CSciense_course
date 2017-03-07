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

int const UNIT_RECORD       =   1;
int const NUMBER_OF_LABELS  = 100;
int const MAX_LEN_OF_LABEL  =  20;
int const NULL_ADR          =   0;

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
	
	char    *labels[NUMBER_OF_LABELS]      = {};
	char     label_cache[MAX_LEN_OF_LABEL] = "";
	double   label_addr[NUMBER_OF_LABELS]  = {};
	
	int   cmd_counter =  0;
	int   i = 0;
	
	
	while ( (fscanf ( Source_Code, "%s", &label_cache ) != EOF) )
	{
		if ( strstr( label_cache, ":" ) ) 
			{
			labels[i] = (char*) malloc( sizeof(char) * strlen(label_cache) );
	    	printf("Malloc addr = %d\n", (int)labels[i] );
	   		strcpy( labels[i], label_cache  );
			label_addr[i] = cmd_counter;
			i++;
			continue;
			}
		cmd_counter++;
		printf("Cmd_count = %d\n", cmd_counter);
	}
		
	// TODO: free labels	
		
//	for( int x = 0; x< i; x++ )
//	{
//		printf("Label name = %s, adr = %d\n", labels[x], label_addr[x]);
//	}
	
	
	rewind( Source_Code );
	
	
	unsigned char   cmd_code     =  0;		
	double  		 data_cache   =  0;
	char    		 cmd_cache[5] = "";
	
	cmd_counter = 0;
			
	while ( (fscanf ( Source_Code, "%s", &cmd_cache ) != EOF) )
	{
		
	/*	if ( cmd_counter != atoi(cmd_cache) ) 
			{
				fclose ( Binary_Out  );
				printf("End of file or invald numeration of commands.Sorry\n"
						"The invalid number = %d\n", atoi(cmd_cache) );
				return 1;
			}
		
		if (fscanf ( Source_Code, "%s", &cmd_cache ) == EOF) 
			{
				printf("There is no expexting cmd. It's end of file\n");
				return 1;
			}*/
		
		//----------------------------------------------------------------------
		if( !(strcmp( cmd_cache, "nop" )) )
		{
			cmd_code = _nop;
			fwrite( &cmd_code , sizeof( cmd_code ) , 1, Binary_Out );
			cmd_counter++;
			
			continue;
		}
		//----------------------------------------------------------------------
		if( !(strcmp( cmd_cache, "push" )) )
		{
			cmd_code = _push;
			fwrite( &cmd_code ,   sizeof( cmd_code ), 1, Binary_Out );
			cmd_counter++;
			
			fscanf ( Source_Code, "%lf", &data_cache );
			fwrite( &data_cache , sizeof(data_cache), 1, Binary_Out );
			cmd_counter++;
			
			continue;
		}
		//----------------------------------------------------------------------
		if( !(strcmp( cmd_cache, "jb" )) )
		{
			cmd_code = _jb;
			fwrite( &cmd_code ,   sizeof( cmd_code ), 1, Binary_Out );
			cmd_counter++;
			
		//	fscanf ( Source_Code, "%lf", &data_cache );
		//	fwrite( &data_cache , sizeof(data_cache), 1, Binary_Out );
			fscanf ( Source_Code, "%s", &label_cache );
			strcat ( label_cache, ":" );
			
			for( int x = 0; ; x++ )
			{
			
				printf("Inv Label_cache = %s Label x = %s\n", label_cache, labels[x]);
			//	for( int x = 0; x< i; x++ )
			//		{
			//		printf("Label name = %s, adr = %d\n", labels[x], label_addr[x]);
			//		}
								
				if ( labels[x] == NULL_ADR ) 
					{ 
					printf("I can't match label with addr on line %d\n", cmd_counter);
					return -1;
					}
				if ( strcmp( labels[x], label_cache) == 0 )  // TODO: strequ ? macro
					{
					fwrite( &label_addr[x] , sizeof(label_addr[x]), 1, Binary_Out );
					printf("Jumping adress = %lf\n", label_addr[x]);
					break;
					}
				if ( x > NUMBER_OF_LABELS ) 
						printf("Wrong label on line %d\n", cmd_counter);
					assert( !(x > NUMBER_OF_LABELS) );
			}
			cmd_counter++;
			
			continue;
		}
		//----------------------------------------------------------------------
		if( !(strcmp( cmd_cache, "jne" )) )
		{
			cmd_code = _jne;
			fwrite( &cmd_code ,   sizeof( cmd_code ), 1, Binary_Out );
			cmd_counter++;
			
		//	fscanf ( Source_Code, "%lf", &data_cache );
		//	fwrite( &data_cache , sizeof(data_cache), 1, Binary_Out );
		
			fscanf ( Source_Code, "%s", &label_cache );
			strcat ( label_cache, ":" );
			
			for( int x = 0; ; x++ )
			{
			
				printf("Inv Label_cache = %s Label x = %s\n", label_cache, labels[x]);

				if ( labels[x] == NULL_ADR ) 
					{ 
					printf("I can't match label with addr on line %d\n", cmd_counter);
					return -1;
					}
				if ( !strcmp( labels[x], label_cache) )
					{
					fwrite( &label_addr[x] , sizeof(label_addr[x]), 1, Binary_Out );
					printf("Jumping adress = %lf\n", label_addr[x]);
					break;
					}
				if ( x > NUMBER_OF_LABELS ) 
						printf("Wrong label on line %d\n", cmd_counter);
					assert( !(x > NUMBER_OF_LABELS) );
			}
			cmd_counter++;
			
			continue;
		}
		//----------------------------------------------------------------------
		if( !(strcmp( cmd_cache, "ja" )) )
		{
			cmd_code = _ja;
			fwrite( &cmd_code ,   sizeof( cmd_code ), 1, Binary_Out );
			cmd_counter++;
			
		//	fscanf ( Source_Code, "%lf", &data_cache );
		//	fwrite( &data_cache , sizeof(data_cache), 1, Binary_Out );
					fscanf ( Source_Code, "%s", &label_cache );
			strcat ( label_cache, ":" );
			
			for( int x = 0; ; x++ )
			{
			
				printf("Inv Label_cache = %s Label x = %s\n", label_cache, labels[x]);
								
				if ( labels[x] == NULL_ADR ) 
					{ 
					printf("I can't match label with addr on line %d\n", cmd_counter);
					return -1;
					}
				if ( !strcmp( labels[x], label_cache) )
					{
					fwrite( &label_addr[x] , sizeof(label_addr[x]), 1, Binary_Out );
					printf("Jumping adress = %lf\n", label_addr[x]);
					break;
					}
				if ( x > NUMBER_OF_LABELS ) 
						printf("Wrong label on line %d\n", cmd_counter);
					assert( !(x > NUMBER_OF_LABELS) );
			}
			cmd_counter++;
			
			continue;
		}
		//----------------------------------------------------------------------
		if( !(strcmp( cmd_cache, "je" )) )
		{
			cmd_code = _je;
			fwrite( &cmd_code ,   sizeof( cmd_code ), 1, Binary_Out );
			cmd_counter++;
			
			fscanf ( Source_Code, "%s", &label_cache );
			strcat ( label_cache, ":" );
			
			for( int x = 0; ; x++ )
			{
			
				printf("Inv Label_cache = %s Label x = %s\n", label_cache, labels[x]);
	
				if ( labels[x] == NULL_ADR ) 
					{ 
					printf("I can't match label with addr on line %d\n", cmd_counter);
					return -1;
					}
				if ( !strcmp( labels[x], label_cache) )
					{
					fwrite( &label_addr[x] , sizeof(label_addr[x]), 1, Binary_Out );
					printf("Jumping adress = %lf\n", label_addr[x]);
					break;
					}
				if ( x > NUMBER_OF_LABELS ) 
						printf("Wrong label on line %d\n", cmd_counter);
					assert( !(x > NUMBER_OF_LABELS) );
			}
			
// TODO: read D.R.Y.
			
		/*	fscanf ( Source_Code, "%lf", &data_cache );
			fwrite( &data_cache , sizeof(data_cache), 1, Binary_Out );*/
			
			
			cmd_counter++;
			
			continue;
		}
		//----------------------------------------------------------------------
		if( !(strcmp( cmd_cache, "call" )) )
		{
			cmd_code = _call;
			fwrite( &cmd_code ,   sizeof( cmd_code ), 1, Binary_Out );
			cmd_counter++;
			
		//	fscanf ( Source_Code, "%lf", &data_cache );
		//	fwrite( &data_cache , sizeof(data_cache), 1, Binary_Out );
			
			fscanf ( Source_Code, "%s", &label_cache );
			strcat ( label_cache, ":" );
			
			for( int x = 0; ; x++ )
			{
			
				printf("Inv Label_cache = %s Label x = %s\n", label_cache, labels[x]);
			//	for( int x = 0; x< i; x++ )
			//		{
			//		printf("Label name = %s, adr = %d\n", labels[x], label_addr[x]);
			//		}
								
				if ( labels[x] == NULL_ADR ) 
					{ 
					printf("I can't match label with addr on line %d\n", cmd_counter);
					return -1;
					}
				if ( !strcmp( labels[x], label_cache) )
					{
					fwrite( &label_addr[x] , sizeof(label_addr[x]), 1, Binary_Out );
					printf("Jumping adress = %lf\n", label_addr[x]);
					break;
					}
				if ( x > NUMBER_OF_LABELS ) 
						printf("Wrong label on line %d\n", cmd_counter);
					assert( !(x > NUMBER_OF_LABELS) );
			}
			cmd_counter++;
			
			continue;
		}
		
		//----------------------------------------------------------------------
		if( !(strcmp( cmd_cache, "pop" )) )
		{
			cmd_code = _pop;
			fwrite( &cmd_code , sizeof( cmd_code ) , 1, Binary_Out );
			cmd_counter++;
			
			continue;
		}
		//----------------------------------------------------------------------
		if( !(strcmp( cmd_cache, "ret" )) )
		{
			cmd_code = _ret;
			fwrite( &cmd_code , sizeof( cmd_code ) , 1, Binary_Out );
			cmd_counter++;
			
			continue;
		}
		//----------------------------------------------------------------------
		if( !(strcmp( cmd_cache, "pow" )) )
		{
			cmd_code = _pow;
			fwrite( &cmd_code , sizeof( cmd_code ) , 1, Binary_Out );
			cmd_counter++;
			
			continue;
		}
		//----------------------------------------------------------------------
		if( !(strcmp( cmd_cache, "sin" )) )
		{
			cmd_code = _sin;
			fwrite( &cmd_code , sizeof( cmd_code ) , 1, Binary_Out );
			cmd_counter++;
			
			continue;
		}
		//----------------------------------------------------------------------
		if( !(strcmp( cmd_cache, "cos" )) )
		{
			cmd_code = _cos;
			fwrite( &cmd_code , sizeof( cmd_code ) , 1, Binary_Out );
			cmd_counter++;
			
			continue;
		}
		//----------------------------------------------------------------------
		if( !(strcmp( cmd_cache, "clr" )) )
		{
			cmd_code = _clr;
			fwrite( &cmd_code , sizeof( cmd_code ) , 1, Binary_Out );
			cmd_counter++;
			
			continue;
		}
		//----------------------------------------------------------------------
		if( !(strcmp( cmd_cache, "ok" )) )
		{
			cmd_code = _ok;
			fwrite( &cmd_code , sizeof( cmd_code ) , 1, Binary_Out );
			cmd_counter++;
			
			continue;
		}
		//----------------------------------------------------------------------
		if( !(strcmp( cmd_cache, "add" )) )
		{
			cmd_code = _add;
			fwrite( &cmd_code , sizeof( cmd_code ) , 1, Binary_Out );
			cmd_counter++;
			
			continue;
		}
		//----------------------------------------------------------------------
		if( !(strcmp( cmd_cache, "sqrt" )) )
		{
			cmd_code = _sqrt;
			fwrite( &cmd_code , sizeof( cmd_code ) , 1, Binary_Out );
			cmd_counter++;
			
			continue;
		}
		//----------------------------------------------------------------------
		if( !(strcmp( cmd_cache, "div" )) )
		{
			cmd_code = _div;
			fwrite( &cmd_code , sizeof( cmd_code ) , 1, Binary_Out );
			cmd_counter++;
			
			continue;
		}
		//----------------------------------------------------------------------
		if( !(strcmp( cmd_cache, "mul" )) )
		{
			cmd_code = _mul;
			fwrite( &cmd_code , sizeof( cmd_code ) , 1, Binary_Out );
			cmd_counter++;
			
			continue;
		}
		//----------------------------------------------------------------------
		if( !(strcmp( cmd_cache, "sub" )) )
		{
			cmd_code = _sub;
			fwrite( &cmd_code , sizeof( cmd_code ) , 1, Binary_Out );
			cmd_counter++;
			
			continue;
		}
		//----------------------------------------------------------------------
		if( !(strcmp( cmd_cache, "swap" )) )
		{
			cmd_code = _swap;
			fwrite( &cmd_code , sizeof( cmd_code ) , 1, Binary_Out );
			cmd_counter++;
			
			continue;
		}
		//----------------------------------------------------------------------
		if( !(strcmp( cmd_cache, "dup" )) )
		{
			cmd_code = _dup;
			fwrite( &cmd_code , sizeof( cmd_code ) , 1, Binary_Out );
			cmd_counter++;
			
			continue;
		}
		//----------------------------------------------------------------------
		if( !(strcmp( cmd_cache, "sub" )) )
		{
			cmd_code = _sub;
			fwrite( &cmd_code , sizeof( cmd_code ) , 1, Binary_Out );
			cmd_counter++;
			
			continue;
		}		
		//----------------------------------------------------------------------
		if( !(strcmp( cmd_cache, "jmp" )) )
		{
			cmd_code = _jmp;
			fwrite( &cmd_code ,   sizeof( cmd_code ), 1, Binary_Out );
			cmd_counter++;
	
			
			fscanf ( Source_Code, "%s", &label_cache );
			strcat ( label_cache, ":" );
			
			for( int x = 0; ; x++ )
			{
			
				printf("Inv Label_cache = %s Label x = %s\n", label_cache, labels[x]);
			//	for( int x = 0; x< i; x++ )
			//		{
			//		printf("Label name = %s, adr = %d\n", labels[x], label_addr[x]);
			//		}
								
				if ( labels[x] == NULL_ADR ) 
					{ 
					printf("I can't match label with addr on line %d\n", cmd_counter);
					return -1;
					}
				if ( !strcmp( labels[x], label_cache) )
					{
					fwrite( &label_addr[x] , sizeof(label_addr[x]), 1, Binary_Out );
					printf("Jumping adress = %lf\n", label_addr[x]);
					break;
					}
				if ( x > NUMBER_OF_LABELS ) 
						printf("Wrong label on line %d\n", cmd_counter);
					assert( !(x > NUMBER_OF_LABELS) );
			}
		  /*fscanf ( Source_Code, "%lf", &data_cache );
			fwrite( &data_cache , sizeof(data_cache), 1, Binary_Out );*/
			cmd_counter++;
			
			continue;
		}	
		//----------------------------------------------------------------------		 
		if( !(strcmp( cmd_cache, "end" )) )
		{
			cmd_code = _end;
			fwrite( &cmd_code , sizeof( cmd_code ) , 1, Binary_Out );
			cmd_counter++;
		//	printf("%d\n", ferror(Binary_Out));
			continue;
		}	 
		//----------------------------------------------------------------------
		if( !(strcmp( cmd_cache, "dump" )) )
		{
			cmd_code = _dump;
			fwrite( &cmd_code , sizeof( cmd_code ) , 1, Binary_Out );
			cmd_counter++;
			
			continue;
		}   		
		//----------------------------------------------------------------------
		printf("There is no cmd. "
			   "May be it's clear - line %d\n", cmd_counter);

		
		
	}
//	printf("%s\n", &cmd_cache );
		
	fclose ( Binary_Out  );
}
//------------------------------------------------------------------------------
