#include <app/headers/fib.h>

#include <drivers/text_vga.h>

#include <tools/types.h>
#include <tools/utils.h>
#include <tools/string.h>

void fib(void *arg)
{
    u32 n = strtou((s8 *)arg);
    u32 a = 0, b = 1;
    for (s32 i = 32 - __builtin_clz(n);i >= 0;--i) {
        u32 t1 = a * (2*b - a);
        u32 t2 = b*b + a*a;
        a = t1;
        b = t2;
        if (n & (1 << i)) {
            t1 = a + b;
            a = b;
            b = t1;
        }
    }
    char ascii[12], in[3];
    utoastr(n, in, 2);
    utoastr(a, ascii, 11);
    KPRINTN(5, "Fib", in, " ", ascii, "\n");
}
