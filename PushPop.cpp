#include "PushPop.h"

void StackPush(Stk_t* stk, stk_el_t el)
{
    HASH_VERIFY(stk)
    STACK_VERIFY(stk)

    if (stk->sz == stk->capacity) {

        stk->data = (stk_el_t*) realloc((char*) stk->data ON_BIRDS(- CANARY_ADDED_SIZE),
                                        (stk->sz * 2 + (stk->sz == 0) * CAPACITY_MIN) * sizeof(stk_el_t)
                                        ON_BIRDS(+ 2 * CANARY_ADDED_SIZE));

        #ifdef CANARIES_MODE
            assert(stk->data);
            stk->data = (stk_el_t*) ((char*) stk->data + CANARY_ADDED_SIZE);
            assert(stk->data);
        #endif

        if (stk->capacity == 0) stk->capacity = CAPACITY_MIN;
        else stk->capacity *= 2;

        ON_BIRDS(*((canary_t*) (stk->data + stk->capacity)) = CANARY;)

        FillPoison(stk);

        STACK_VERIFY(stk)
    }

    (stk->data)[(stk->sz)++] = el;

    #ifdef HASH_MODE
        stk->data_hash = CalculateHash((const char*) stk->data, stk->capacity * sizeof(stk_el_t));
        stk->stk_hash  = CalculateHash((const char*) stk + STK_PTR_SHIFT, STK_SIZE);
    #endif

    STACK_VERIFY(stk)
}

void StackPop(Stk_t* stk, stk_el_t* var)
{
    HASH_VERIFY(stk)
    STACK_VERIFY(stk)

    if (stk->sz == 0) {
        fprintf(stderr, RED "Error: calling pop() for empty stack\n" COLOUR_RESET);
    } else {
        *var = (stk->data)[--(stk->sz)];
        (stk->data)[stk->sz] = POISON;

        if (stk->capacity > CAPACITY_MIN && stk->sz == stk->capacity / 4) {

            stk->data = (stk_el_t*) realloc((char*) stk->data ON_BIRDS(- CANARY_ADDED_SIZE),
                                            sizeof(stk_el_t) * stk->capacity / 2 ON_BIRDS(+ 2 * CANARY_ADDED_SIZE));
            #ifdef CANARIES_MODE
                assert(stk->data);
                stk->data = (stk_el_t*) ((char*) stk->data + CANARY_ADDED_SIZE);
                assert(stk->data);
            #endif

            stk->capacity /= 2;

            ON_BIRDS(*((canary_t*) (stk->data + stk->capacity)) = CANARY;)
        }

        #ifdef HASH_MODE
            stk->data_hash = CalculateHash((const char*) stk->data, stk->capacity * sizeof(stk_el_t));
            stk->stk_hash  = CalculateHash((const char*) stk + STK_PTR_SHIFT, STK_SIZE);
        #endif
    }
    STACK_VERIFY(stk)
}
