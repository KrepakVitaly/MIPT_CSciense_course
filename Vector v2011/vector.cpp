 //------------------------------------------------------------------------------
///  \brief 			Vector's exersize         
///  \date				18.09.2011
///  \description      
///  \author		    Крепак zorroxied Виталий 016 ФРТК
//------------------------------------------------------------------------------

#include <stdio.h>
#include <iostream>
#include <assert.h>
#include <windows.h>

//------------------------------------------------------------------------------
//------ "Global" Constants ----------------------------------------------------

int const THE_END_OF_WAY = 137;
int const STILL_ALIVE    =   0;

int const karma_ = 3;

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//--------------------- My Classes ---------------------------------------------
/*! \class fn
    \brief 
*/    

class Demont
	{
	//Content
		int soul_;
		int acts_;	
	
	//Functions	
	public:
		int Assign_Value ( int input );
		int	Get_Value    ();
		Demont();
		~Demont();
	};
	
//------------------------------------------------------------------------------
Demont::Demont():
	soul_(0), acts_(0)
	{
		printf("I'm reborn.\n");
	}
//------------------------------------------------------------------------------
Demont::~Demont()
	{
		soul_ = 0xDEAD;
		acts_ = -666;
		printf("I'm dead.\n");
	}
//------------------------------------------------------------------------------
int Demont::Assign_Value( int input )
	{
		assert(this);
		assert( acts_ != -666 );
		
		if ( karma_ == acts_ )
			{
				printf("This is end of my way. Way of Int.\n");
				printf("Now I'm a spirit. My edges are diffused.\n");
				printf("And you can't recognize my value with confidence.\n\n");
				return THE_END_OF_WAY;
			}
			
		soul_ = input;
		acts_++;
		
		return STILL_ALIVE;
	}
//------------------------------------------------------------------------------
int	Demont::Get_Value ()
	{
		assert(this);
		assert( acts_ != -666 );
		
		return soul_;
	}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

using namespace std;

int main()
	{
		Demont ghost;
		int i = 0;
		
		for ( i = 0 ; i < 5; i++ )
			{
			ghost.Assign_Value(i);
			}
			
		i = ghost.Get_Value();
		cout<<i<<endl;
		
		system("PAUSE");
		return 0;
	}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
