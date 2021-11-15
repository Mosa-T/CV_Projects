;input - two numbers
;output - the quotient and the remainder

.MODEL	SMALL
.STACK	20
.DATA
	prompt	db	"Please enter a number:", 0dh, 0ah, "$"
	new_line	db	 0dh, 0ah, "$"
	the_number	db 16 dup(0), '$' ;printInt PROC prints the numbers in this string
	num1 dw 01
	num2 dw 01  
	reminder dw 0   
.CODE

BASE = 10

start:
	mov	ax, @DATA
	mov	ds, ax
	
	;print first prompt
	mov	ah, 09	
	lea	dx, prompt
	int	21H
	
	call getInt
	mov num1, ax
	
	;print new line 
	mov	ah, 09	
	lea	dx, new_line
	int	21H
	
	;print second prompt
	mov	ah, 09	
	lea	dx, prompt
	int	21H
	
	call getInt
	mov num2, ax
	
	;print new line 
	mov	ah, 09	
	lea	dx, new_line
	int	21H
	
	 
	xor bx, bx ;bx=0
	mov bx, num2
	cmp num1, bx
	jl lower 
	
	; if num1 bigger than num2
	
	xor ax, ax  ; ax =0 (for quotient) 
	xor dx, dx  ; dx=0 (fpr remainder)
	
	mov ax, num1
	div num2
	
	mov reminder, dx ; save the remainder before dx will change
	lea bx, the_number ;save the quotient in the_number and call printInt 
	
	mov [bx],ax 
	    ;print the quotient	
	call printInt 

	;print new line 
	xor dx, dx
	mov	ah, 09	
	lea	dx, new_line
	int	21H            
 
    ;print the remainder     
	mov [bx],word ptr 0H
	mov dx, reminder  
	mov [bx], dx  ;save the reminder in the_number and call printInt
	
	xor ax, ax ;ax=0
	
	mov ax, reminder
	call printInt
	
	jmp next
	;if num2 is bigger than num1
	lower:
	xor ax, ax ; ax =0 (for quotient)
	xor dx, dx ; dx=0 (for remainder)
	mov ax, bx
	div  num1 
	mov reminder, dx ;must to save the remainder before dx will change
	lea bx, the_number
	mov [bx],ax
	
    ;print the quotient
	call printInt   
	
    ;print the remainder
	xor dx, dx
	mov	ah, 09	
	lea	dx, new_line
	int	21H            

	;print the remainder     
	mov [bx],word ptr 0H
	mov dx, reminder
	mov [bx], dx   ;save the reminder in the_number and call printInt
	xor ax, ax ;ax=0
	mov ax, reminder
	call printInt
	
	next:
	;print new line 
	xor dx, dx
	mov	ah, 09	
	lea	dx, new_line
	int	21H
	;end program
    mov     ah, 4CH
    mov     al, 0
    int     21H
 
;printInt gets a number in ax and print it to screen
printInt	PROC
	mov	cx, BASE
	lea	si, the_number
	add	si, 16-1	; point to end of number string
    
	next_digit:
    xor	dx, dx ;dx=0
	div	cx
	add	dx, '0'	;convert to ASCII
	mov	[si], dl
	cmp	ax, 0	;when number is 0, exit
	
	je	print
	dec	si
	
	jmp	next_digit
    
	print:
    	mov	ah, 09
    	mov	dx, si
    	int	21h
    	ret
ENDP
 
;gets a number from user (stream of digits) and return the number in ax
getInt   PROC
	xor	dx, dx ;dx=0
	xor	bx, bx ;bx=0
	
	new_digit:
	mov	ah, 1
	int 	21H
	
	;check if a digit
	cmp	al, '0'
	jl	end_number
	cmp	al, '9'
	jg	end_number
	
	;convert digit to value
	sub	al, '0'
	mov	cl, al
	xor	ch, ch
	mov	ax, BASE
	mul	bx
	mov	bx, ax
	add	bx, cx
	jmp	new_digit
	
	end_number:
 	mov	ax, bx
 	ret
ENDP	

END start

