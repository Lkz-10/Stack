#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "StackHeads.h"

int main()
{
    Stk_t stk = {INIT(stk)};

    StackCtor(&stk);

    STACK_ASSERT(&stk)

    StackPush(&stk, 1925);

    STACK_ASSERT(&stk)

    StackPush(&stk, 2048);

    STACK_ASSERT(&stk)

    stk_el_t popped_el = 0;
    StackPop(&stk, &popped_el);

    STACK_ASSERT(&stk)

    //printf("Popped element: %d\n\n", popped_el);

    StackDump(&stk, __FILE__, __LINE__, __func__);

    StackDtor(&stk);

    printf("Zenit champion\n");

    return 0;
}
