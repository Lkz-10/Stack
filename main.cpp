#include <stdio.h>
#include <stdlib.h>

#include "OutputColours.h"

typedef int stk_el_t;

const size_t CAPACITY_0 = 10;

struct Stk_t
{
    stk_el_t* data;
    size_t    sz;
    size_t    capacity;
    int       err_code;
};

enum Error_codes
{
    NO_ERR   = 0,
    CTOR_ERR = 1,
    PUSH_ERR = 2,
    POP_REALLOC_ERR = 3,
    POP_SZ_ERR = 4
};

void StackCtor(Stk_t* stk);
void StackPush(Stk_t* stk, stk_el_t el);
void StackPop(Stk_t* stk, stk_el_t* var);
void StackDump(Stk_t* stk);

int main()
{
    Stk_t stk = {};

    StackCtor(&stk);

    StackPush(&stk, 1925);
    StackPush(&stk, 2048);

    StackDump(&stk);

    stk_el_t popped_el = 0;
    StackPop(&stk, &popped_el);

    StackDump(&stk);
    printf("Popped element: %d\n", popped_el);

    free(stk.data);

    printf("Zenit champion\n");

    return 0;
}

void StackCtor(Stk_t* stk)
{
    stk->data     = (stk_el_t*) calloc(CAPACITY_0, sizeof(stk_el_t));
    stk->sz       = 0;
    stk->capacity = CAPACITY_0;
    stk->err_code = NO_ERR;

    if (stk->data == NULL) {
        fprintf(stderr, RED "Error while constructing stack\n" COLOUR_RESET);
        stk->err_code = CTOR_ERR;
    }
}

void StackPush(Stk_t* stk, stk_el_t el)
{
    if (stk->sz == stk->capacity) {
        stk->data = (stk_el_t*) realloc(stk->data, stk->sz * 2 * sizeof(stk_el_t));
        stk->capacity *= 2;

        if (stk->data == NULL) {
            stk->err_code = PUSH_ERR;
            fprintf(stderr, RED "Error while realloc up\n" COLOUR_RESET);
        }
    }
    if (stk->err_code == NO_ERR) {
        (stk->data)[(stk->sz)++] = el;
    }
}

void StackPop(Stk_t* stk, stk_el_t* var)
{
    if (stk->sz > 0) {
        *var = (stk->data)[--(stk->sz)];
        (stk->data)[stk->sz] = 0;

        if (stk->sz == stk->capacity / 4) {
            stk->data = (stk_el_t*) realloc(stk->data, sizeof(stk_el_t) * stk->capacity / 2);
            stk->capacity /= 2;

            if (stk->data == NULL) {
                fprintf(stderr, RED "Error while realloc down\n" COLOUR_RESET);
                stk->err_code = POP_REALLOC_ERR;
            }
        }
    } else {
        fprintf(stderr, RED "Error: sz <= 0\n" COLOUR_RESET);
        stk->err_code = POP_SZ_ERR;
    }
}

void StackDump(Stk_t* stk)
{
    if (stk->err_code == NO_ERR) {
        printf("Capacity: %lld,\nNumber of elements: %lld,\n", stk->capacity, stk->sz);
        if (stk->sz <= stk->capacity) {
            printf("Data: ");
            for (size_t i = 0; i < stk->sz; ++i) {
                printf("%d ", (stk->data)[i]);
            }
            printf("\n");
        }
    }
}
