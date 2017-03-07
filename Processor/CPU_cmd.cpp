///  \brief           Command for Virtual Preprocessor v0.1
///
///  
///  \author		    Крепак zorroxied Виталий 016 ФРТК


#include "instr_set.cpp"


//------------------------------------------------------------------------------
//------Constants---------------------------------------------------------------

int const NO_CALLING_FUNC  = -1;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*! \function  Nop_CPU
    \brief Функция, ни делающая ничего. Сделана на всякий случай.
*/
void Nop_CPU ( Stack_t* CPU_Calc_Stack )
{
	return;
}

//------------------------------------------------------------------------------
/*! \Pop_CPU
    \brief  

    Функция, вытаскивающая элемент из стека, и возвращающая его значение, 
    если функция вызвана пользователем, то значение печатается на экран.
    В случае, если стек пуст, то в сообщении об ошибке печатается код вызвавшей 
	функции (см. Instr_set.cpp), если функция вызвана пользователем, 
	то возвращается -1 (NO_CALLING_FUNC).
*/
double Pop_CPU ( Stack_t* CPU_Calc_Stack, int fun_code = NO_CALLING_FUNC )
{
		
	if ( Check_Damage (CPU_Calc_Stack) || CPU_Calc_Stack->pointer ==  0 ) 
	    printf ("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"
				"##Attention! Warning! The danger of total extermination!\n\n"
	    
				"##Error of pointer in Pop. I can't pop anything.\n" 
				"##Calling function is: %d\n"
	            "----------------------------------------------------------------\n"
				, fun_code ); 
	 
    assert( !(Check_Damage (CPU_Calc_Stack) || CPU_Calc_Stack->pointer ==  0) );	
	
	double _out_value = Pop( CPU_Calc_Stack );
	if (fun_code == NO_CALLING_FUNC) 
		return printf("I've popped the value = %lf\n", _out_value);

	return _out_value;
}

//------------------------------------------------------------------------------
/*! \class fn
    \brief Push_CPU

    Функция, которая кладет переданное ей значение в стек.     
    Если произошло переполнение стека, то выводится сообщение об ошибке.
    При этом возвращается код вызвавшей функции (см. Instr_set.cpp), 
	если функция вызвана пользователем, то возвращается -1 (NO_CALLING_FUNC).
*/

void   Push_CPU ( Stack_t* CPU_Calc_Stack, 
				  double   input_value, 
				  int      fun_code = NO_CALLING_FUNC )
{
	if (Check_Damage (CPU_Calc_Stack)) 
		 printf ("##Attention! Warning!\n\n"
	    
				"##Detected damage of stack.\n" 
				"##Calling function is: %d\n"
	            "----------------------------------------------------------------\n"
				, fun_code ); 
	
	if (CPU_Calc_Stack->pointer == 
		CPU_Calc_Stack->Size_of_Stack + (int)CPU_Calc_Stack->Begin_Stack - 1 )
		 
	    printf ("##Attention! Warning!\n\n"
	    
				"##Stack Overflow.\n" 
				"##Calling function is: %d\n"
	            "----------------------------------------------------------------\n"
				, fun_code ); 	 
    assert( !(Check_Damage (CPU_Calc_Stack)) );
  
    assert( !(CPU_Calc_Stack->pointer == CPU_Calc_Stack->Size_of_Stack + (int)CPU_Calc_Stack->Begin_Stack - 1 ) );	
			  
	
	Push ( CPU_Calc_Stack, input_value );

	return;
}

//------------------------------------------------------------------------------
/*! \class fn
    \brief Dup_CPU

    Функция, дублирующая последний элемент в стеке.          
*/

void   Dup_CPU ( Stack_t* CPU_Calc_Stack )
{
	double t = Pop_CPU ( CPU_Calc_Stack, _dup );
	
	Push_CPU ( CPU_Calc_Stack, t, _dup );
	Push_CPU ( CPU_Calc_Stack, t, _dup );
	
	return;
}

//------------------------------------------------------------------------------
/*! \class fn
    \brief Swap_CPU

    Функция, меняющая местами два последних элемента стека.          
*/
void   Swap_CPU ( Stack_t* CPU_Calc_Stack )
{
	double one = Pop_CPU ( CPU_Calc_Stack, _swap );
	double two = Pop_CPU ( CPU_Calc_Stack, _swap );
	
	Push_CPU (CPU_Calc_Stack, one, _swap );
	Push_CPU (CPU_Calc_Stack, two, _swap );
	
	return;
}

//------------------------------------------------------------------------------
/*! \class fn
    \brief Add_CPU

    Функция, складывающая два послених элемента в стеке,
	и возвращающая результат в стек          
*/
void   Add_CPU ( Stack_t* CPU_Calc_Stack )
{
	double one = Pop_CPU ( CPU_Calc_Stack, _add );
	double two = Pop_CPU ( CPU_Calc_Stack, _add );
	
	Push_CPU (CPU_Calc_Stack, one+two, _add );
	
	return;
}

//------------------------------------------------------------------------------
/*! \class fn
    \brief Sub_CPU

    Функция, вычитающая из последнего элемента стека предпоследний
	и возвращающая результат в стек.          
*/
void   Sub_CPU ( Stack_t* CPU_Calc_Stack )
{
	double one = Pop_CPU ( CPU_Calc_Stack, _sub );
	double two = Pop_CPU ( CPU_Calc_Stack, _sub );
	
	Push_CPU (CPU_Calc_Stack, one-two, _sub );
	
	return;
}
//------------------------------------------------------------------------------
/*! \class fn
    \brief Mul_CPU

    Функция, умножающая последний элемент стека на предпоследний
	и возвращающая результат в стек.          
*/
void   Mul_CPU ( Stack_t* CPU_Calc_Stack )
{
	double one = Pop_CPU ( CPU_Calc_Stack, _mul );
	double two = Pop_CPU ( CPU_Calc_Stack, _mul );
	
	Push_CPU (CPU_Calc_Stack, one*two, _mul );
	
	return;
}
//------------------------------------------------------------------------------
/*! \class fn
    \brief Div_CPU

    Функция, делящая последний элемент стека на предпоследний
	и возвращающая результат в стек.          
*/
void   Div_CPU ( Stack_t* CPU_Calc_Stack )
{
	double one = Pop_CPU ( CPU_Calc_Stack, _div );
	double two = Pop_CPU ( CPU_Calc_Stack, _div );
	
	Push_CPU (CPU_Calc_Stack, one/two, _div );
	
	return;
}

//------------------------------------------------------------------------------
/*! \class fn
    \brief Pow_CPU

    Функция, возводящая предпоследний элемент стека в стпень, которая
	лежит в последнем элементе 
	и возвращающая результат в стек.        
*/
void   Pow_CPU ( Stack_t* CPU_Calc_Stack )
{
	double exp   = Pop_CPU ( CPU_Calc_Stack, _pow );
	double base  = Pop_CPU ( CPU_Calc_Stack, _pow );

	base = pow ( base, exp );
	Push_CPU (CPU_Calc_Stack, base, _pow );	
	
	return;
}

//------------------------------------------------------------------------------
/*! \class fn
    \brief Sqrt_CPU

    Функция, извлекающая корень из последнего элемента в стеке
	и возвращающая результат в стек.        
*/
void   Sqrt_CPU ( Stack_t* CPU_Calc_Stack )
{
	double one = Pop_CPU ( CPU_Calc_Stack, _sqrt );
	
	Push_CPU (CPU_Calc_Stack, sqrt(one), _sqrt );
	
	return;
}

//------------------------------------------------------------------------------
/*! \class fn
    \brief Sin_CPU

    Функция, возвращающая синус последнего элемента в стек.       
*/
void   Sin_CPU ( Stack_t* CPU_Calc_Stack )
{
	double one = Pop_CPU ( CPU_Calc_Stack, _sin );
	
	Push_CPU (CPU_Calc_Stack, sin(one), _sin );
	
	return;
}

//------------------------------------------------------------------------------
/*! \class fn
    \brief Sin_CPU

    Функция, возвращающая косинус последнего элемента в стек.       
*/
void   Cos_CPU ( Stack_t* CPU_Calc_Stack )
{
	double one = Pop_CPU ( CPU_Calc_Stack, _cos );
	
	Push_CPU (CPU_Calc_Stack, cos(one), _cos );
	
	return;
}

//------------------------------------------------------------------------------
/*! \class fn
    \brief Call_CPU
	
    Функция, вызвающая функцию описанную пользователем в своей программе,
	записывает адрес возврата в стек адресов (CPU_Addrs_Stack)   
*/
void Call_CPU ( int* cmd_counter, Stack_t* CPU_Addrs_Stack, double addr )
{
//	printf("I was called at %d to %lf\n", *cmd_counter, addr);
	Push_CPU ( CPU_Addrs_Stack, (double) (*cmd_counter+2), _call );
//	printf("I was saved addr = %d\n", *cmd_counter+2);
	
	
	*cmd_counter = (int) addr-2;
	
	if ( *cmd_counter < -1 || *cmd_counter >= PROG_MEMORY_SIZE ) 
	    printf ("Error of cmd_counter in Call. Incorrect addr.\n"
	            "----------------------------------------------------------------\n");
    assert( !(*cmd_counter < -1) );
    assert( !(*cmd_counter >= PROG_MEMORY_SIZE) );
    
	return;
}

//------------------------------------------------------------------------------
/*! \class fn
    \brief Ret_CPU
	
    Функция, которая возвращает программу в место памяти, 
	откуда была вызвана функция (см. Call_CPU)   
*/
void Ret_CPU ( int* cmd_counter, Stack_t* CPU_Addrs_Stack)
{
	*cmd_counter = (int) Pop ( CPU_Addrs_Stack ) - 1;
//	printf("I was restored cmd_count to %d\n", *cmd_counter );
	return;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*! \class fn
    \brief Jmp_CPU
	
    Функция, которая перемещает программу на указанный адрес.  
*/
void Jmp_CPU ( int* cmd_counter, double addr )
{
	*cmd_counter = (int) addr - 2;
//	printf( "cmd_counter = %d\n", *cmd_counter+1 );

	
	if ( *cmd_counter < -1 || *cmd_counter >= PROG_MEMORY_SIZE ) 
	    printf ("Error of cmd_counter in Jmp. Incorrect addr.\n"
	            "----------------------------------------------------------------\n");
    assert( !(*cmd_counter < -1) );
    assert( !(*cmd_counter >= PROG_MEMORY_SIZE) );
		
	return;
}

//------------------------------------------------------------------------------
/*! \class fn
    \brief Ja_CPU
	
    Функция, которая перемещает программу на указанный адрес,
	если последний элемент стека больше предыдущего. 
*/	    	
void Ja_CPU  ( int* cmd_counter, Stack_t* CPU_Calc_Stack, double addr )
{
	if ( *cmd_counter < -1 || *cmd_counter >= PROG_MEMORY_SIZE ) 
	    printf ("Error of cmd_counter in Ja. Incorrect addr.\n"
	            "----------------------------------------------------------------\n");
    assert( !(*cmd_counter < -1 ) );
    assert( !(*cmd_counter >= PROG_MEMORY_SIZE) );
	
	
	double  Oper_1 = Pop_CPU ( CPU_Calc_Stack, _ja );
	double  Oper_2 = Pop_CPU ( CPU_Calc_Stack, _ja );
	
	if ( Oper_1 > Oper_2 ) *cmd_counter = (int) addr - 2; 
//	printf( "cmd_counter = %d\n", *cmd_counter+1 );
	

	Push_CPU ( CPU_Calc_Stack, Oper_2, _ja );
	Push_CPU ( CPU_Calc_Stack, Oper_1, _ja );
	
	return;
}

//------------------------------------------------------------------------------
/*! \class fn
    \brief Jb_CPU
	
    Функция, которая перемещает программу на указанный адрес,
	если последний элемент стека меньше предыдущего. 
*/	  	    		    	
void Jb_CPU  ( int* cmd_counter, Stack_t* CPU_Calc_Stack, double addr )
{
	
	if ( *cmd_counter < -1 || *cmd_counter >= PROG_MEMORY_SIZE ) 
	    printf ("Error of cmd_counter in Jb. Incorrect addr.\n"
	            "----------------------------------------------------------------\n");
    assert( !(*cmd_counter < -1) );	
    
    assert( !(*cmd_counter >= PROG_MEMORY_SIZE) );
    
	double Oper_1 = Pop_CPU ( CPU_Calc_Stack, _jb );
	double Oper_2 = Pop_CPU ( CPU_Calc_Stack, _jb );	
	
	if ( Oper_1 < Oper_2 ) *cmd_counter = (int) addr - 2;

//	printf( "cmd_counter = %d\n", *cmd_counter+1 );

	
	Push_CPU ( CPU_Calc_Stack, Oper_2, _jb );
	Push_CPU ( CPU_Calc_Stack, Oper_1, _jb );
		
	return;
}

//------------------------------------------------------------------------------
/*! \class fn
    \brief Je_CPU
	
    Функция, которая перемещает программу на указанный адрес,
	если последний элемент стека равен предыдущему. 
*/	    		    	    		    	
void Je_CPU  ( int* cmd_counter, Stack_t* CPU_Calc_Stack, double addr )
{
		
	if ( *cmd_counter < -1 || *cmd_counter >= PROG_MEMORY_SIZE ) 
	    printf ("Error of cmd_counter in Je. Incorrect addr.\n"
	            "----------------------------------------------------------------\n");
    assert( !(*cmd_counter < -1) );
    assert( !(*cmd_counter >= PROG_MEMORY_SIZE) );
    
	double Oper_1 = Pop_CPU ( CPU_Calc_Stack, _je );
	double Oper_2 = Pop_CPU ( CPU_Calc_Stack, _je );	
	
	if ( Oper_1 == Oper_2 ) *cmd_counter = (int) addr - 2;
//	printf( "cmd_counter = %d\n", *cmd_counter+1 );

    
	Push_CPU ( CPU_Calc_Stack, Oper_2, _je );
	Push_CPU ( CPU_Calc_Stack, Oper_1, _je );
			
	return;
}

//------------------------------------------------------------------------------
/*! \class fn
    \brief Jne_CPU
	
    Функция, которая перемещает программу на указанный адрес,
	если последний элемент стека не равен предыдущему. 
*/	    		    		    	
void Jne_CPU ( int* cmd_counter, Stack_t* CPU_Calc_Stack, double addr )
{
	if ( *cmd_counter < -1 || *cmd_counter >= PROG_MEMORY_SIZE ) 
	    printf ("Error of cmd_counter in Jne. Incorrect addr.\n"
	            "----------------------------------------------------------------\n");
    assert( !(*cmd_counter < -1) );
    assert( !(*cmd_counter >= PROG_MEMORY_SIZE) );
		
	double Oper_1 = Pop_CPU ( CPU_Calc_Stack, _jne );
	double Oper_2 = Pop_CPU ( CPU_Calc_Stack, _jne );	
	
	if ( Oper_1 != Oper_2 ) *cmd_counter = (int) addr - 2;

//	printf( "cmd_counter = %d\n", *cmd_counter );
    
	Push_CPU ( CPU_Calc_Stack, Oper_2, _jne );
	Push_CPU ( CPU_Calc_Stack, Oper_1, _jne );
		
	return;
}

//------------------------------------------------------------------------------
