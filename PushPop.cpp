#include "PushPop.h"

void StackPush(Stk_t* stk, stk_el_t el)
{
    if (stk->sz == stk->capacity) {
        stk->data = (stk_el_t*) realloc(stk->data, stk->sz * 2 * sizeof(stk_el_t));
        stk->capacity *= 2;
    }

    if (StackError(stk, PUSH_PROC) == NO_ERR) (stk->data)[(stk->sz)++] = el;
}

void StackPop(Stk_t* stk, stk_el_t* var)
{
    if (stk->sz == 0) {
        fprintf(stderr, RED "Error: calling pop() for empty stack\n" COLOUR_RESET);
    } else {
        *var = (stk->data)[--(stk->sz)];
        (stk->data)[stk->sz] = 0;

        if (stk->capacity > CAPACITY_MIN && stk->sz == stk->capacity / 4) {
            stk->data = (stk_el_t*) realloc(stk->data, sizeof(stk_el_t) * stk->capacity / 2);
            stk->capacity /= 2;
        }
    }
}
