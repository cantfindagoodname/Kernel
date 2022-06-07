#include <drivers/text_vga.h>
#include <tools/string.h>
#include <tools/utils.h>

/* currently 2 arguments (more after malloc) */
static void scan(char *input, char *output[2], char delim);
/* hashtable after malloc */
static void match(char *args[2]);

void prompt(char *input)
{
    for (;*input && (*input == ' ');++input)
        ;

    char *token[2] = {0, 0};
    token[0] = input;
    *token[1] = '\0';
    scan(input, token, ' ');
    match(token);
    kprint("> ");
}

static void scan(char *input, char *output[2], char delim)
{

    u32 *pt = (u32 *)input;
    for (;DETECT_NULL(*pt) == 0;++pt)
        if (DETECT_CHAR(*pt, delim))
            break;

    s8 *lpt = (s8 *)pt;
    if (DETECT_CHAR(*pt, delim)) {
        for (int i = 0;i < 4;++i) {
            if (lpt[i] == delim) {
                lpt[i] = '\0';
                output[1] = (lpt+i+1);
            }
        }
    }

    for (;*output[1] && (*output[1] == ' ');++output[1])
        ;
}

#include <app/functions.h>

static void match(char *args[2])
{
    int i;
    for (i = 0;i < _TOTAL_FUNCTION;++i) {
        if (ms_strcmp(args[0], apps[i].alias) == 0) {
            if (ms_strcmp(args[1], "H") == 0)
                kprint(apps[i].help);
            else
                apps[i].fptr((void *)args[1]);
            return;
        }
    }
    if (i == _TOTAL_FUNCTION)
        KPRINTN(3, "Unknown Command: ", args[0], "\n");
}
