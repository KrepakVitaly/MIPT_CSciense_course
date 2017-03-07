format PE
entry main

section '.idata' data import readable
include "win32ax.inc"
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
cinvoke   puts, _hello

;scanf ("%d", &num1);
cinvoke  scanf, _format_i, num1

cmp	 eax, 1
jne	 error

;puts
cinvoke  puts, _prompt2

;scanf
cinvoke  scanf, _format_i, num2
cmp	eax, 1
jne	error

;average
mov	eax, [num1]
add	eax, [num2]
shr	eax, 1

;printf
cinvoke printf, _format_o, eax

;getch
cinvoke getchar
cinvoke getchar

;exit (o)
cinvoke exit, 0

error:
;puts _error
cinvoke puts, _error
;exit -1
cinvoke exit, -1

