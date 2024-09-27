#include "DumpErr.h"

int StackError(Stk_t* stk, int process)
{
    assert(stk);
    if (stk->err_code == NO_ERR) {
        if (stk->data == NULL) stk->err_code = DATA_ERR;
        else if (stk->sz > stk->capacity) stk->err_code = SIZE_ERR;
    }
    if (stk->err_code != NO_ERR) PrintError(stk->err_code, process);

    return stk->err_code;
}

void StackDump(Stk_t* stk)
{
    assert(stk);
    printf("Capacity: %lld,\nNumber of elements: %lld,\n", stk->capacity, stk->sz);

    assert(stk->data);
    printf("Data: ");
    for (size_t i = 0; i < stk->sz; ++i) {
        printf("%d ", (stk->data)[i]);
    }
    printf("\n\n");
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
