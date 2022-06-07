PRINT16:
        PUSHA
.LOOP:
        MOV     AL, [BX]
        CMP     AL, 0
        JE      PRINT16.RETURN
        MOV     AH, 0x0E
        INT     0x10
        INC     BX
        JMP     PRINT16.LOOP
.RETURN:
        POPA
        RET
