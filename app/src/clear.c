#include <app/headers/clear.h>

#include <tools/utils.h>

#include <drivers/text_vga.h>

void clear_screen(void *arg)
{
    clrs();
    UNUSED(arg);
}
