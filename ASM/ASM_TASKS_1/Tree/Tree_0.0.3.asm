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
_format_eax     db "eax = %d ",  NEW_LINE, 0
_format_elmnt   db "Element = %d ",  NEW_LINE, 0
_format_addr    db "Addr of Element = %d ",  NEW_LINE, 0
_format_data    db "Data of Element = %d ",  NEW_LINE, 0
_format_data_r  db "Data Right of Element = %d",  NEW_LINE, 0
_format_data_l  db "Data Left  of Element = %d",  NEW_LINE, 0
_format_max     db "Max value = %d ",  NEW_LINE, 0
_format_min     db "Min value = %d ",  NEW_LINE, 0
_format_left    db "Left",  NEW_LINE, 0
_format_right   db "Right",  NEW_LINE, 0
_format_home    db "Home",   NEW_LINE, 0
_format_tree    db "%*s%d", NEW_LINE, 0
_format_newline db " ", NEW_LINE, 0
_mem_error      db "Not enough memory or error of memory allocation!", NEW_LINE, 0

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

       stdcall Create_Bin_Tree_New, dword[size]
       stdcall Print_Tree_New,  eax
       call [getchar]
       cinvoke exit, 0

;________________________________________________________
;________________________________________________________

proc Print_Tree_New stdcall uses ebx , _head:DWORD
       mov ebx, -1
       stdcall Print_Tree_Without_Init_EBX, dword[_head]
       pushad
       cinvoke printf, _format_newline
       popad
       ret
endp

;________________________________________________________

proc Print_Tree_Without_Init_EBX stdcall _head:DWORD

       inc ebx
       mov eax, dword[_head]

       cmp dword[eax + node.left], 0
       jbe .Next
       mov eax, dword[eax + node.left]
       stdcall Print_Tree_Without_Init_EBX, eax
       mov eax, dword[_head]
.Next:
       pushad                                                          ;
       cinvoke printf, _format_tree, ebx, '', dword[eax + node.data]  ;
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
;________________________________________________________

proc Create_Bin_Tree_New stdcall uses edx ecx ebx,  _size:DWORD
     locals
       _cur      dd 0
       _head     dd 0
     endl
       mov eax, 0
       mov ecx, dword[_size]                   ; проверка на правильность ввода
       cmp ecx, 0                              ; количества элементов дерева
       jle .End                                ;

       push eax                                ;
       push ecx                                ; подготовка к генерации
       cinvoke time, 0                         ; случайного числа
       cinvoke srand, eax                      ;
       cinvoke rand                            ;
       mov edx, eax                            ;
       pop ecx                                 ;
       pop eax                                 ;

.Cycle:
       push eax                                ;
       push ecx                                ;
       cinvoke rand                            ;
       mov edx, eax                            ;
       pop ecx                                 ;
       pop eax

       push ecx
       stdcall AddNodeToTreeWithSort_Val_in_EDX,  eax
       pop ecx

       loop .Cycle

.End:
       ret
endp
;___________________________________________________________________
;    Функция добавляет узел в дерево в зависимости от
;    его значения, если записываемое значение меньше или равно
;    значения в текущем узле, то узел добавляется в
;    правое поддерево, иначе в левое.
;    Если создался новый узел, то адрес на него передается через EAX
;    Если узел не создался, то EAX = 0

proc AddNodeToTreeWithSort_Val_in_EDX stdcall  _cur:DWORD
     locals
       _new      dd 0
     endl

       mov eax, dword[_cur]
       cmp eax, 0                               ; если адрес на текущий элемент нулевой, то его нужно создать
       jbe .Record

       cmp dword[eax + node.data], edx          ; решаем, куда двигаться: влево или вправо?
       jbe .To_Right

.To_Left:
       mov eax, dword[eax + node.left]
       stdcall AddNodeToTreeWithSort_Val_in_EDX,  eax
       cmp eax, 0
       jbe .End
       push ebx
       mov ebx, eax
       mov eax, dword[_cur]
       mov dword[eax + node.left], ebx
       pop ebx
       ret

.To_Right:
       mov eax, dword[eax + node.right]
       stdcall AddNodeToTreeWithSort_Val_in_EDX,  eax
       cmp eax, 0
       jbe .End
       push ebx
       mov ebx, eax
       mov eax, dword[_cur]
       mov dword[eax + node.right], ebx
       pop ebx
       ret

.Record:
       push edx
       cinvoke malloc, sizeof.node
       pop edx                                 ; выделяем память под узел, в eax -- адрес этого узла
       mov dword[eax + node.data ], edx        ; инициализация узла
       mov dword[eax + node.left ], 0d         ;
       mov dword[eax + node.right], 0d         ;

.End:
       ret
endp