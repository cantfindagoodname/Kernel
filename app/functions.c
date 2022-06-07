#include <kernel/kernel.h>

#include <tools/string.h>

#include <app/functions.h>
#include <app/headers/fib.h>
#include <app/headers/time.h>
#include <app/headers/clear.h>

void init_functions()
{
    set_func(QUIT, _exit, "QUIT", "Halt the Program\n");
    set_func(TIME, get_time, "TIME", "TIME [ CHECKPOINT | ELAPSED ]\n");
    set_func(FIB, fib, "FIB", "FIB [n]\n");
    set_func(CLR, clear_screen, "CLEAR", "Clear Screen\n");
}
