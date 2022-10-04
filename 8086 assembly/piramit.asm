
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt
org 100h

.model small

.data

counter1 dw 000ah
counter2 dw 0001h

.code

mov cx,counter1

l1:   
    l2:;spaces
    
    mov ah, 0002h
    mov dl, ' '
    int 021h
    
    loop l2
    
    
    mov cx,counter2
    l3:;stars
    
    mov ah, 0002h
    mov dl, '*'
    int 021h
    
    loop l3
    add counter2,0002h

mov ah, 0002h
mov dl, 000dh
int 021h

mov dl, 000ah
int 21h


mov cx,counter1
dec counter1
loop l1
ret




