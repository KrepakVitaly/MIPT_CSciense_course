/** ********************************************************************************
 @file    CPU Ass.c
 @date    2013-11-09 12:45
 @author  Denis Prokopenko <denis.prokopenko@frtk.ru>

 Процессор - начало

 @warning Максимальный размер STACK = 20
 ************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
// Организуй работу с библиотеками так, как я рассказывал
//http://ru.wikipedia.org/wiki/%D0%97%D0%B0%D0%B3%D0%BE%D0%BB%D0%BE%D0%B2%D0%BE%D1%87%D0%BD%D1%8B%D0%B9_%D1%84%D0%B0%D0%B9%D0%BB
#include "stack.c"


#define ASSERT_OK(cond) if (!(cond))                                       \
                        {                                                  \
                            printf ( "All is bad: %s; file %s; line %d\n", \
                                    # cond, __FILE__, __LINE__);           \
                            abort();                                       \
                        }
void HELP();
int iSwitch(ST *s,int k);
int iRead();
int iCmp ();

int main()
{
    HELP();
    iRead();
}
/** ********************************************************************************
 HELP - выводит информацию по командам
 ************************************************************************************/
void HELP()
{
    printf ("Push x  - AVAILABLE      To keep a number x > 0 - \n"
            "Pop     - AVAILABLE      To delete/turn out the upper number from STACK\n"
            "Add     - NOT AVAILABLE  To sum up 2 upper numbers\n"
            "Mul     - NOT AVAILABLE  To multiply 2 upper numbers\n"
            "Print   - AVAILABLE      To print upper number from STACK\n"
            "Exit    - AVAILABLE      Exit\n");
}

/** ********************************************************************************
 iRead - считывание команд с консоли
 ************************************************************************************/

int iRead()
{
    ST s;

    while (1)
    {
        int i = 0;
        char c = '\0';
        char data[10] = {'\0'};
        while (((c = getchar()) != ' ') && ( c != '\n') && ( c != '\0') && ( c != EOF))
        {
            data [i]=c;
            i++;
        }
        iSwitch( &s, iCmp(&data[0]));
        if( c == EOF) exit (0);
    }
}

/** ********************************************************************************
 iCmp - перевод команды в число
 ************************************************************************************/

int iCmp (char * s)
{
    if (!((strncmp (s,  "push", 4))))return 1;
    if (!((strncmp (s,   "pop", 3)))) return 2;
    if (!((strncmp (s, "print", 5)))) return 3;
    if (!((strncmp (s, "exit", 4)))) return -1;
}

/** ********************************************************************************
 iSwitch - выполнение команды по её номеру
 ************************************************************************************/

int iSwitch(ST *s, int k)
{
  printf ("I'm in iSwitch k = %d\n", k);
    int N = 0;
    switch (k)
    {
    case 1:
        scanf ("%d", &N);
        Push( s, N);          //Программа ломается на вызове функции push( ST * s, int N)

        break;
    case 2:
        Pop( s);
        break;
    case 3:
        N = Pop( s);          //Программа ломается на вызове функции pop( ST * s)
        if (N != 0xBADBEEF)
        {
            printf ("%lg", N);
            Push ( s, N);
        }
        break;
    case -1:
        exit(0);
        break;
    default:
        printf("THIS IS ERROR!!!\n");
        break;
    }
    
     printf ("I'm ended iSwitch\n");
}











