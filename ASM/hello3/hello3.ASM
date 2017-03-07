;#########################################
;  project:    "Hello, world 3!"        ##
;   author:    Krepak zorroxied Vitaliy ##
;              FRTK 016                 ##
;     date:    17.02.2011               ##
;                                       ##
;#########################################

format PE
entry main

section '.idata' data import readable

include "win32ax.inc"

library msvcrt, 'MSVCRT.DLL'


import  msvcrt, \
        printf, 'printf', \
        puts,   'puts',   \
        getchar,'getchar',\
        scanf,  'scanf',  \
        exit,   'exit'


;#########_DATA_SECTION_##############################

section '.data' data readable writable

;##########_CONSTANTS_########

new_line = 0Ah

;############

_hello          db "Hello!", new_line, "Please type a number: ", 0
_promt2         db "Type another number ", 0
_format_i       db "%d %d", 0
_format_o       db "The greatest is %d  ", new_line, 0
_error          db "Error!", new_line, 0
_equal          db "This is equal numbers.", new_line, 0

;#########_VARIABLES_#########

num1    dd 0 ; ? нам не важно начальное значение переменной
num2    dd 0

;#########_DATA_SECTION_END_##########################

;###################################

section  '.text' code readable executable
main:

       ;puts("Hello!\n.....")
       cinvoke puts, _hello

       ;scanf("%d", &num1, &num2)
       cinvoke scanf, _format_i, num1, num2


       mov eax, [num1]
       cmp eax, [num2]
       jg  Num1GNum2
       je  Equal

       ;printf ("The greatest is", [num2])
       cinvoke printf, _format_o, [num2]

Exit:
       call [getchar]
       call [getchar]
       ;exit(0)
        cinvoke exit, 0


Num1GNum2:
       ;printf ("The greatest is", eax)
       cinvoke printf, _format_o, eax

       jmp Exit


Equal:
       ;printf ("This is equal numbers.\n")
       cinvoke printf, _equal

       jmp Exit



