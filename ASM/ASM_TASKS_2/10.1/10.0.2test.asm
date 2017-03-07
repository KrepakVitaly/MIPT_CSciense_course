;##########################################
;#  project:    "quadratic equation"     ##
;#   author:    Krepak zorroxied Vitaliy ##
;#              FRTK 016                 ##
;#     date:    31.03.2011               ##
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

NEW_LINE   = 0Ah

;________________________________________________________

_format_o       db "Please, enter the coefficients of quadratic equation: a, b, c",  NEW_LINE, 0
_format_in      db "%lg %lg %lg",  0
_format_var     db "A_quad = %lg, %lg",  NEW_LINE, 0
_format_d       db "D =  %lg",  NEW_LINE, 0
_format_lin     db "A_linr = %lg",  NEW_LINE, 0
_format_inf     db "There are many solves",  NEW_LINE, 0
_format_none    db "There are no solves",  NEW_LINE, 0

;______________VARIABLES_________________________________

a       dq ?
b       dq ?
c       dq ?
res1    dq ?
res2    dq ?

;______________DATA_SECTION_END__________________________



;________________________________________________________

section  '.text' code readable executable
main:
       cinvoke printf, _format_o
       cinvoke scanf,  _format_in, a, b, c

       stdcall  Solve_L_equation,  dword[b], dword[b + 4], dword[c], dword[c + 4], dword[res1], dword[res1 + 4], dword[res2], dword[res2 + 4]


       stdcall   Print_Solves, dword[res1], dword[res1 + 4], dword[res2], dword[res2 + 4]

       call [getchar]
       call [getchar]

       cinvoke exit, 0

;________________________________________________________
;_________________________________________________________________

proc Solve_L_equation stdcall _b:QWORD, _c:QWORD, _res1:QWORD, _res2:QWORD

       FLD [_c]
       FLD [_b]


       FDIVP st1, st0
       FCHS

       FLDZ
       FLDZ
       FDIVP

       FSTP qword[res2]   ; так как уравнение линейное, второй корень = -1.#IND
       FSTP qword[res1]   ;




       ret
endp




proc Print_Solves stdcall _res1:QWORD, _res2:QWORD

       push dword[_res1 + 4]
       push dword[_res1]
       cinvoke printf, _format_d

       ret
endp





















