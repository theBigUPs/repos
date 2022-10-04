org 100h


.data
    
binary db 0014h
grey db 0000h

.code

mov al,binary
shr al,0001h
xor al,binary
mov grey,al

ret




