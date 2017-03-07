;#########################################
;  project:    "Task 1.1"               ##
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
_format_i       db "%u", 0
_format_o       db "The 32-bit unsigned number: %u  ", new_line, 0


;#########_VARIABLES_#########

num1    dd 0 ; ? нам не важно начальное значение переменной


;#########_DATA_SECTION_END_##########################

;###################################

section  '.text' code readable executable
main:

       ;puts("Hello!\n.....")
       cinvoke puts, _hello

       ;scanf("%u", &num1)
       cinvoke scanf, _format_i, num1

       mov eax, [num1]

       ;printf("The 32-bit unsigned number: %u\n");
       cinvoke printf, _format_o, eax
Exit:
       call [getchar]
       call [getchar]
       ;exit(0)
        cinvoke exit, 0
