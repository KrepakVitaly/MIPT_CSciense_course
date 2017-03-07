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
_format_nonex   db "Solve isn't exist",  NEW_LINE, 0
_format_wtf     db "What the terrible problem with solves?",  NEW_LINE, 0
_format_num     db "%lg",  NEW_LINE, 0

;______________VARIABLES_________________________________

a       dq 0
b       dq 0
c       dq 0
res1    dq -1d
res2    dq -1d
tmp     dq ?

;______________DATA_SECTION_END__________________________



;________________________________________________________

section  '.text' code readable executable
main:

       FLD1


       FLDZ              ;
       FLD1              ; формируем -1.#INF
       FCHS              ;
       FDIVRP            ;
       FCOMIP  st1
       je SOLVE_IS_LIN

       FST qword[tmp]
       cinvoke printf, _format_num, dword[tmp], dword[tmp+4]

SOLVE_IS_LIN:


       call [getchar]

       cinvoke exit, 0

;________________________________________________________
;________________________________________________________






