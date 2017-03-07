/** ********************************************************************************
 @file    stack.c
 @date    2013-11-08 18:45
 @author  Denis Prokopenko <denis.prokopenko@frtk.ru>

 Создание структуры STACK и соответствующих функции

 @warning Максимальный размер STACK = 20
 ************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define SIZE  20

#define ASSERT_OK(cond) if (!(cond))                                       \
                        {                                                  \
                            printf ( "All is bad: %s; file %s; line %d\n", \
                                    # cond, __FILE__, __LINE__);           \
                            abort();                                       \
                        }


typedef struct stack_t ST;

int Construct( ST *s);
int Destruct ( ST *s);
int Dump     ( ST *s);
int OK       ( ST *s);
int Push     ( ST *s, int N);
int Pop   ( ST *s);

/** ********************************************************************************
 Struct stack_t  Структура STACK
 ************************************************************************************/

struct stack_t
{
    int numData;
    double Data[SIZE];
};

/** ********************************************************************************
 Construct  Создание STACK с обнуленными данными
 ************************************************************************************/

int Construct ( ST *s)
{
    ASSERT_OK ( s != NULL);
    s -> numData = 0;
    printf("NumData = %d\n", s->numData);
    for ( int i = 0; i < SIZE; i++)
        s -> Data[i] = 0;
}

/** ********************************************************************************
 Destruct - разрушение STACK и заполнение стека ядом
 ************************************************************************************/

int Destruct ( ST *s)
{
    ASSERT_OK ( s != NULL);
    s -> numData = 0;
    for ( int i = 0; i < SIZE; i++)
        s -> Data[i] = 0xBADBEEF;
}

/** ********************************************************************************
Dump Вывод всей информации по стеку
 ************************************************************************************/

int Dump ( ST *s)
{
    ASSERT_OK ( s != NULL);
    printf ( "STACK\nnumData = %d\n", s -> numData);
    for ( int i = 0; i < SIZE; i++)
        printf ( "%d ", s -> Data[i]);
    printf ( "\n");
}

/** ********************************************************************************
 OK проверка стека на профпригодность
 ************************************************************************************/

int OK ( ST *s)
{
    ASSERT_OK ( s != NULL);
    return !( ( s -> numData >= 0) && (s -> numData < SIZE));
}

/** ********************************************************************************
 Push положить число в стек
 ************************************************************************************/


int Push ( ST *s, int N)
{
  printf("PushEnter %p NumData = %d\n", s->numData);
  if ( !OK(s) ) exit(0);
    if ( s -> numData == SIZE)
        printf( "STACK IS FULL");
    else
        s -> Data[s -> numData ++] = N;
        
      printf("PushExit\n");
        return 0;
}

/** ********************************************************************************
 Pop Достать/удалить число из стека
 ************************************************************************************/


int Pop ( ST *s)
{
    if ( s->numData == 0)
    {
        printf( "STACK IS EMPTY");
        return 0xBADBEEF;

    }
    else
        return s -> Data[-- (s -> numData)];
}
