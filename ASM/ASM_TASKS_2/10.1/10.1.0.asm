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
_format_wtf     db "What the terrible problem with solves?",  NEW_LINE, 0

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


       stdcall Solve_Q_equation, dword[a], dword[a + 4], dword[b], dword[b + 4], dword[c], dword[c + 4]
       stdcall Print_Solves

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

       FSUBP st1, st0   ; нахождение D
       FSQRT

       FLDZ             ;
       FUCOMIP st0, st1 ; если D - QNaN ( Quiet Non a Number ), то действительных корней нет
       jp NO_REAL_SOLVES;

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
       FSTP qword[res2]    ;Если дискриминант отрицательный, то оба корня = -1.#IND
       FSTP qword[res1]    ;
       ret
endp

;_________________________________________________________________

proc Solve_L_equation stdcall _b:QWORD, _c:QWORD

       FLD [_c]
       FLD [_b]

       FDIVP st1, st0
       FCHS

       FLDZ
       FLDZ
       FDIVP

       FSTP qword[res2]   ; так как уравнение линейное, второй корень = -1.#IND
       FSTP qword[res1]   ; если корня уравнения не существует, то первый корень = -1.#INF
                          ; если корней бесконечно много, то первый корень = 1.#QNAN

       ret
endp

;________________________________________________________________

proc Print_Solves stdcall

       FLD [res2]
       FLDZ
       FCOMIP st0, st1
       ;jp RES2_IND

       pushad
       push dword[res2 + 4]
       push dword[res2]
       push dword[res1 + 4]
       push dword[res1]
       cinvoke printf, _format_var
       popad

       ret

RES2_IND:
       FLD [res1]
       FLDZ
       FCOMIP st0, st1
       jp RES1_IND

       push dword[res1 + 4]
       push dword[res1]
       cinvoke printf, _format_lin
       ret


RES1_IND:
       cinvoke printf, _format_none
       ret

endp















