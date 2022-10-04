

org 100h

;(32F - 32) * 5/9 

.data
    
fahrenheit dw 0064h
celcius dw 0000h

.code

mov ax,fahrenheit
sub ax,0020h
mov bx,0005h
mul bx
mov bx,0009h
div bx
mov celcius,ax

ret




