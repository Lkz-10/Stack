#include "DumpErr.h"

int StackError(Stk_t* stk)
{
    assert(stk);
    if (stk->err_code == NO_ERR) {
        if (stk->data == NULL) stk->err_code = DATA_ERR;
        else if (stk->sz > stk->capacity) stk->err_code = SIZE_ERR;
        else if (stk->canary1 != CANARY || stk->canary2 != CANARY) stk->err_code = CANARY_ERR;
    }
    //if (stk->err_code != NO_ERR) PrintError(stk->err_code);

    return stk->err_code;
}

void StackDump(Stk_t* stk, const char* file_name, const int line, const char* func_name)
{
    printf("\nStk_t [0x%p]", stk);
    assert(stk);

    printf(" born at %s:%d, named \"%s\"\n", stk->file, stk->line, stk->name);
    printf("called from %s:%d (%s)\n", file_name, line, func_name);

    printf("{\n  canary1 = %x\n  ", stk->canary1);
    printf("capacity = %lld\n  size     = %lld\n  data [0x%p]", stk->capacity, stk->sz, stk->data);
    assert(stk->data);

    printf(":\n  {\n");

    for (size_t i = 0; i < stk->capacity; ++i) {
        if ((stk->data)[i] != POISON) {
            printf("   *[%lld] = %f\n", i, (stk->data)[i]);
        } else {
            printf("    [%lld] = %f (POISON)\n", i, (stk->data)[i]);
        }
    }
    printf("  }\n  ");
    printf("canary2 = %x\n}\n", stk->canary2);

    if (stk->err_code != NO_ERR) PrintError(stk->err_code);

    StackDtor(stk);
}

void PrintError(int error_code)
{
    switch (error_code)
    {
        case DATA_ERR:
            fprintf(stderr, RED "Error: address of data is NULL\n" COLOUR_RESET);
            break;

        case SIZE_ERR:
            fprintf(stderr, RED "Error: size > capacity\n" COLOUR_RESET);
            break;

        case CANARY_ERR:
            fprintf(stderr, RED "Canary error\n" COLOUR_RESET);
            break;

        default:
            fprintf(stderr, RED "Unknown error\n" COLOUR_RESET);
    }
}
