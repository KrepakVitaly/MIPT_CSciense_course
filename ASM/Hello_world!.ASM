.model tiny
.org 100h
.code
start:
        mov ah, 09h
        mov dx, offset HelloStr
        int 21h
        mov ax, 4c00h
        int 21h
HelloStr        db 'Hello world!', 13, 10, '$,
end start