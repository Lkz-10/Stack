#include <stdio.h>
#include <stdlib.h>

#include "OutputColours.h"

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

void StackCtor(Stk_t* stk);
void StackPush(Stk_t* stk, stk_el_t el);
void StackPop(Stk_t* stk, stk_el_t* var);
void StackDump(Stk_t* stk);
void StackDtor(Stk_t* stk);
int  StackError(Stk_t* stk, int process);
void PrintError(int error_code, int process);

int main()
{
    Stk_t stk = {};

    StackCtor(&stk);

    if(StackError(&stk, CTOR_PROC) == NO_ERR) StackDump(&stk);

    if(StackError(&stk, CTOR_PROC) == NO_ERR) StackPush(&stk, 1925);
    if(StackError(&stk, CTOR_PROC) == NO_ERR) StackPush(&stk, 2048);

    if(StackError(&stk, PUSH_PROC) == NO_ERR) StackDump(&stk);

    stk_el_t popped_el = 0;
    if(StackError(&stk, PUSH_PROC) == NO_ERR) StackPop(&stk, &popped_el);

    if(StackError(&stk, POP_PROC) == NO_ERR) {
        StackDump(&stk);
        printf("Popped element: %d\n\n", popped_el);
    }

    StackDtor(&stk);

    printf("Zenit champion\n");

    return 0;
}

void StackCtor(Stk_t* stk)
{
    stk->data     = (stk_el_t*) calloc(CAPACITY_MIN, sizeof(stk_el_t));
    stk->sz       = 0;
    stk->capacity = CAPACITY_MIN;
    stk->err_code = NO_ERR;
}

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

int StackError(Stk_t* stk, int process)
{
    if (stk->err_code == NO_ERR) {
        if (stk->data == NULL) stk->err_code = DATA_ERR;
        else if (stk->sz > stk->capacity) stk->err_code = SIZE_ERR;
    }
    if (stk->err_code != NO_ERR) PrintError(stk->err_code, process);

    return stk->err_code;
}

void StackDump(Stk_t* stk)
{
    printf("Capacity: %lld,\nNumber of elements: %lld,\n", stk->capacity, stk->sz);

    printf("Data: ");
    for (size_t i = 0; i < stk->sz; ++i) {
        printf("%d ", (stk->data)[i]);
    }
    printf("\n\n");
}

void StackDtor(Stk_t* stk)
{
    free(stk->data);

    stk->data     = NULL;
    stk->capacity = CAPACITY_MIN;
    stk->sz       = 0;
}

void PrintError(int error_code, int process)
{
    switch (error_code)
    {
        case DATA_ERR:
            fprintf(stderr, "Error: address of data is NULL\n");
            break;

        case SIZE_ERR:
            fprintf(stderr, "Error: size > capacity\n");
            break;

        default:
            fprintf(stderr, RED "Unknown error\n" COLOUR_RESET);
    }

    printf("Process: ");

    switch (process)
    {
        case CTOR_PROC:
            fprintf(stderr, "Ctor\n\n");
            break;
        case PUSH_PROC:
            fprintf(stderr, "Push\n\n");
            break;

        case POP_PROC:
            fprintf(stderr, "Pop\n\n");
            break;

        default:
            fprintf(stderr, RED "Unknown process\n\n" COLOUR_RESET);
    }
}
