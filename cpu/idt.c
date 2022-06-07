#include <cpu/idt.h>

void set_gate(s32 n, u32 set)
{
    idt[n].lo = set & 0x0FFFF;
    idt[n].sel = KERNEL_CS;
    idt[n].always0 = 0;
    idt[n].flags = 0x8E;
    idt[n].hi = (set >> 16) & 0x0FFFF;
}

void set_idt()
{
    idt_reg.base = (u32)&idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_st) - 1;

    __asm__ __volatile__(
        "lidtl (%0)"
        :
        : "r"   (&idt_reg)
    );
}
