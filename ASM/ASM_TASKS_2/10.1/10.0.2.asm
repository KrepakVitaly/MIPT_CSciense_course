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

a       dq 0
b       dq 0
c       dq 0
res1    dq 0
res2    dq 0

;______________DATA_SECTION_END__________________________



;________________________________________________________

section  '.text' code readable executable
main:
       cinvoke printf, _format_o
       cinvoke scanf,  _format_in, a, b, c

       stdcall Solve_Q_equation, dword[a], dword[a + 4], dword[b], dword[b + 4], dword[c], dword[c + 4]

       call [getchar]
       call [getchar]

       cinvoke exit, 0

;________________________________________________________
;________________________________________________________

proc Solve_Q_equation stdcall _a:QWORD, _b:QWORD, _c:QWORD

       FLD [_b]
       FLD [_b]
       FMULP

       FLD [_a]
       FLDZ
       FCOMIP st0, st1  ;если а = 0, то уравнение - линейное
       jz LINEAR

       FLD [_c]

       FLD1             ;+
       FLD1             ;+
       FLD1             ;+
       FLD1             ;+  добавление в стек числа 4
       FADDP            ;+
       FADDP            ;+
       FADDP            ;+

       FMULP            ; нахождение 4ac
       FMULP            ;

       FSUBP st1, st0   ;нахождение D

       sub esp, 8
       FST qword[esp]

       cinvoke printf, _format_d

       FLDZ
       FCOMIP st0, st1
       ja NO_REAL_SOLVES
       FSQRT



       FLD1             ;
       FLD1             ;
       FADDP            ; нахождение 2*а
       FLD [_a]         ;
       FMULP            ;

       FDIV st1, st0    ; разделить sqrt(d) на 2а

       FLD [_b]         ; разделить b на 2а
       FDIVRP st1, st0  ;
       FCHS             ; поменять знак

       FADD st0, st1    ; найти -b/2a + sqrt(d)/2a

       FST qword[res1]

       FSUB st0, st1    ; найти -b/2a + sqrt(d)/2a - sqrt(d)/2a
       FSUB st0, st1    ; найти -b/2a - sqrt(d)/2a

       FST qword[res2]
       ret

LINEAR:
       stdcall Solve_L_equation, dword[_b], dword[_b + 4], dword[_c], dword[_c + 4]
       ret
NO_REAL_SOLVES:
       cinvoke printf, _format_none
       ret
endp

;_________________________________________________________________

proc Solve_L_equation stdcall _b:QWORD, _c:QWORD

       FLD [_c]
       FLDZ
       FCOMIP st0, st1
       jz C_EQUAL_Z

       FLD [_b]
       FLDZ
       FCOMIP st0, st1
       jz NO_SOLVES


       FDIVP st1, st0
       FCHS


EXTRACT:
       sub esp, 8
       FSTP qword[esp]

       cinvoke printf, _format_lin
       ret

MANY_SOLVES:
       cinvoke printf, _format_inf
       ret

C_EQUAL_Z:
       FLD [_b]
       FLDZ
       FCOMIP st0, st1
       jz MANY_SOLVES   ; b = c = 0
       FLDZ
       jmp EXTRACT

NO_SOLVES:
       cinvoke printf, _format_none
       ret

endp





















