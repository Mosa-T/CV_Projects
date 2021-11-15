;Question 1: 
;- get from user string
;- change the string to upper case string
.MODEL SMALL
.DATA

         string DB  255 DUP(?)
         prompt1  DB  0DH,0AH, ' ENTER THE STRING :  $'
         prompt2 DB  0DH,0AH, ' YOUR STRING IS :  $'
.CODE

START:
          MOV AX,@DATA
          MOV DS,AX

          LEA DX,prompt1
          MOV AH,09H
          INT 21H

          LEA SI,string
          MOV AH,01H
GET_STRING:  
          INT 21H
          MOV BL,AL

          CMP AL,0DH
          JE  PRINT_STRING

          AND AL,0DFh
          MOV [SI],AL
          INC SI

          JMP GET_STRING
PRINT_STRING:

          MOV AL,'$'
          MOV [SI],AL

          LEA DX,prompt2
          MOV AH,09H
          INT 21H

          LEA DX,string
          MOV AH,09H
          INT 21H

          .EXIT
END START 