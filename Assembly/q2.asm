
.MODEL SMALL
.STACK	64
.DATA

prompt1    db  0ah,0dh,'Enter First Num: $'
prompt2   db  0ah,0dh,'Enter Second Num: $'    
m_input         db   db  21, ?, 21 dup(?)
m_output         db    db  22, ?, 22 dup(?)

.CODE
start:
	mov	    ax, @data
	mov	    ds, ax 
 
input_m_input:
    lea     dx,	prompt1
    mov     ah, 9
    int     21h      
    
	lea     dx, m_input
	mov     ah, 0ah
	int     21h      
	mov     di, 1
	mov     si, 1   
	mov     cx, 22   ; loop counter         
	 





check_m_input:     
    sub    m_input[si], '0' ; sub for ascii code
    cmp    m_input[si], 0  
    jl     jj   ; if <0 (no digit) -> jj to move index of input only dec cx and come back to this loop
    cmp    m_input[si], 9  
    jg     jj   ; if >9  same as above  
    MOV  al,m_input[si]
   MOV m_output[di],al 
   add m_output[di],'0'
    inc    si 
    inc    di        
loop check_m_input

jj:
cmp cx, 0
inc si
dec cx
jg check_m_input

	
end_:                 
MOV dl, 10
MOV ah, 02h
INT 21h
MOV dl, 13
MOV ah, 02h
INT 21h   
    mov     m_output[22], '$' 
    lea     dx, m_output[1]
    mov     ah, 9        ; print the result
    int     21h   
	
	mov	    ah, 4ch
	mov	    al, 0
	int	    21H     ; exit
END start
