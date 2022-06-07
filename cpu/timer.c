#include <cpu/isr.h>
#include <cpu/ports.h>
#include <cpu/timer.h>

#include <tools/utils.h>

static void timer_cb(registers_st r)
{
    ++jiffies;
    UNUSED(r);
}

void init_timer(u32 hz)
{
    register_interrupt_handler(IRQ0, timer_cb);

    /* https://wiki.osdev.org/Programmable_Interval_Timer */
    u32 divisor = (7159093) / (6 * hz);
    u8 lo = (u8)(divisor & 0xFF);
    u8 hi = (u8)((divisor >> 8) &0xFF);

    port_byte_out(0x43, 0x36);
    port_byte_out(0x40, lo);
    port_byte_out(0x40, hi);
}
