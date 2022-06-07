#include <kernel/kernel.h>

#include <shell/shell.h>

#include <drivers/keyboard.h>
#include <drivers/text_vga.h>

#include <tools/utils.h>

#include <cpu/timer.h>
#include <cpu/isr.h>
#include <cpu/idt.h>

#include <app/functions.h>

void _start()
{
    isr_install();
    irq_install();
    init_functions();

    clrs();
    kprint("> ");
}

void _exit(void *arg)
{
    kprint("Program Halted...\n");
    __asm__ __volatile__("HLT");
    UNUSED(arg);
}
