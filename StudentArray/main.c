#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int const Size = 15;


//------------------------------------------------------------------------------
struct Students
       {
       char  Surname[15];
       int Day,
           Month,
           Year;   
       };
//------------------------------------------------------------------------------


int main()
{
    
    struct Students Stud[10]={};
    int i=0;
    for(i;i<10;i++)
     { 
     strcpy (Stud[i].Surname , "Ivanov"); 
     Stud[i].Day = i; 
     Stud[i].Month = i; 
     Stud[i].Year=i+1990;
     }
    

    FILE* input = fopen("input.txt","r");
    FILE* output = fopen("output.txt","w");

for(i = 0; i <10 ; i++)
fscanf(input, "\%s \%i", Stud[0].Surname, &Stud[0].Day);

    
for( i = 0 ; i <10 ; i++)
   { 
   printf("Student - \%s    Birthday \%i\\\%i\\\%i\n",
   Stud[i].Surname,  Stud[i].Day,  Stud[i].Month,   Stud[i].Year);
   }
    
  fclose(output);
  fclose(input);
  
  system("PAUSE");	
  return 0;
}
