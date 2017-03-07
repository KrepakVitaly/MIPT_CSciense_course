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

_hello          db "Hello!", new_line, "The flags contain: ", 0
_promt2         db "Type another number ", 0
_format_i       db "%d %d", 0
_format_o       db "The greatest is %d  ", new_line, 0
_error          db "Error!", new_line, 0
_equal          db "This is equal numbers.", new_line, 0
;_CF_NULL        db "CF = 0 "
_NULL           db "0", 0
_TRUE           db "1", 0

;#########_VARIABLES_#########

true     dd 0 ; ? нам не важно начальное значение переменной
false    dd 0

;#########_DATA_SECTION_END_##########################

;###################################

section  '.text' code readable executable
main:
       ;mov eax, 0
       ;sub eax, 4
       pushad;
       pushfd

       ;puts("Hello!\n.....")
       cinvoke puts, _hello

       popfd
       popad

CF:
       jb CF_SET ;CF = 1
       pushad
       pushfd
       cinvoke printf, _NULL;_CF_NULL
       popfd
       pushfd
       jmp ZF
CF_SET:
       pushad
       pushfd
       cinvoke printf, _TRUE;_CF_NULL
       popfd
       pushfd

ZF:
       je ZF_SET ;ZF = 1
       pushad
       pushfd
       cinvoke printf, _NULL
       popfd
       pushfd
       jmp SF

ZF_SET:
       pushad
       pushfd
       cinvoke printf, _TRUE;_CF_NULL
       popfd
       pushfd



SF:
       js SF_SET ;SF = 1
       pushad
       pushfd
       cinvoke printf, _NULL
       popfd
       pushfd
       jmp OF
SF_SET:
       pushad
       pushfd
       cinvoke printf, _TRUE;_CF_NULL
       popfd
       pushfd



OF:
       jo OF_SET ;OF = 1
       pushad
       pushfd
       cinvoke printf, _NULL
       popfd
       pushfd
       jmp Exit
OF_SET:
       pushad
       pushfd
       cinvoke printf, _TRUE;_CF_NULL
       popfd
       pushfd

       ;call Print_Null




Exit:

       call [getchar]

       ;exit(0)
        cinvoke exit, 0



;proc Print