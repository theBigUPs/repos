org 100h


.data
    
num dw 0042h
res dw 0000h

.code

mov ax,num
xor ax,0ffffh
add ax,0001h
mov res,ax

ret




