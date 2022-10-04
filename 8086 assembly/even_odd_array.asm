

org 100h

.data

array dw 0005h, 0008h, 0003h, 0005h, 0007h


.code

mov ax,@data
mov ds,ax
mov si, offset array
mov cx,0005h


;converts the value in the array location to 0 if even 1 if odd
;
up:

mov dx,[si]

mov ax,dx
mov dx,0000h
mov bx,0002h 
div bx
mov [si],dx


inc si
inc si

loop up



ret




