///  \brief         Research of the sscanf function 
///	
///  \description      
///  \author		    Крепак zorroxied Виталий 016 ФРТК

#include <stdio.h>
#include <windows.h>

//------------------------------------------------------------------------------

 
int main()
{
	char str[81] = "";
	long double i = 0;	
	
	sscanf("", "%s %LE", str, &i);
	printf("%s %.16LE\n", str, i);
	
	
	system("PAUSE");
	return 0;
}

