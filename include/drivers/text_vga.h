#ifndef __TEXT_VGA__
#define __TEXT_VGA__

#include <tools/types.h>

#define VGA 0xB8000
#define NR_LINE 25
#define NR_CPL 80   // Character Per Line
#define BF_BW 0x0F
#define BF_WR 0xF4

#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

#define KPRINTN(N, ...)                             \
    do {                                            \
        for (int _i = 0;_i < N;++_i)                \
            kprint(((s8 *[]){__VA_ARGS__})[_i]);    \
    } while(0)

void clrs();
void clr1();
void kprint_at(s8 *msg, s32 x, s32 y);
void kprint(s8 *msg);

#endif
