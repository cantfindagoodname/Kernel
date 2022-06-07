[BITS   16]
[ORG    0x7C00]
KERNEL_OFFSET EQU 0x1000

MOV     [DISK], DL
MOV     BP, 0x9000
MOV     SP, BP

MOV     AH, 0x0
MOV     AL, 0X3
INT     0x10                            ; Go to Text Mode, Clear Screen

MOV     BX, MSG_REAL
CALL    PRINT16

CALL    LOAD_KERNEL
CALL    SWITCH_PM
EXIT:   JMP     $                       ; Never reach here

LOAD_KERNEL:
        MOV     BX, MSG_KERN
        CALL    PRINT16

        MOV     BX, KERNEL_OFFSET
        MOV     DH, 0x1F                ; Number of Sectors to read
        MOV     DL, [DISK]
        CALL    LOAD_DISK
        RET

SWITCH_PM:   
        CLI                             ; Disable Interrupt
        LGDT    [GDT_DESC]              ; Load GDT
        MOV     EAX, CR0
        OR      EAX, 1
        MOV     CR0, EAX                ; Set first bit of CR0 (Control Register)
        JMP     CODE_SEG:CLEAR_PIPE     ; CPU is in 32-bit protected mode
                                        ; Far jump is needed to clear the current pipeline
                                        ; as CPU does not know if instruction in pipeline is 16-bit or 32-bit mode

%include "boot/gdt.asm"
%include "boot/disk.asm"
%include "boot/print_bx.asm"
%include "boot/print_ebx.asm"

[BITS   32]

VIDEO   EQU 0xB8000
BBFW    EQU 0x0F

CLEAR_PIPE:
        MOV     AX, DATA_SEG
        MOV     DS, AX
        MOV     SS, AX
        MOV     ES, AX
        MOV     FS, AX
        MOV     GS, AX
        MOV     EBP, 0x90000
        MOV     ESP, EBP
PRINT:
        MOV     EBX, MSG_PROT
        CALL    PRINT_EBX
KERNEL:
        CALL    KERNEL_OFFSET
HANG:   
        JMP     $

DISK        DB      0
MSG_REAL    DB  "HELLO 16BITS",0
MSG_PROT    DB  "HELLO 32BITS",0
MSG_KERN    DB  "LOAD KERNEL",0

TIMES   510-($-$$) DB       0
DW      0xAA55
