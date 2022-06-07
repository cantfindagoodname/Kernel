#ifndef __STRING_H__
#define __STRING_H__

#include <tools/types.h>

s32 ms_strlen(s8 *s);
void ms_append(s8 *s, s8 c);
int ms_strcmp(s8 *s1, s8 *s2);
void ms_strncpy(s32 n, s8 *dest, s8 *src);

#endif
