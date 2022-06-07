[BITS   32]
; Print 0 terminated string starting from EBX
PRINT_EBX:
        PUSHA
        MOV     EDX, VIDEO
.LOOP:
        MOV     AL, [EBX]
        MOV     AH, BBFW
        CMP     AL, 0
        JE      LRET
        MOV     [EDX], AX
        INC     EBX
        ADD     EDX, 2
        JMP     .LOOP
LRET:
        POPA
        RET

