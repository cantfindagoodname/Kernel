#include <tools/string.h>
#include <tools/types.h>
#include <tools/utils.h>

void utoastr(s32 n, char *str, u16 d)
{
    if (d == 0) return;
    utoastr(n/10, str, d-1);
    str[d-1] = (n%10) + '0';
    str[d] = '\0';
}

u32 strtou(char *str)
{
    u32 ret = 0, c = 1;
    for (s32 i = (s32)ms_strlen(str)-1;i >= 0;--i, c*=10) {
        ret += c * (str[i] - '0');
    }
    return ret;
}
