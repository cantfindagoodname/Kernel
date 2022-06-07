#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#define set_func(IDX,FUN,ALIAS,HELP)                                    \
        apps[IDX].fptr = FUN;                                           \
        ms_strncpy(ms_strlen(ALIAS), apps[IDX].alias, ALIAS);           \
        ms_strncpy(ms_strlen(HELP), apps[IDX].help, HELP)

enum {
    QUIT,
    FIB,
    TIME,
    CLR,
    _TOTAL_FUNCTION,
};

struct shellfunctions_st {
    void (*fptr)(void *);
    char alias[8];
    char help[32];
};
typedef struct shellfunctions_st sf_t;

sf_t apps[_TOTAL_FUNCTION];

void init_functions();

#endif
