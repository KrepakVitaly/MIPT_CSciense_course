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

SIZE_ARRAY = 8d

NEW_LINE   = 0Ah

;________________________________________________________

_format_o       db "Random number = %d ",  NEW_LINE, 0
_format_        db "Counter = %d",         NEW_LINE, 0
_format_mem     db "Malloc returned = %d", NEW_LINE, 0
_format_max     db "Maximal number = %d",  NEW_LINE, 0
_format_min     db "Minimal number = %d",  NEW_LINE, 0

;______________VARIABLES_________________________________

max_val   dd  0d;
min_val   dd -1d;
begin_arr dd  0d

;______________DATA_SECTION_END__________________________

;________________________________________________________

section  '.text' code readable executable
main:
       cinvoke malloc, SIZE_ARRAY*4
       mov edx, eax


       call Rand_Array


       call [getchar]

       cinvoke exit, 0




proc Rand_Array stdcall  param1:DWORD, _size_arr :DWORD

        mov edx, eax

        ret
endp