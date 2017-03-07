format PE
entry main

section '.idata' data import readable
include "macro\import32.inc"
library msvcrt, 'MSVCRT.DLL'
import msvcrt,\
printf, 'printf',\
scanf, 'scanf',\
puts, 'puts',\
getchar, 'getchar',\
exit, 'exit'

section '.data' data readable writable
new_line = 0Ah

_hello	   db "Hello!", new_line, "Please type a number: ", 0
_prompt2   db "Type another number: ", 0
_format_i  db "%d", 0
_format_o  db "Average of the number is %d", new_line, 0
_error	   db "Error!", new_line, 0

num1	   dd ?
num2	   dd ?

section  '.text' code readable executable
;puts("Hello!\n...:");
main:
push	_hello
call	[puts]
add	esp, 4

;scanf ("%d", &num1);
push   num1
push   _format_i
call   [scanf]
add    esp, 8

cmp    eax, 1
jne    error

;puts
push	_prompt2
call	[puts]
add	esp, 4

;scanf
push	num2
push	_format_i
call	[scanf]
add	esp, 8
cmp	eax, 1
jne	error

;average
mov	eax, [num1]
add	eax, [num2]
shr	eax, 1

;printf
push	eax
push	_format_o
call	[printf]
add	esp, 8

;getch
call [getchar]
call [getchar]

;exit (o)
push 0
call [exit]

error:
;puts _error
call [puts]
add esp,4
;exit -1
push -1
call [exit]

