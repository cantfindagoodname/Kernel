#include <tools/string.h>
#include <tools/types.h>
#include <tools/utils.h>

s32 ms_strlen(s8 *s)
{
    u32 *pt = (u32 *)s;
    for (;DETECT_NULL(*pt) == 0;++pt)
        ;

    const s8 *lpt = (s8 *)pt;
    for (int i = 0;i < 4;++i)
        if (lpt[i] == 0)
            return (s32)pt - (s32)s + (s32)i;
    /* Never Reach Here */
    return -1;
}

void ms_append(s8 *s, s8 c)
{
    s += ms_strlen(s);
    *s++ = c;
    *s = '\0';
}

int ms_strcmp(s8 *s1, s8 *s2)
{
    u32 *pt1 = (u32 *)s1;
    u32 *pt2 = (u32 *)s2;
    for (;!(DETECT_NULL(*pt1) && DETECT_NULL(*pt2));++pt1, ++pt2)
        if (*pt1 != *pt2)
            return 1;

    const s8 *lpt1 = (s8 *)pt1;
    const s8 *lpt2 = (s8 *)pt2;
    for (int i = 0;i < 4;++i) {
        if (!(lpt1[i] && lpt2[i]))
            return (lpt1[i] != lpt2[i]);
        else if (lpt1[i] != lpt2[i])
            return 1;
    }
    /* Never Reach Here */
    return -1;
}

void ms_strncpy(s32 n, s8 *dest, s8 *src)
{
    for (s32 i = 0;src[i] && i < n;++i) {
        dest[i] = src[i];
    }
    dest[n+1] = '\0';
}
