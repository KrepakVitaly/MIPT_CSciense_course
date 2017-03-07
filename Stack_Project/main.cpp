#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Stack_construct - занул€ет count
Stack_error котора€ выдает ошибку если некуда класть или нечего вынимать
сделать Stack_clear котора€ приравнивает счетчик к 0
Stack_top
Stack_ok - провер€ет не испорчена ли структура данных (счетчик должен быть от 0 до границы стека)
Stack_destruct - уничтожает структуру ( загаживать индекс (k = -666))
Stack_dump (&s, output) - выводит все содержимое стека и информацию о нем
Stack_dup - дублирует последний элемент стека
swap - мен€ет два послдних элемента
+ (Add) - (Sub) / (Div) * (Mul) ^ (Pow) sqrt sin cos

пример enum
enum
{
    cmd None = 0;
    cmd Push = 1;
    cmd Pop = 2;
    cmd Max;
    cmd Stop = -1
}
switch - чета типа case

прога использующа€ стек
из файла читает команды, отичающиес€ по номерам. ѕример:
1 5 1 7 1 10 1 2 11 -1
команда 1 означает пуш и пушит то что после него
т. е. push(5); push(7);
команда 10 - сложение - последние 2 числа удал€ет и записывает их сумму
команда 11 - вычитание (аналогично сложению)
-1 - конец программы - распечатка ответа на экране (последнее число (top))

написать асемблер.екзе
котора€ прерводит push в 1

дизассемблер.екзе
1 в push

1) push 5
2) push 7
3) +
4) push10
5) jb 3

jb - если топ > топ - 1
ja - если топ < топ - 1
je - если топ = топ - 1
jne - если топ != топ - 1
переходит к третьему оператору

1) push 2
2) push 3
3) +
4) call 8
5) -1
6)
7)
8) dup
9) *
10) ret

после  4ой сторки идет на восьмую, после 10ой на 5ую

на сайте деда есть стать€ јндре€ ћатвиенко про виртуальный процессор с примерами

можно еще добавить setpixel чтоб она ставила точку на экране, тогда она будет строить графику
*/
/*
My assembler's functions
0) nop
1) push
2) pop
3) dup
4) call
5) ret
6) jb - если топ > топ - 1
7) ja - если топ < топ - 1
8) je - если топ = топ - 1
9) jne - если топ != топ - 1
10) add
11) sub
12) mul
13) div
14) pow
15) ret

*/

#define DEFINE_CMD_( cmd ) cmd_##cmd,

enum cmd
{  
cmd_MaxCmdError = -1,
#include "cmd_list.c"
cmd_MaxCmdNum
};

#undef DEFINE_CMD_

const int NMAX = 1000, CMD_MAX = 17;

struct Cmd_t
    {
    int         code;
    const char* name;
    };

const Cmd_t commands[] = {
    {cmd_nop,  "nop" },
    {cmd_push, "push"},
    {cmd_pop,  "pop" }
};

//------------------------------------------------------------------------

#define DEFINE_CMD_( cmd )                  \
    {                                       \
    commands[cmd_##cmd].code = cmd_##cmd;   \
    commands[cmd_##cmd].name = #cmd;        \
    }

void InitCommandTable (Cmd_t commands[])
{
#include "cmd_list.c"
}

#undef DEFINE_CMD_

#ifndef __cplusplus
typedef int bool;
#endif

//-------------------------------------------------------------
//! @brief Reads file into NEW allocated buf
//! @param filename File Name
//! @warning NB: this MUST be freed by caller!
//!
//! Example:
//! @code
//!  int main()
//!  {
//!  char* buf = ReadFile_New ("a.txt");
//!  
//!  bool hasDollarSigns = strchr (buf, '$');
//!
//!  if (hasDollarSigns) printf ("This is money-oriented information!");
//!
//!  free (buf);   // NB: this MUST be done
//!  }
//! @endcode
//-------------------------------------------------------------

#define TRY
#define CATCH   __catch:
#define THROW   goto __catch;

char* ReadFile_New (const char* filename)
{
TRY
    {
    FILE* f = fopen (filename, "r");
    if (!f) THROW;
    
    int size = fseek (f, 0, SEEK_END);
    if (rewind (f) == EOF) THROW;
    
    if (size == EOF) THROW;
    
    char* new_buf = calloc (sizeof (*new_buf), size);
    if (!new_buf) THROW;

    if (!fread (new_buf, sizeof (*new_buf), size, f) != size) THROW;

    return new_buf;  // NB: this MUST be freed by caller
    }
    
CATCH
    {
    free (new_buf);
    fclose (f);
    return NULL;
    }
}

//------------------------------------------------------------------------

const char* cmd_arr[CMD_MAX] = {"nop ","push","pop ","dup ","call","ret ","jb  ","ja  ","je  ","jne ",
                                 "add ","sub ","mul ","div ","pow ","sqrt","end "};
struct Stack_t
{
    int data [NMAX];
    int count;
};

//stack functions
void Stack_construct(Stack_t* s, int size);
void Stack_push (Stack_t* s, int v);
int Stack_pop (Stack_t* s);
bool Stack_error (Stack_t* s);
bool Stack_ok (Stack_t* s);
void Stack_destruct (Stack_t* s);
void Stack_dump (Stack_t* s, FILE* output);
int Stack_top (Stack_t* s);
void Stack_dup (Stack_t* s);

//assembler function
int assembl();



int main()
{
    Stack_t s={};
    Stack_construct (&s, 100); // 100 это размер
    Stack_push (&s, 10);
    Stack_push (&s, 20);

    printf ("%d ", Stack_pop(&s));
    printf ("%d ", Stack_pop(&s));

    assembl();

    http://sizeof.livejournal.com
    https://livejournal.com

    return 0;

}

void Stack_construct(Stack_t* s, int size)
{
    s -> count = 0;
}

void Stack_push (Stack_t* s, int v)
{
    if (Stack_ok (s)){
        s -> data [ s -> count++ ] = v;
    }
}

int Stack_pop (Stack_t* s)
{
    return s -> data [ --s -> count];
}

bool Stack_error (Stack_t* s)
{
    return ((s -> count) < 0) || ((s -> count) > NMAX);
}

bool Stack_ok (Stack_t* s)
{
    return ((s -> count) >= 0) && ((s -> count) <= NMAX);
}

void Stack_destruct (Stack_t* s)
{
    s -> count = -666;
}

void Stack_dump (Stack_t* s, FILE* output)
{
    int i = 0;

    for (i; i <= (s -> count); i++) {
        fprintf(output,"%d ", s -> data[i]);
    }
}

int Stack_top(Stack_t* s)
{
    return (s -> data[ s -> count--]);
}

void Stack_dup(Stack_t* s)
{
    int tmp = s -> data[s -> count-1];
    s -> data[s ->count++] = tmp;
}

int assembl ()
{
    FILE* inp = fopen("input.txt","r");
    FILE* outp = fopen("output.txt", "w");

    char str[4]={' ',' ',' ',' '};
    int arg = 0, i = 0;

    //fscanf (inp, "%s %d", str, &arg);
    while ((stricmp(str,"end"))!=0){
        fscanf (inp, "%s %d", str, &arg);

        for (i; i < CMD_MAX; i++){
            if (stricmp(cmd_arr[i], str))
                fprintf(outp,"%d %d ", i, arg);
        }

        /*switch (str){
            case "push": fprintf(outp,"1 %d ", arg);
                break;
            case "nop": fprintf(outp,"0 ");
                break;
            case "pop": fprintf(outp,"2 ");
                break;
            case "dup": fprintf(outp,"3 ");
                break;
            case "call": fprintf(outp,"4 %d ", arg);
                break;
            case "ret": fprintf(outp,"5 ");
                break;
            case "jb": fprintf(outp,"6 ");
                break;
            case "ja": fprintf(outp,"7 ");
                break;
            case "je": fprintf(outp,"8 ");
                break;
            case "jne": fprintf(outp,"9 ");
                break;
            case "add": fprintf(outp,"10 ");
                break;
            case "sub": fprintf(outp,"11 ");
                break;
            case "mul": fprintf(outp,"12 ");
                break;
            case "div": fprintf(outp,"13 ");
                break;
            case "pow": fprintf(outp,"14 ");
                break;
            case "sqrt": fprintf(outp,"15 ");
                break;
            case "end": fprintf(outp,"16 ");
                break;
        }
    */
    }

    fprintf (outp, "%s %d",str, arg);
    printf("after the writing procedure");

    fclose(inp);
    fclose(outp);

    return 0;
}
