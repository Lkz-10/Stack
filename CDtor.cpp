#include "CDtor.h"

void StackCtor(Stk_t* stk)
{
    assert(stk);
    stk->data     = (stk_el_t*) calloc(CAPACITY_MIN, sizeof(stk_el_t));
    stk->sz       = 0;
    stk->capacity = CAPACITY_MIN;
    stk->err_code = NO_ERR;

    FillPoison(stk);
}

void StackDtor(Stk_t* stk)
{
    free(stk->data);

    stk->data     = NULL;
    stk->capacity = CAPACITY_MIN;
    stk->sz       = 0;
}

int FillPoison (Stk_t* stk)
{
    STACK_ASSERT(stk)

    for (size_t i = stk->sz; i < stk->capacity; ++i) {
        (stk->data)[i] = POISON;
    }

    return 0;
}
