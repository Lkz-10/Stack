#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "StackHeads.h"

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
