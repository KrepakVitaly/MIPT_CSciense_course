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
bit_mask = 100011000001b

;############

_hello          db "Hello!", new_line, "Please type a number: ", 0
_promt2         db "Type another number ", 0
_format_i       db "%d %d", 0
_format_o       db "The greatest is %d  ", new_line, 0
_error          db "Error!", new_line, 0
_equal          db "This is equal numbers.", new_line, 0
_CF_NULL        db "CF = NULL  "

;#########_VARIABLES_#########

true     dd 0 ; ? нам не важно начальное значение переменной
false    dd 0

;#########_DATA_SECTION_END_##########################

;###################################

section  '.text' code readable executable
main:
       pushad;
       pushfd

       ;puts("Hello!\n.....")
       cinvoke puts, _hello

       popfd
       popad

       jb CF_SET ;CF = 1
       pushad
       pushfd
       cinvoke printf, _CF_NULL
       popfd
       pushfd

       je ZF_SET ;ZF = 1
       pushad
       pushfd
       cinvoke printf, _ZF_NULL
       popfd
       pushfd

       js SF_SET ;SF = 1
       pushad
       pushfd
       cinvoke printf, _SF_NULL
       popfd
       pushfd

       jo OF_SET ;OF = 1
       pushad
       pushfd
       cinvoke printf, _OF_NULL
       popfd
       pushfd




Exit:

       call [getchar]
       call [getchar]

       popa;

       ;exit(0)
        cinvoke exit, 0



