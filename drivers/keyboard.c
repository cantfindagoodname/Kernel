#include <cpu/isr.h>
#include <cpu/ports.h>

#include <drivers/text_vga.h>
#include <drivers/keyboard.h>

#include <tools/utils.h>
#include <tools/string.h>
#include <tools/scancode.h>

#include <shell/shell.h>

static s8 buf[256];

static void keyboard_cb(registers_st r)
{
    /* https://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html */
    u8 scancode = port_byte_in(0x60);
    /* Don't do key up down event */
    if (scancode > 0x39) return;
    /* Backspace */
    if (scancode == 0x0E) {
        buf[ms_strlen(buf)-1]='\0';
        clr1();
    }
    /* Enter */
    else if (scancode == 0x1C) {
        kprint("\n");
        prompt(buf);
        buf[0] = '\0';
    }
    else {
        char ch = scancode_map[scancode][0];
        char key[2] = {ch, '\0'};
        ms_append(buf, ch);
        kprint(key);
    }
    UNUSED(r);
}

void init_keyboard()
{
    register_interrupt_handler(IRQ1, keyboard_cb);
}
