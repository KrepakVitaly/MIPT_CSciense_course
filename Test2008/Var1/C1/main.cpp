//Вариант 1 
//Задача С
//Удаление лишних пробелов
//Крепак Виталий 016 гр ФРТК
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

const int BUFSIZE = 512;

int main (int argc, char *argv[])
{
  printf ("Hello! I am a program for finding and deleting the unnessesary gaps.\n"
  		 " (c)zorroxied \n"
	     "Date - " __DATE__ " " __TIME__ "\n\n"
	     "Now I am find and delete unnessesary gaps.\n"
	     "Process progress:\n\n");

for ( int i = 0 ; i < 20 ; i++ ) { Sleep (100); printf ("#"); };
printf ("\n\nCongratulations!\n\n");
  
  FILE* input  = fopen ( "input.txt",  "r" );
  FILE* output = fopen ( "output.txt", "w" );
  
  char Bufer = 'a';
  
  
  int Gap_Detect = 0;
  
  while ( ( (Bufer = getc ( input ) ) != EOF) ) 
        {
            
        if ( (Bufer == ' ') && ( Gap_Detect == 0 ) ) 
             { 
             putc ( ' ', output ); 
             Gap_Detect = 1;
             }
        if ( Bufer != ' ' ) 
             {
             putc ( Bufer, output );
             Gap_Detect = 0;
             }
        }
              
  fclose ( input );
  fclose ( output );
  
  system ("PAUSE");	
  return 0;
}
