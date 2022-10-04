
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

.data
    
    str1 DB 255 DUP('$')
    str2 db 20 dup('$')
    op1 dw 0000h  ;word 16bit
    op2 dw 0000h
    order dw 0000h
    operation dw 0000h
    power dw 000ah 
    res dw 0000h
    prev dw 0000h
    remainder dw 0000h
    carry dw 0000h

.code
    
     MOV AX,@DATA
     MOV DS,AX
    
     LEA SI,STR1
     lea di ,str2
     MOV AH,01H   
     ;mov di,si  ; di has the beginning si has the end cx has length
    
       
READ proc
          INT 21H
          CMP AL,0dh      ;cariage return = 0dh
          
          JE convert 
          MOV [SI],AL
          inc bx
          INC SI
        call READ
        
      READ  endp





convert:
mov cx,0000h
mov cx,bx
mov ax,0001h
mov bx,0000h
mov dx,0000h



str_to_num:
dec si
mov bx,[si]
mov bh,00h

cmp bx,02ah ;2a:*
je op
cmp bx,02bh ;2b:+ 
je op
cmp bx,02dh ;2d:- 
je op
cmp bx,02fh ;2f:/
je op

sub bx,030h
mov prev,ax
mul bx

cmp order,0001h
je change_op
add op2,ax
jmp same_op
change_op:
add op1, ax
same_op:


mov ax,prev
mul power
mov prev,ax

op_rec:
loop str_to_num
jmp calculation




op:
;dec cx maybe
mov operation,bx
inc order
mov ax,0001h
mov power,000ah
jmp op_rec






calculation:

cmp operation,02ah ;2a:*
je multiply
cmp operation,02bh ;2b:+ 
je addition
cmp operation,02dh ;2d:- 
je subtraction
cmp operation,02fh ;2f:/
je division


addition:
mov dx ,op2
add op1,dx
mov dx,op1
mov res,dx
jmp to_str


multiply:
mov ax ,op2
mul op1
mov op1,ax
mov dx,op1
mov res,dx
jmp to_str


subtraction:
mov dx ,op2
sub op1,dx
mov dx,op1
mov res,dx
jmp to_str


division:;remainder goes to the dx register
;mov dx,0000h
mov ax ,op1
;xor dx, dx
div op2
mov dx,ax
mov res,ax

jmp to_str
;cmp di,si
;je write_string








to_str:; remainder in dx
push 0040h ;ascii @
mov bx,000ah




continue:
mov ax,res
xor dx, dx
div bx
mov res,ax
mov remainder,dx
push remainder
cmp res , 0000h
jne continue
;je to_dec
;cmp dx,000bh
;je to_dec
;cmp dx,000ch
;je to_dec
;cmp dx,000dh
;je to_dec
;cmp dx,000eh
;je to_dec
;cmp dx,000fh
;je to_dec





write:
pop ax
cmp ax,0040h
je write_string
add al,0030h
mov [di],al
inc di
jmp write







write_string:
    MOV AH, 2                    ; 
    MOV DL, 0ah ;newline
    INT 21H


 
    ; load address of the string 
    LEA DX,str2 
  
    ;output the string
    ;loaded in dx 
    MOV AH,09H
    INT 21H
    mov ah,4ch
    int 21h





ret


