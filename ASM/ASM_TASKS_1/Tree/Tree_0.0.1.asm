;##########################################
;#  project:    "Tree"                   ##
;#   author:    Krepak zorroxied Vitaliy ##
;#              FRTK 016                 ##
;#     date:    12.05.2011               ##
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

NEW_LINE = 0Ah

;________________________________________________________

_format_o       db "Random number = %d ",  NEW_LINE, 0
_format_ecx     db "ecx = %d ",  NEW_LINE, 0
_format_elmnt   db "Element = %d ",  NEW_LINE, 0
_format_addr    db "Addr of Element = %d ",  NEW_LINE, 0
_format_data    db "Data of Element = %d ",  NEW_LINE, 0
_format_data_r    db "Data Right of Element = %d",  NEW_LINE, 0
_format_data_l    db "Data Left  of Element = %d",  NEW_LINE, 0
_format_max     db "Max value = %d ",  NEW_LINE, 0
_format_min     db "Min value = %d ",  NEW_LINE, 0
_format_left     db "Left",  NEW_LINE, 0
_format_right     db "Right",  NEW_LINE, 0
_format_home     db "Home",   NEW_LINE, 0
_format_tree     db "%*s|%d", NEW_LINE, 0

;______________VARIABLES_________________________________

struct node
        data    dd ?
        left    dd ?
        right   dd ?
ends

size   dd 20d

;______________DATA_SECTION_END__________________________

;________________________________________________________

section  '.text' code readable executable
main:                                         ;

       stdcall Create_Bin_Tree, dword[size]
       ;stdcall Print_Tree,  eax
       mov ebx, -1
       stdcall Print_Tree_Without_Init_EBX, eax

       call [getchar]

       cinvoke exit, 0

;________________________________________________________
;________________________________________________________

proc Create_Bin_Tree stdcall uses edx ecx,  _size:DWORD
     locals
       _cur      dd 0
       _head     dd 0
     endl

       mov ecx, dword[_size]
       dec ecx
       mov eax, 0                              ; проверка на правильность ввода
       cmp ecx, 0                              ; количества элементов дерева
       jle .End                                ;



       pushad                                  ;

       push ecx;                               ;
       cinvoke malloc, sizeof.node             ; выделяем память под начальный узел
       pop ecx                                 ;
       mov dword[_head], eax                   ; в eax -- адрес этого узла

       push eax                                ;
       push ecx                                ;
       cinvoke time, 0                         ; генерим случайное число
       cinvoke srand, eax                      ;
       cinvoke rand                            ;
       cinvoke rand                            ;
       mov edx, eax                            ;
       pop ecx                                 ;
       pop eax                                 ;

       mov dword[eax + node.data ], edx        ; инициализация начального узла
       ;pushad                                 ;
       ;cinvoke printf, _format_o, edx         ;
       ;popad                                  ;
       mov dword[eax + node.left ], 0d         ;
       mov dword[eax + node.right], 0d         ;

.Cycle:
       push eax                                ;
       push ecx                                ;
       cinvoke rand                            ;
       mov edx, eax                            ;
       pop ecx                                 ;
       pop eax                                 ;

       cmp dword[eax + node.data], edx
       jbe .To_Right                           ;
                                               ; для функций Add_Node_To_Left и Add_Node_To_Right должны быть
.To_Left:                                      ; подготовлены регистры eax -- адрес начального узла и edx -- случайное
       stdcall Add_Node_To_Left, eax           ; значение, после отработки функции возвращают в eax -- адрес
       jmp .End_Cycle                          ; нового узла дерева
                                               ;
.To_Right:                                     ;
       stdcall Add_Node_To_Right, eax          ;

.End_Cycle:
       ;pushad                                  ;
       ;cinvoke printf, _format_ecx, ecx        ;
       ;popad                                   ;

       loop .Cycle

       popad

       mov eax, dword[_head]

.End:
       ret
endp

;________________________________________________________

;________________________________________________________

proc Add_Node_To_Left stdcall uses eax edx ecx, _prev:DWORD
     locals
       _new      dd 0
     endl
       mov eax, dword[_prev]
       ;pushad
       ;cinvoke printf, _format_left
       ;popad
       cmp dword[eax + node.left], 0     ; в eax -- адрес узла-"предка"
       jbe .Record

       mov eax, dword[eax + node.left]   ; если указатель не нулевой продолжаем двигаться в случайном порядке,
                                         ; приняв за узел-"предок" левый узел

       cmp dword[eax + node.data], edx
       jbe .To_Right

.To_Left:
       stdcall Add_Node_To_Left, eax
       ret
.To_Right:
       stdcall Add_Node_To_Right, eax
       ret

.Record:                                       ; если указатель на левый узел от узла-"предка" -- нулевой, то
                                               ; создаем этот левый узел
       push eax
       push edx                                ;
       cinvoke malloc, sizeof.node
       pop edx                                 ; выделяем память под узел, в eax -- адрес этого узла
       mov dword[eax + node.data ], edx        ; инициализация узла
       ;pushad                                  ;
       ;cinvoke printf, _format_o, edx          ;
       ;popad                                   ;
       mov dword[eax + node.left ], 0d         ;
       mov dword[eax + node.right], 0d         ;
       mov edx , eax
       pop eax

       mov dword[eax + node.left], edx

       ret
endp


;________________________________________________________

proc Add_Node_To_Right stdcall uses eax edx ecx, _prev:DWORD
     locals
       _new      dd 0
     endl
       mov eax, dword[_prev]

       ;pushad
       ;cinvoke printf, _format_right
       ;popad

       cmp dword[eax + node.right], 0     ; в eax -- адрес узла-"предка"
       jbe .Record

       mov eax, dword[eax + node.right]   ; если указатель не нулевой продолжаем двигаться в случайном порядке,
                                          ;  приняв за узел-"предок" правый узел

       cmp dword[eax + node.data], edx
       jbe .To_Right

.To_Left:
       stdcall Add_Node_To_Left, eax
       ret
.To_Right:
       stdcall Add_Node_To_Right, eax
       ret

.Record:                                       ; если указатель на левый узел от узла-"предка" -- нулевой, то
                                               ; создаем этот левый узел
       push eax
       push edx                                ;
       cinvoke malloc, sizeof.node
       pop edx                                 ; выделяем память под узел, в eax -- адрес этого узла
       mov dword[eax + node.data ], edx        ; инициализация узла
       ;pushad                                  ;
       ;cinvoke printf, _format_o, edx          ;
       ;popad                                   ;
       mov dword[eax + node.left ], 0d         ;
       mov dword[eax + node.right], 0d         ;
       mov edx , eax
       pop eax

       mov dword[eax + node.right], edx

       ret
endp


;________________________________________________________

proc Print_Tree stdcall uses ebx edx ecx, _head:DWORD

       mov eax, dword[_head]                                           ;
       mov ebx, 0
       cmp dword[eax + node.left], 0
       jbe .Next
       stdcall Print_From_Left, eax
.Next:
       pushad                                                          ;
       cinvoke printf,  _format_tree, ebx, '', dword[eax + node.data]         ;
       cinvoke printf, _format_home
       popad


       cmp dword[eax + node.right], 0
       jbe .End
       stdcall Print_From_Right, eax

.End:
       ret
endp

;________________________________________________________

proc Print_From_Left stdcall uses ebx edx eax ecx, _head:DWORD

       mov eax, dword[eax + node.left]
       inc ebx
       cmp dword[eax + node.left], 0
       jbe .Next
       stdcall Print_From_Left, eax
.Next:
       pushad                                                          ;
       cinvoke printf, _format_tree, ebx, '', dword[eax + node.data]             ;
       ;cinvoke printf, _format_left
       popad


       cmp dword[eax + node.right], 0
       jbe .End
       stdcall Print_From_Right, eax

.End:
       dec ebx
       ret
endp
;________________________________________________________


proc Print_From_Right stdcall uses ebx edx eax ecx, _head:DWORD

       mov eax, dword[eax + node.right]
       inc ebx
       cmp dword[eax + node.left], 0
       jbe .Next
       stdcall Print_From_Left, eax
.Next:
       pushad                                                          ;
       cinvoke printf, _format_tree, ebx, '', dword[eax + node.data]          ;
       ;cinvoke printf, _format_right
       popad


       cmp dword[eax + node.right], 0
       jbe .End
       stdcall Print_From_Right, eax

.End:
       dec ebx
       ret
endp

;________________________________________________________

proc Print_Tree_New stdcall uses ebx , _head:DWORD
       mov ebx, -1
       stdcall Print_Tree_Without_Init_EBX, dword[_head]
       ret
endp

proc Print_Tree_Without_Init_EBX stdcall _head:DWORD

       inc ebx
       mov eax, dword[_head]                                           ;

       cmp dword[eax + node.left], 0
       jbe .Next
       mov eax, dword[eax + node.left]
       stdcall Print_Tree_Without_Init_EBX, eax
       mov eax, dword[_head]
.Next:
       pushad                                                          ;
       cinvoke printf,  _format_tree, ebx, '', dword[eax + node.data]  ;
       popad


       cmp dword[eax + node.right], 0
       jbe .End
       mov eax, dword[eax + node.right]
       stdcall Print_Tree_Without_Init_EBX, eax
       mov eax, dword[_head]

.End:
       dec ebx
       ret
endp

;________________________________________________________

proc Create_Bin_Tree_New stdcall uses edx ecx,  _size:DWORD
     locals
       _cur      dd 0
       _head     dd 0
     endl

       mov ecx, dword[_size]
       dec ecx
       mov eax, 0                              ; проверка на правильность ввода
       cmp ecx, 0                              ; количества элементов дерева
       jle .End                                ;



       pushad                                  ;

       push ecx;                               ;
       cinvoke malloc, sizeof.node             ; выделяем память под начальный узел
       pop ecx                                 ;
       mov dword[_head], eax                   ; в eax -- адрес этого узла

       push eax                                ;
       push ecx                                ;
       ;cinvoke time, 0                         ; генерим случайное число
       ;cinvoke srand, eax                      ;
       cinvoke rand                            ;
       cinvoke rand                            ;
       mov edx, eax                            ;
       pop ecx                                 ;
       pop eax                                 ;

       mov dword[eax + node.data ], edx        ; инициализация начального узла
       ;pushad                                  ;
       ;cinvoke printf, _format_o, edx          ;
       ;popad                                   ;
       mov dword[eax + node.left ], 0d         ;
       mov dword[eax + node.right], 0d         ;

.Cycle:
       push eax                                ;
       push ecx                                ;
       cinvoke rand                            ;
       mov edx, eax                            ;
       pop ecx                                 ;
       pop eax                                 ;

       cmp dword[eax + node.data], edx
       jbe .To_Right                           ;
                                               ; для функций Add_Node_To_Left и Add_Node_To_Right должны быть
.To_Left:                                      ; подготовлены регистры eax -- адрес начального узла и edx -- случайное
       stdcall Add_Node_To_Left, eax           ; значение, после отработки функции возвращают в eax -- адрес
       jmp .End_Cycle                          ; нового узла дерева
                                               ;
.To_Right:                                     ;
       stdcall Add_Node_To_Right, eax          ;

.End_Cycle:
       ;pushad                                  ;
       ;cinvoke printf, _format_ecx, ecx        ;
       ;popad                                   ;

       loop .Cycle

       popad

       mov eax, dword[_head]


.End:
       ret
endp
