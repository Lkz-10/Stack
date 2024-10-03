#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#define DEBUG

#include <stdlib.h>

typedef double stk_el_t;

const size_t   CAPACITY_MIN = 10;
const stk_el_t POISON       = -79173490302.102;
const int      CANARY       = 0xEDADEDA;

struct Stk_t
{
    #ifdef DEBUG
        int         canary1;
        const char* name;
        const char* file;
        const int   line;
    #endif

    int       err_code;
    stk_el_t* data;
    size_t    sz;
    size_t    capacity;

    #ifdef DEBUG
        int canary2;
    #endif
};

enum Error_codes
{
    NO_ERR     = 0,
    DATA_ERR   = 1,
    SIZE_ERR   = 2,
    CANARY_ERR = 4
};

#ifdef DEBUG
    #define INIT(var) CANARY, #var, __FILE__, __LINE__
    #define ON_DEBUG(...) __VA_ARGS__
    #define STACK_ASSERT(var)                                  \
        if (StackError(var) != NO_ERR) {                       \
            StackDump(var, __FILE__, __LINE__, __func__);      \
            assert(0);                                         \
        }
#else
    #define INIT(var)
    #define ON_DEBUG(...)
    #define STACK_ASSERT(var)
#endif

#endif
