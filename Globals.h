#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <stdlib.h>

typedef int stk_el_t;

const size_t CAPACITY_MIN = 1;

struct Stk_t
{
    stk_el_t* data;
    size_t       sz;
    size_t    capacity;
    int       err_code;
};

enum Error_codes
{
    NO_ERR   = 0,
    DATA_ERR = 1,
    SIZE_ERR = 2
};

enum Process_codes
{
    CTOR_PROC = 0,
    PUSH_PROC = 1,
    POP_PROC  = 2
};

#endif
