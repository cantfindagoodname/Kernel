#include <drivers/text_vga.h>
#include <tools/types.h>
#include <cpu/ports.h>

/* Private Functions Prototype */
static s32 get_cursor();
static void set_cursor(s32 offset);
static s32 get_screen_offset(s32 x, s32 y); /* get_cursor if x, y < 0 */
static s32 print_char(s8 c, s32 x, s32 y, s8 attribute);

/* Public Functions */
void clrs()
{
    s32 screen_size = NR_CPL * NR_LINE;
    u8 *vbuf = (u8 *)VGA;

    for (s32 i = 0;i < screen_size;++i) {
        vbuf[i << 1] = ' ';
        vbuf[(i << 1) + 1] = BF_BW;
    }
    set_cursor(0);
}

void clr1()
{
    s32 offset = get_cursor();
    if (offset) offset -= 2;
    s32 x = (offset >> 1) % NR_CPL;
    s32 y = (offset >> 1) / NR_CPL;
    print_char(' ', x, y, BF_BW);
    set_cursor(offset);
}

void kprint_at(s8 *msg, s32 x, s32 y)
{
    s32 offset = get_screen_offset(x, y);
    x = (offset >> 1) % NR_CPL;
    y = (offset >> 1) / NR_CPL;

    for (s32 i = 0;msg[i] != '\0';++i) {
        offset = print_char(msg[i], x, y, BF_BW);
        x = (offset >> 1) % NR_CPL;
        y = (offset >> 1) / NR_CPL;
    }
}

void kprint(s8 *msg)
{
    kprint_at(msg, -1, -1);
}

/* Helper Private Functions*/
static s32 get_cursor()
{
    s32 offset;
    port_byte_out(REG_SCREEN_CTRL, 14);
    offset = port_byte_in(REG_SCREEN_DATA) << 8;
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset << 1;     /* Consider attribute */
}

static void set_cursor(s32 offset)
{
    offset >>= 1;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (u8)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (u8)(offset & 0xFF));
}

static s32 get_screen_offset(s32 x, s32 y)
{
    if (x >= 0 && y >= 0)
        return (y * NR_CPL + x) << 1;
    return get_cursor();
}

static s32 print_char(s8 ch, s32 x, s32 y, s8 attribute)
{
    u8 *vbuf = (u8 *)VGA;
    attribute = attribute ? BF_BW : attribute;

    if (x >= NR_CPL || y >= NR_LINE) {
        s32 offset = 2 * NR_CPL * NR_LINE - 2;
        vbuf[offset++] = 'E';
        vbuf[offset] = BF_WR;
        return get_screen_offset(x, y) % (NR_CPL * NR_LINE); /* Wrap Around */
    }

    s32 offset = get_screen_offset(x, y);
    if (ch == '\n') {
        s32 line = (offset / (2 * NR_CPL)) % NR_LINE;           /* Consider (-1,-1) case */
        offset = get_screen_offset(0, line + 1);
    }
    else {
        vbuf[offset++] = ch;
        vbuf[offset++] = attribute;
    }

    if (offset >= (NR_LINE * NR_CPL) << 1) {
        u32 *vs = (u32 *)VGA;
        for (int r = 0;r < NR_LINE - 1;++r)
            for (int c = 0;c < (NR_CPL >> 1);++c, vs++)
                *vs = vs[NR_CPL >> 1];

        for (int c = 0;c < NR_CPL;++c) {
            offset = get_screen_offset(c, NR_LINE-1);
            vbuf[offset] = ' ';
            vbuf[offset + 1] = BF_BW;
        }
        offset = get_screen_offset(0, NR_LINE-1);
    }

    set_cursor(offset);
    return offset;
}
