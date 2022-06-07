#ifndef __IDT_H__
#define __IDT_H__

#include <tools/types.h>

#define KERNEL_CS 0x8

struct idt_entry_s {
    u16 lo;
    u16 sel;
    u8 always0;
    u8 flags;
    u16 hi;
} __attribute__((packed));
typedef struct idt_entry_s idt_gate_st;

struct idt_pointer_s {
    u16 limit;
    u32 base;
} __attribute__((packed));
typedef struct idt_pointer_s idt_register_st;

/* 256 or CPU Panic */
#define IDT_ENTRIES 256
idt_gate_st idt[IDT_ENTRIES];
idt_register_st idt_reg;

void set_gate(s32 n, u32 set);
void set_idt();

#endif
