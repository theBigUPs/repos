
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

mov cx , 064h
mov bx , 5000h
mov dx , 01h


l1:

    mov [bx],dx
    inc bx
    inc dx

loop l1
ret




