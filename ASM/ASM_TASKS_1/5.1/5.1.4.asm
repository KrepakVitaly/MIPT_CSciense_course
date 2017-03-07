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

import  msvcrt,           \
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
_format_elmnt_  db "%d ", NEW_LINE, 0

;______________VARIABLES_________________________________


begin_arr dd  0d
size_arr  dd  SIZE_ARRAY

;______________DATA_SECTION_END__________________________

SIZE_ARRAY = 2000000d
SIZE_DWORD = 4

;________________________________________________________

section  '.text' code readable executable
main:
       cinvoke malloc, SIZE_ARRAY*SIZE_DWORD
       mov [begin_arr], eax

       stdcall Rand_Array, [begin_arr], SIZE_ARRAY
       ;stdcall Print_Arr,  [begin_arr], SIZE_ARRAY
       stdcall Find_Min,   [begin_arr], SIZE_ARRAY
       stdcall Find_Max,   [begin_arr], SIZE_ARRAY


       call [getchar]

       cinvoke exit, 0

;________________________________________________________
;________________________________________________________

proc Rand_Array stdcall uses edx eax ecx,  _begin_arr:DWORD, _size_arr:DWORD

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

       add edx, 4
       inc ecx
       cmp ecx, [_size_arr]
       jb Begin

       ret
endp

;________________________________________________________

proc Print_Arr stdcall uses eax ecx,  _begin_arr:DWORD, _size_arr:DWORD

       mov eax, [_begin_arr]
       mov ecx, [_size_arr]

.Cycle:
       pushad
       cinvoke printf, _format_elmnt_, dword[eax]
       popad

       add eax, SIZE_DWORD
       loop .Cycle

       ret
endp

;________________________________________________________

proc Find_Min stdcall  uses edx ecx, _begin_arr:DWORD, _size_arr:DWORD

       mov eax, -1d
       mov ecx, [_size_arr]
       mov edx, [_begin_arr]

.Cycle:
       cmp eax, [edx]
       jb .Next
       mov eax, [edx]
.Next:
       add edx, 4d
       loop .Cycle

       pushad
       cinvoke printf, _format_min , eax
       popad

       ret
endp

;________________________________________________________

proc Find_Max stdcall uses edx ecx,  _begin_arr:DWORD, _size_arr:DWORD

       mov eax, 0d
       mov ecx, [_size_arr]
       mov edx, [_begin_arr]

Cycle:
       cmp eax, [edx]
       jg Next_1
       mov eax, [edx]
Next_1:
       add edx, 4d
       loop Cycle

       pushad
       cinvoke printf, _format_max , eax
       popad

       ret
endp

;________________________________________________________