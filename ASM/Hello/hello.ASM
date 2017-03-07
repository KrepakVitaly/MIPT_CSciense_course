;#########################################
;  project:    "Hello, world!"          ##
;   author:    Krepak zorroxied Vitaliy ##
;              FRTK 016                 ##
;     date:    17.02.2011               ##
;                                       ##
;#########################################

format PE
entry main

section '.idata' data import readable

include "macro\import32.inc"

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

num1    dd ? ; ? нам не важно начальное значение переменной
num2    dd ?

;#########_DATA_SECTION_END_##########################

;###################################

section  '.text' code readable executable
main:

       ;puts("Hello!\n.....")
       push  _hello
       call [puts]
       add   esp, 4

       ;scanf("%d", &num1)
       push num1
       push _format_i
       call [scanf]
       add  esp, 8

       cmp eax, 1
       jne error

       ;puts
       push _promt2
       call [puts]
       add esp, 4

       ;scanf
       push num2
       push _format_i
       call [scanf]
       add esp, 8

       cmp eax, 1
       jne error

       mov eax, [num1]
       add eax, [num2]
       shr eax, 1

       ;printf ("Average...", eax )
       push eax
       push _format_o
       call [printf]
       add  esp, 8


       call [getchar]
       call [getchar]

       ;exit(0)
       push 0;
       call [exit]

error:
       ;puts("Error!\n")
       push _error
       call [puts]
       add esp, 4

       ;exit(-1)
       push -1;
       call [exit]





