#ifndef __UTILS_H__
#define __UTILS_H__

#include <tools/types.h>

#define UNUSED(x) (void)(x)

#define DETECT_NULL(X) (((X) -0x01010101) & ~(X) & 0x80808080)
#define DETECT_CHAR(X, M) (DETECT_NULL(X ^ (((u8)M) * 0x01010101)))

void utoastr(s32 n, char *str, u16 d);
u32 strtou(char *str);

#endif
