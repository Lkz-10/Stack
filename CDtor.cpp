#include "CDtor.h"

void StackCtor(Stk_t* stk)
{
    stk->data     = (stk_el_t*) calloc(CAPACITY_MIN, sizeof(stk_el_t));
    stk->sz       = 0;
    stk->capacity = CAPACITY_MIN;
    stk->err_code = NO_ERR;
}

void StackDtor(Stk_t* stk)
{
    free(stk->data);

    stk->data     = NULL;
    stk->capacity = CAPACITY_MIN;
    stk->sz       = 0;
}
