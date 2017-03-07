;##########################################
;#  project:    "linked list"            ##
;#   author:    Krepak zorroxied Vitaliy ##
;#              FRTK 016                 ##
;#     date:    14.04.2011               ##
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

a       dq ?
b       dq ?
c       dq ?
res1    dq ?
res2    dq ?
tmp     dq ?

struct list_t
        data    dd ?



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
       FCOMIP st0, st1  ;���� � = 0, �� ��������� - ��������
       jz LINEAR

       FLD [_c]

       FLD1             ;+
       FLD1             ;+
       FLD1             ;+
       FLD1             ;+  ���������� � ���� ����� 4
       FADDP            ;+
       FADDP            ;+
       FADDP            ;+

       FMULP            ; ���������� 4ac
       FMULP            ;

       FSUBP st1, st0   ; ���������� D
       FSQRT


       FLDZ             ;
       FUCOMIP st0, st1 ; ���� D - QNaN ( Quiet Non a Number ), �� �������������� ������ ���
       jp NO_REAL_SOLVES;

       FLD1             ;
       FLD1             ;
       FADDP            ; ���������� 2*�
       FLD [_a]         ;
       FMULP            ;

       FDIV st1, st0    ; ��������� sqrt(d) �� 2�

       FLD [_b]         ; ��������� b �� 2�
       FDIVRP st1, st0  ;
       FCHS             ; �������� ����

       FADD st0, st1    ; ����� -b/2a + sqrt(d)/2a

       FST qword[res1]

       FSUB st0, st1    ; ����� -b/2a + sqrt(d)/2a - sqrt(d)/2a
       FSUB st0, st1    ; ����� -b/2a - sqrt(d)/2a

       FST qword[res2]
       ret

LINEAR:
       stdcall Solve_L_equation, dword[_b], dword[_b + 4], dword[_c], dword[_c + 4]
       ret

NO_REAL_SOLVES:
       FLDZ                ;
       FLD1                ; ��������� -1.#INF
       FCHS                ;
       FDIVRP              ;

       FST  qword[res2]    ; ���� ������������ �������������, �� ��� ����� = -1.#INF
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
       FCHS

       FSTP qword[res2]   ; ��� ��� ��������� ��������, ������ ������ = -1.#QNAN
       FSTP qword[res1]   ; ���� ����� ��������� �� ����������, �� ������ ������ = -1.#INF
                          ; ���� ������ ���������� �����, �� ������ ������ = 1.#QNAN

       ret
endp

;________________________________________________________________

proc Print_Solves stdcall

       FLD [res1]
       FLD [res2]

       FCOMI st0         ; ���� ������ ������ = -1.#QNAN, �� ��������� ��������
       jp  SOLVE_IS_LIN  ;

       FXCH

       FLDZ              ;
       FLD1              ; ��������� -1.#INF
       FCHS              ;
       FDIVRP            ;

       FCOMIP  st1       ; ���� ������ ������ = -1.#INF, �� ������������ �������������
       je SOLVE_IS_IND   ; ������� ���

       pushad
       cinvoke printf, _format_var, dword[res1], dword[res1+4], dword[res2], dword[res2+4]
       popad

       ret


SOLVE_IS_LIN:
       FXCH
       FCOMI st0         ; ���������� res1 � res1, ���� res1 = 1.#QNAN, ��
       jp SOLVE_IS_NAN   ; ��������������� PF, � ���������� ���������� ����� ������

       FLDZ              ;
       FLD1              ; ��������� -1.#INF
       FCHS              ;
       FDIVRP            ;

       FCOMIP  st1       ; ���� ����� ��������� �� ����������, �� ������ ������ = -1.#INF
       je SOLVE_IS_IND   ;

       pushad
       cinvoke printf, _format_lin, dword[res1], dword[res1+4]
       popad
       ret


SOLVE_IS_NAN:
       pushad
       cinvoke printf, _format_inf
       popad
       ret

SOLVE_IS_IND:
       pushad
       cinvoke printf, _format_none
       popad
       ret


endp



