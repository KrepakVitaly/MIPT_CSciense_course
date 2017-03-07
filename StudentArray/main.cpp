#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int const Size = 15;
int const NStud = 8;

struct Students
       {
       char  Surname[Size];
       int   Day,
             Month,
             Year;   
       };
       
       
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

void Write_List_Students ( FILE* input, struct Students Stud[] );

void Load_List_Students ( FILE* input, struct Students Stud[] );

void Init_Students_List ( struct Students Stud[] );

void Sort_Students_by_Name ( struct Students Stud[] );

int Compare_Students_By_Name ( const void* aa,const void* bb );

void Sort_Students_by_Date ( struct Students Stud[] );

int Compare_Students_By_Date ( const void* aa,const void* bb );

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


int main()
{
    
    struct Students Stud[NStud] = {};
    
    Init_Students_List ( Stud );

    const char* input_txt = "input.txt";
    FILE* input = fopen ( input_txt,"r" );
//  FILE* output = fopen ( "output.txt","w" );
    if ( !input ) return perror ("Error"), printf ("I can't find '%s'", input_txt), 1;

/*    Load_List_Students ( input, Stud );
    
    Write_List_Students ( input, Stud );
    
    printf ( "\n" );*/    
    
    Sort_Students_by_Date ( Stud );
    
    Write_List_Students ( input, Stud );
    
    printf ( "\n" );

    Sort_Students_by_Name ( Stud );
    
    Write_List_Students ( input, Stud );
        

    
//  fclose ( output );
    fclose ( input );
  
    system ( "PAUSE" );	
    return 0;
}







//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

void Write_List_Students ( FILE* input, struct Students Stud[] )//* (Stud[i].Surname) 
{
     
     for ( int i = 0 ; i < NStud ; i++ )
             printf ( "Student - \%s    Birthday \%i\\\%i\\\%i\n",
                       Stud[i].Surname,
                       Stud[i].Day,
                       Stud[i].Month,
                       Stud[i].Year );
   
}


//------------------------------------------------------------------------------



void Load_List_Students ( FILE* input, struct Students Stud[] )
{
     for ( int i = 0; i < NStud ; i++ )
     fscanf ( input, "\%s \%i \%i \%i",  Stud[i].Surname, &Stud[i].Day, 
                                       &Stud[i].Month,   &Stud[i].Year );
}



//-----------------------------------------------------------------------------


void Init_Students_List ( struct Students Stud[] )
{
    for ( int i = 0 ; i < NStud ; i++ )
     { 
     strcpy ( Stud[i].Surname , "" ); 
     
     Stud[i].Day   = 0; 
     Stud[i].Month = 0; 
     Stud[i].Year  = 0;
     }
}


//------------------------------------------------------------------------------

void Sort_Students_by_Name ( struct Students Stud[] )
{
     qsort ( Stud, NStud, sizeof ( Stud[0] ), &Compare_Students_By_Name );   
}

//------------------------------------------------------------------------------

int Compare_Students_By_Name ( const void* aa, const void* bb )
{
    const Students* a = ( const Students* ) aa;
    const Students* b = ( const Students* ) bb;
    
    return strcmp ( a->Surname, b->Surname );
         
}

//------------------------------------------------------------------------------

void Sort_Students_by_Date ( struct Students Stud[] )
{
     qsort ( Stud, NStud, sizeof ( Stud[0] ), &Compare_Students_By_Date );   
}

//------------------------------------------------------------------------------

int Compare_Students_By_Date ( const void* aa, const void* bb )
{
    const Students* a = ( const Students* )aa;
    const Students* b = ( const Students* )bb;
        
    return ( a->Day + a->Month*100 + a->Year*10000 - 
             b->Day - b->Month*100 - b->Year*10000 );
}

//------------------------------------------------------------------------------
