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

true     dd 0 ; ? ��� �� ����� ��������� �������� ����������
false    dd 0

;#########_DATA_SECTION_END_##########################

;###################################

section  '.text' code readable executable
main:
       ;mov eax, 0FFFFFFFFh
       ;add eax, 4

       call Print_Flags

       call [getchar]

       ;exit(0)
        cinvoke exit, 0

;###################################
;###################################
;###################################

proc Print_Flags

       pushad;
       pushfd
       ;puts("Hello!\n.....")
       cinvoke puts, _hello
       popfd
       popad

CF:                     ; CF handler
       jb CF_SET        ; If CF flag is set than jmp and print true
       call Print_Null
       jmp ZF           ; else print null and jmp to next registers handler
CF_SET:
       call Print_True  ;


ZF:                     ; ZF handler
       je ZF_SET        ; If ZF flag is set than jmp and print true
       call Print_Null
       jmp SF           ; else print null and jmp to next registers handler

ZF_SET:
       call Print_True


SF:                     ; SF handler
       js SF_SET        ; If ZF flag is set than jmp and print true
       call Print_Null
       jmp OF           ; else print null and jmp to next registers handler
SF_SET:
       call Print_True


OF:                     ; OF handler
       jo OF_SET        ; If OF flag is set than jmp and print true
       call Print_Null
       jmp _ret         ; else print null and jmp to exit from procedure
OF_SET:
       call Print_True

_ret:
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