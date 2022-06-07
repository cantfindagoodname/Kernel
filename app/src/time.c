#include <app/headers/time.h>

#include <cpu/timer.h>

#include <drivers/text_vga.h>

#include <tools/utils.h>
#include <tools/string.h>


static u32 tpoint = 0;
extern u32 jiffies;

void get_time(void *ts)
{
    s8 tbuf[16];
    if (ms_strlen((s8 *)ts) == 0) {
        utoastr(jiffies, tbuf, 10);
        KPRINTN(3, "Uptime: ", tbuf, "\n");
    }
    else if (!ms_strcmp((s8 *)ts, "CHECKPOINT")) {
        tpoint = jiffies;
        utoastr(tpoint, tbuf, 10);
        KPRINTN(3, "Checkpoint placed: ", tbuf, "\n");
    }
    else if (!ms_strcmp((s8 *)ts, "ELAPSED")) {
        s32 diff = jiffies - tpoint;
        utoastr(diff, tbuf, 10);
        KPRINTN(3, "Time since Checkpoint: ", tbuf, "\n");
    }
}
