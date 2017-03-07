;#########################################
;  project:    "Randomize me, quickly!" ##
;   author:    Krepak zorroxied Vitaliy ##
;              FRTK 016                 ##
;     date:    17.03.2011               ##
;                                       ##
;#########################################

format PE
entry main

section '.idata' data import readable

include "win32ax.inc"

library msvcrt, 'MSVCRT.DLL'

;________________________________________________________

import  msvcrt, \
        printf, 'printf', \
        puts,   'puts',   \
        getchar,'getchar',\
        scanf,  'scanf',  \
        exit,   'exit',   \
        malloc, 'malloc', \
        free,   'free',   \
        srand,  'srand',  \
        rand,   'rand',   \
        time,   'time'


;______________DATA_SECTION______________________________

section '.data' data readable writable

;______________CONSTANTS_________________________________

SIZE_ARRAY = 0Ah
NEW_LINE   = 0Ah

;________________________________________________________

_hello          db "Hello!", NEW_LINE, "The flags contain: ", 0
_format_o       db "Random number = %d ",  NEW_LINE, 0
_format_        db "Counter = %d",  NEW_LINE, 0
_format_mem     db "Malloc returned = %d",  NEW_LINE, 0
_format_max     db "Maximal number = %d",  NEW_LINE, 0
_format_min     db "Minimal number = %d",  NEW_LINE, 0

;______________VARIABLES_________________________________

arr_begin   dd 0 ;

;______________DATA_SECTION_END__________________________

;________________________________________________________

section  '.text' code readable executable
main:
       cinvoke malloc, 100d
       mov [arr_begin], eax
       mov edx, eax
       ;pusha
       ;cinvoke printf, _format_mem, eax
       ;popa

       pusha
       cinvoke time, 0
       cinvoke srand, eax
       popa

       mov ecx,  0d
       mov ebx,  0d
       mov edx, -1d
       push ebx

Begin:
       push ecx
       cinvoke rand
       pop ecx


       cmp edx, eax
       jb Next_0
       mov edx, eax
Next_0:

       cmp ebx, eax
       jg Next_1
       mov ebx, eax
Next_1:

       mov [arr_begin+4*ecx], eax
       inc ecx
       cmp ecx, 8d

       jb Begin

       pusha
       cinvoke printf, _format_max , ebx
       popa

       pusha
       cinvoke printf, _format_min , edx
       popa

       call [getchar]

       cinvoke exit, 0

