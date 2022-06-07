#ifndef __TIMER_H__
#define __TIMER_H__

#include <tools/types.h>

u32 jiffies = 0;

void init_timer(u32 hz);

#endif
