#include "PushPop.h"

void StackPush(Stk_t* stk, stk_el_t el)
{
    STACK_ASSERT(stk)

    if (stk->sz == stk->capacity) {
        stk->data = (stk_el_t*) realloc(stk->data,
                                        (stk->sz * 2 + (stk->sz == 0) * CAPACITY_MIN) * sizeof(stk_el_t));
        stk->capacity *= 2;
        if (stk->capacity == 0) stk->capacity = CAPACITY_MIN;

        FillPoison(stk);

        STACK_ASSERT(stk)
    }

    (stk->data)[(stk->sz)++] = el;

    STACK_ASSERT(stk)
}

void StackPop(Stk_t* stk, stk_el_t* var)
{
    STACK_ASSERT(stk)

    if (stk->sz == 0) {
        fprintf(stderr, RED "Error: calling pop() for empty stack\n" COLOUR_RESET);
    } else {
        *var = (stk->data)[--(stk->sz)];
        (stk->data)[stk->sz] = POISON;

        if (stk->capacity > CAPACITY_MIN && stk->sz == stk->capacity / 4) {
            stk->data = (stk_el_t*) realloc(stk->data, sizeof(stk_el_t) * stk->capacity / 2);
            stk->capacity /= 2;
        }
    }
    STACK_ASSERT(stk)
}
