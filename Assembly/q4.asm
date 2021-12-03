;input - 10 email string addresses
;output - check if @ in the string
.MODEL SMALL
.STACK 100
.DATA
	prompt1	        db	"Please enter email address :$"
	prompt2        db  "The Address is not an email address$"                    
	prompt4 db "Email was proper!$"
	prompt3 db "We've reach the maximum emails allowed to be entered, goodbye$"
	new_line	db	 0dh, 0ah, "$"
	string	db	30, ?, 31 dup ('$')  
	counter     dw 10 
	zero        dw 0H 
	one         dw 01H
.CODE

     
check_mail PROC
    xor ax,ax
    check_str:
        mov dl,byte ptr[si]
		cmp dl,'@'
		jne done_check
		inc ax
	done_check:
	    inc si
	loop check_str
	cmp one, ax
	je proper
    jne returnProc
    proper:
    mov	ah, 09	;print prompt1
	lea	dx, prompt4
	int	21H    
	lea	dx, new_line ;print new line
	mov	ah, 09
	int	21H      
	mov ax, 1
	call return      
	returnProc:
	call return

ENDP        

main:
	mov	ax, @data
	mov	ds, ax
	xor bx, bx
	mov bx, 3
	
 get_emails:
    cmp counter, 0
    je the_end
    dec bx
	mov	ah, 09	;print prompt1
	lea	dx, prompt1
	int	21H
	
	lea	dx, new_line ;print new line
	mov	ah, 09
	int	21H
	
	mov	ah, 0ah	; get string
	lea	dx, string
	int	21H
	
	lea	dx, new_line ;print new line
	mov	ah, 09
	int	21H
	
	mov si,offset string+1
	mov ch,0
	mov cl,byte ptr[si] ; puts number of chars in cx
	inc si
	sub counter, 1
	call check_mail  
	
	return PROC
	ENDP          
	
	cmp one, ax
	
	jne print_prompt2
	
	je get_emails
	
	print_prompt2:
	    lea	dx, prompt2 ;print prompt2
	    mov	ah, 09
	    int	21H
	    lea	dx, new_line ;print new line
	    mov	ah, 09
	    int	21H  
	    
 loop get_emails  
 the_end:  
    lea	dx, new_line ;print new line
	mov	ah, 09
	int	21H
    mov	ah, 09	;print prompt1
	lea	dx, prompt3
	int	21H
	mov	ah, 4ch
	int	21H
	
END main	    