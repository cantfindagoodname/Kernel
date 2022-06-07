CODE_SEG EQU GDT.CODE_DESCRIPTOR - GDT
DATA_SEG EQU GDT.DATA_DESCRIPTOR - GDT

GDT:    
; offset 0x00
.NULL_DESCRIPTOR:
        DQ      0x0
; offset 0x08
.CODE_DESCRIPTOR:
        DW      0xFFFF          ; Limit [0:15]
        DW      0x0             ; Base  [0:15]
        DB      0x0             ; Base  [16:23]
        DB      0x9A            ; [0:4] : Present + Privilege + CS/DS, [5:8] : Code + Conform + Readable + Accessed
        DB      0b11001111      ; [0:4] : Limit granularity 0x1000 + 32-bit default + AVL = 00, [5:8] Limit [16-19]
        DB      0x0             ; Base [24:31]
; offset 0x10
.DATA_DESCRIPTOR:
        DW      0xFFFF          ; Limit [0:15]
        DW      0x0             ; Base  [0:15]
        DB      0x0             ; Base  [16:23]
        DB      0x92            ; [0:4] : Present + Privilege + CS/DS, [5:8] : Code + Expand Down + Writeable + Accessed
        DB      0b11001111      ; [0:4] : Limit granularity 0x1000 + 32-bit default + AVL = 00, [5:8] Limit [16-19]
        DB      0x0             ; Base [24:31]
GDT_END:

GDT_DESC:
        DW      GDT_END - GDT - 1
        DD      GDT

