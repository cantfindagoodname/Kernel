[EXTERN isr_handler]
[EXTERN irq_handler]

ISR_COMMON_STUB:
        PUSHA
        MOV     AX, DS
        PUSH    EAX

        MOV     AX, 0x10
        MOV     DS, AX
        MOV     ES, AX
        MOV     FS, AX
        MOV     GS, AX

        CALL    isr_handler

        POP     EAX
        MOV     DS, AX
        MOV     ES, AX
        MOV     FS, AX
        MOV     GS, AX
        POPA
        ADD     ESP, 0x8
        STI
        IRET

IRQ_COMMON_STUB:
        PUSHA
        MOV     AX, DS
        PUSH    EAX

        MOV     AX, 0x10
        MOV     DS, AX
        MOV     ES, AX
        MOV     FS, AX
        MOV     GS, AX

        CALL    irq_handler

        POP     EBX
        MOV     DS, BX
        MOV     ES, BX
        MOV     FS, BX
        MOV     GS, BX
        POPA
        ADD     ESP, 0x8
        STI
        IRET

%MACRO ISR 2 ; ISR number, ISR number
    [GLOBAL isr%1]
    isr%1:
        CLI
        PUSH    BYTE 0
        PUSH    BYTE %2
        JMP     ISR_COMMON_STUB
%ENDMACRO

ISR 0, 0
ISR 1, 1
ISR 2, 2
ISR 3, 3
ISR 4, 4
ISR 5, 5
ISR 6, 6
ISR 7, 7
ISR 8, 8
ISR 9, 9
ISR 10, 10
ISR 11, 11
ISR 12, 12
ISR 13, 13
ISR 14, 14
ISR 15, 15
ISR 16, 16
ISR 17, 17
ISR 18, 18
ISR 19, 19
ISR 20, 20
ISR 21, 21
ISR 22, 22
ISR 23, 23
ISR 24, 24
ISR 25, 25
ISR 26, 26
ISR 27, 27
ISR 28, 28
ISR 29, 29
ISR 30, 30
ISR 31, 31

%MACRO IRQ 2 ; IRQ number, ISR number map
    [GLOBAL irq%1]
    irq%1:
        CLI
        PUSH    BYTE 0
        PUSH    BYTE %2
        JMP     IRQ_COMMON_STUB
%ENDMACRO

IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47
