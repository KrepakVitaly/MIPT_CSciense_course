;##########################################
;#  project:    "Randomize me, quickly!" ##
;#   author:    Krepak zorroxied Vitaliy ##
;#              FRTK 016                 ##
;#     date:    17.03.2011               ##
;#                                       ##
;##########################################

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
size_arr  dd  8d

;______________DATA_SECTION_END__________________________

SIZE_ARRAY = 8d

;________________________________________________________

section  '.text' code readable executable
main:
       cinvoke malloc, SIZE_ARRAY*4
       mov [begin_arr], eax

       stdcall Rand_Array, [begin_arr], [size_arr]
       stdcall Find_Min, [begin_arr], [size_arr]
       stdcall Find_Max, [begin_arr], [size_arr]

       call [getchar]

       cinvoke exit, 0

;________________________________________________________
;________________________________________________________

proc Rand_Array stdcall uses edx, eax, ecx  _begin_arr:DWORD, _size_arr:DWORD

       ;pushad
       mov edx, [_begin_arr]

       pushad
       cinvoke time, 0
       cinvoke srand, eax
       popad

       mov ecx, 0d ;счетчик

Begin:
       push edx
       push ecx
       cinvoke rand
       pop ecx
       pop edx

       mov [edx], eax

       pushad
       cinvoke printf, _format_o, dword[edx]
       popad

       pushad
       cinvoke printf, _format_ , ecx
       popad

       add edx, 4
       inc ecx
       cmp ecx, [_size_arr]
       jb Begin

       ;popad
       ret
endp

;________________________________________________________


proc Find_Min stdcall  uses edx eax ecx, _begin_arr:DWORD, _size_arr:DWORD
       ;pushad
       mov edx, -1d
       mov ecx, [_size_arr]
       mov eax, [_begin_arr]

_Cycle:
       cmp edx, [eax]
       jb Next_0
       mov edx, [eax]
Next_0:
       add eax, 4d
       loop _Cycle

       pushad
       cinvoke printf, _format_min , edx
       popad

       ;popad
       ret
endp

;________________________________________________________

proc Find_Max stdcall uses eax edx ecx  _begin_arr:DWORD, _size_arr:DWORD
       ;pushad
       mov edx, 0d
       mov ecx, [_size_arr]
       mov eax, [_begin_arr]

Cycle:
       cmp edx, [eax]
       jg Next_1
       mov edx, [eax]
Next_1:
       add eax, 4d
       loop Cycle

       pushad
       cinvoke printf, _format_max , edx
       popad

       ;popad
       ret
endp