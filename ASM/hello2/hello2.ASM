;#########################################
;  project:    "Hello, world 2!"        ##
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
_format_i       db "%d", 0
_format_o       db "Average of the numbers if %d  ", new_line, 0
_error          db "Error!", new_line, 0

;#########_VARIABLES_#########

num1    dd 0 ; ? нам не важно начальное значение переменной
num2    dd 0

;#########_DATA_SECTION_END_##########################

;###################################

section  '.text' code readable executable
main:

       ;puts("Hello!\n.....")
       cinvoke puts, _hello

       ;scanf("%d", &num1)
       cinvoke scanf, _format_i, num1

       cmp eax, 1
       jne error

       ;puts
       cinvoke puts, _promt2

       ;scanf
       cinvoke scanf, _format_i, num2

       cmp eax, 1
       jne error

       mov eax, [num1]
       add eax, [num2]
       shr eax, 1

       ;printf ("Average...", eax )
       cinvoke printf, _format_o, eax


       call [getchar]
       call [getchar]

       ;exit(0)
        cinvoke exit, 0

error:
       ;puts("Error!\n")
       cinvoke puts, error

       ;exit(-1)
       cinvoke exit, -1





