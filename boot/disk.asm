LOAD_DISK:
        PUSHA
        PUSH    DX

        MOV     AH, 0x02
        MOV     AL, DH          ; Sector to read
        MOV     CH, 0           ; Cylinder
        MOV     DH, 0           ; Head
        MOV     CL, 0x02        ; Sector
        INT     0x13

        JC      DISK_ERROR      ; Hang if error

        POP     DX
        CMP     DH, AL
        JNE     SECT_ERROR      ; Hang if error (read = expected)

        POPA
        RET

DISK_ERROR:
        MOV     BX, MSG_DISK
        CALL    PRINT16
        JMP     HANG_ERROR

SECT_ERROR:
        MOV     BX, MSG_SECT
        CALL    PRINT16
        JMP     HANG_ERROR

HANG_ERROR:
        JMP     $

MSG_DISK    DB "Error : Disk read",0
MSG_SECT    DB "Error : Sectors number",0
