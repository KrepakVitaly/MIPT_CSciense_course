;#########################################
;  project:    "Print CF, ZF, OF, SF!"  ##
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
bit_mask = 1b

;############

_hello          db "Hello!", new_line, "The flags contain: ", 0
_cpy_flag       db "0000", 0
_NULL           db "0", 0
_TRUE           db "1", 0


;#########_DATA_SECTION_END_##########################

;###################################

section  '.text' code readable executable
main:
       ;mov eax, 0FFFFFFFFh
       ;add eax, 4

       call Print_Flags

       call [getchar]

       cinvoke exit, 0

;###################################
;###################################
;###################################

proc Print_Flags
       pushad
       pushfd

       pushfd
       pop eax
       push eax
       push eax
       push eax
       and eax, bit_mask



      ret
endp

;############################## This is the function print #
proc Print_Null
       pushad
       pushfd
       cinvoke printf, _NULL
       popfd
       popad
       ret
endp

;###################################
proc Print_True
       pushad
       pushfd
       cinvoke printf, _TRUE
       popfd
       popad
       ret
endp