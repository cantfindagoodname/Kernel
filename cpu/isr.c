#include <cpu/idt.h>
#include <cpu/isr.h>
#include <cpu/ports.h>
#include <cpu/timer.h>

#include <drivers/keyboard.h>
#include <drivers/text_vga.h>

#include <tools/utils.h>

#define SET_GATE_ISR(N) set_gate(N, (u32)isr##N)
#define SET_GATE_IRQ(N1, N2) set_gate(N1, (u32)irq##N2)

/* IVT from https://wiki.osdev.org/Interrupt_Vector_Table */
static char *em[] = {
    "Divide by 0",
    "Reserved"
    "Non-Maskable Interrupt",
    "Breakpoint",
    "Overflow (INT 00)",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "Reserved",

    "x87 FPU Error",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
};

void isr_install()
{
    SET_GATE_ISR(0);
    SET_GATE_ISR(1);
    SET_GATE_ISR(2);
    SET_GATE_ISR(3);
    SET_GATE_ISR(4);
    SET_GATE_ISR(5);
    SET_GATE_ISR(6);
    SET_GATE_ISR(7);
    SET_GATE_ISR(8);
    SET_GATE_ISR(9);
    SET_GATE_ISR(10);
    SET_GATE_ISR(11);
    SET_GATE_ISR(12);
    SET_GATE_ISR(13);
    SET_GATE_ISR(14);
    SET_GATE_ISR(15);
    SET_GATE_ISR(16);
    SET_GATE_ISR(17);
    SET_GATE_ISR(18);
    SET_GATE_ISR(19);
    SET_GATE_ISR(20);
    SET_GATE_ISR(21);
    SET_GATE_ISR(22);
    SET_GATE_ISR(23);
    SET_GATE_ISR(24);
    SET_GATE_ISR(25);
    SET_GATE_ISR(26);
    SET_GATE_ISR(27);
    SET_GATE_ISR(28);
    SET_GATE_ISR(29);
    SET_GATE_ISR(30);
    SET_GATE_ISR(31);

    /* https://wiki.osdev.org/PIC#Protected_Mode */
    port_byte_out(0x20, 0x11);
    port_byte_out(0xA0, 0x11);
    port_byte_out(0x21, 0x20);
    port_byte_out(0xA1, 0x28);
    port_byte_out(0x21, 0x04);
    port_byte_out(0xA1, 0x02);
    port_byte_out(0x21, 0x01);
    port_byte_out(0xA1, 0x01);
    port_byte_out(0x21, 0x0);
    port_byte_out(0xA1, 0x0);

    SET_GATE_IRQ(32, 0);
    SET_GATE_IRQ(33, 1);
    SET_GATE_IRQ(34, 2);
    SET_GATE_IRQ(35, 3);
    SET_GATE_IRQ(36, 4);
    SET_GATE_IRQ(37, 5);
    SET_GATE_IRQ(38, 6);
    SET_GATE_IRQ(39, 7);
    SET_GATE_IRQ(40, 8);
    SET_GATE_IRQ(41, 9);
    SET_GATE_IRQ(42, 10);
    SET_GATE_IRQ(43, 11);
    SET_GATE_IRQ(44, 12);
    SET_GATE_IRQ(45, 13);
    SET_GATE_IRQ(46, 14);
    SET_GATE_IRQ(47, 15);

    set_idt();
}

void irq_install()
{
    __asm__ __volatile__("sti");
    init_timer(50);
    init_keyboard();
}

void isr_handler(registers_st r)
{
    char nr_reg[3];
    utoastr(r.nr_int, nr_reg, 2);
    KPRINTN(5, "Trigger Interrupt: ", nr_reg, "\n", em[r.nr_int], "\n");
}

void irq_handler(registers_st r)
{
    /* > 7 */
    if (r.nr_int >= 40)
        port_byte_out(0xA0, 0x20);
    port_byte_out(0x20, 0x20);

    if (interrupt_handlers[r.nr_int]) {
        void (*handler)(registers_st) = interrupt_handlers[r.nr_int];
        handler(r);
    }
}

void register_interrupt_handler(u8 n, void (*handler)(registers_st))
{
    interrupt_handlers[n] = handler;
}
