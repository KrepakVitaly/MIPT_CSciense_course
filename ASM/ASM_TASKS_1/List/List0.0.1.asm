;##########################################
;#  project:    "List"                   ##
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

size_elmnt = 12d
NEW_LINE = 0Ah

;________________________________________________________

_format_o       db "Random number = %d ",  NEW_LINE, 0
_format_ecx     db "ecx = %d ",  NEW_LINE, 0
_format_elmnt   db "Element = %d ",  NEW_LINE, 0
_format_addr    db "Addr of Element = %d ",  NEW_LINE, 0
_format_data    db "Data of Element = %d ",  NEW_LINE, 0
_format_iter    db "Iterator = %d ",  NEW_LINE, 0
_format_max     db "Max value = %d ",  NEW_LINE, 0
_format_min     db "Min value = %d ",  NEW_LINE, 0

;______________VARIABLES_________________________________

struct list
        data    dd ?
        next    dd ?
ends

size   dd 10d

;______________DATA_SECTION_END__________________________

;________________________________________________________

section  '.text' code readable executable
main:

       stdcall Create_List, dword[size]
       stdcall Print_List,  eax
       stdcall Find_Min_and_Max, eax
       call [getchar]

       cinvoke exit, 0

;________________________________________________________
;________________________________________________________

proc Create_List stdcall uses edx ecx,  _size:DWORD
     locals
       _cur    dd 0
       _head   dd 0
       _rand_val dd 0
     endl
       mov ecx, dword[_size]
       mov eax, 0
       cmp ecx, 0
       jle .End

       pushad
       cinvoke malloc, sizeof.list            ; выделяем память под начало списка
       mov dword[_head] , eax                 ; в eax -- адрес начала списка

       pushad
       cinvoke time, 0
       cinvoke srand, eax
       cinvoke rand
       cinvoke rand
       mov dword[_rand_val], eax
       popad

       mov edx, dword[_rand_val]

       mov dword[eax + list.data], edx         ; инициализация "головы" списка
       mov dword[eax + list.next], 0d
       popad

       mov eax, dword[_head]

       mov ecx, dword[_size]
       dec ecx
       jz .End

.Another_Elmnt:
       stdcall Add_Random_Elmnt_to_end, eax
       loop .Another_Elmnt


.End:
       ret
endp

;________________________________________________________
;________________________________________________________


proc Add_Random_Elmnt_to_end stdcall uses edx eax, _ptr:DWORD   ; _ptr -- указатель на начало списка
     locals
       _cur    dd 0
       _last   dd 0
       _rand_val dd 0
     endl

       mov eax, dword[_ptr]             ; eax -- указатель на начало списка

.Rewind:                                ; отматываем список до конца
       mov dword[_last], eax            ; текущий элемент становиться последним
       mov eax, dword[eax + list.next]  ; копируем адрес следующего



       cmp eax, 0                       ; если не ноль то продолжаем цикл
       jne .Rewind


       pushad
       cinvoke malloc, sizeof.list      ; если eax = 0, то мы дошли до конца списка
       mov dword[_cur], eax             ; теперь в eax -- адрес нового элемента
       popad

       mov eax, dword[_cur]
       mov edx, dword[_last]
       mov dword[edx + list.next], eax

       pushad
       cinvoke rand
       mov dword[_rand_val], eax
       popad

       mov edx, dword[_rand_val]

       mov dword[eax + list.data], edx        ; инициализация
       mov dword[eax + list.next], 0d

       ;pushad
       ;cinvoke printf, _format_data, edx
       ;popad

       ret
endp

;________________________________________________________


proc Add_Random_Elmnt_to_begin  stdcall uses edx, _ptr:DWORD
     locals
       _cur    dd 0
       _last   dd 0
      _rand_val dd 0
     endl

       pushad
       cinvoke malloc, sizeof.list      ;
       mov dword[_cur], eax             ; теперь в eax -- адрес нового элемента
       popad

       mov eax, dword[_cur]
       mov edx, dword[_ptr]



       mov dword[eax + list.next], edx
       pushad
       cinvoke rand
       mov dword[_rand_val], eax
       popad

       mov edx, dword[_rand_val]
       mov dword[eax + list.data], edx        ; инициализация

       ret
endp

;________________________________________________________


proc Print_List stdcall uses eax,_head:DWORD
     locals
        _cur dd 0
     endl

        mov eax, dword[_head]           ; в eax -- начало списка
        mov dword[_cur], eax            ; текущий -- начальный
        cmp eax, 0
        jbe .End

.Cycle:
        ;pushad
        ;cinvoke printf, _format_addr , eax
        ;popad
        pushad
        cinvoke printf, _format_data , dword[eax + list.data]
        popad

        mov eax, dword[eax + list.next] ; в eax -- адрес следующего
        cmp eax, 0
        jne .Cycle

.End:
        ret
endp

;________________________________________________________

proc Find_Min_and_Max stdcall uses eax, _head:DWORD
        cmp dword[_head], 0
        jle .End

        mov eax, dword[_head]           ; в ecx -- адрес начала списка
        mov edx, 10000000000000000000000000000001b            ; в edx -- наименьшее возможное значение
        mov ecx, 01111111111111111111111111111111b            ; в ecx -- наибольшее значение

.Loop:
        cmp edx, dword[eax + list.data]
        jge  .Inact_max
        mov edx, dword[eax + list.data]
.Inact_max:

        cmp ecx, dword[eax + list.data]
        jle  .Inact_min
        mov ecx, dword[eax + list.data]
.Inact_min:

        cmp dword[eax + list.next], 0
        jle .End

        mov eax, dword[eax + list.next]
        jmp .Loop

.End:
        pushad
        cinvoke printf, _format_max, edx
        popad
        pushad
        cinvoke printf, _format_min, ecx
        popad
        ret
endp
;________________________________________________________
