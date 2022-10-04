
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

.model small

.data

counter dw 0001h
counter2 dw 000ah

.code

l1:
mov cx,counter
    l2:
    
    mov ah, 2
    mov dl, '*'
    int 21h 
    
    
    loop l2


mov ah, 2
mov dl, 0dh
int 21h

mov ah, 2
mov dl, 0ah
int 21h


inc counter


mov cx ,counter2
dec counter2

loop l1


ret

