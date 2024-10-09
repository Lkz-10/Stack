#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "StackHeads.h"

int main()
{
    Stk_t stk = {INIT(stk)};

    StackCtor(&stk);

    StackPush(&stk, 1925);
    StackPush(&stk, 2048);
    StackPush(&stk, 2056);
    StackPush(&stk, 2451);

    StackPush(&stk, 20.5);
    StackPush(&stk, 0.009);

    stk_el_t popped_el = 0;

    StackPop(&stk, &popped_el);
    StackPop(&stk, &popped_el);
    StackPop(&stk, &popped_el);
    StackPop(&stk, &popped_el);

    StackPush(&stk, 2512);

    StackPop(&stk, &popped_el);
    StackPop(&stk, &popped_el);
    StackPop(&stk, &popped_el);

    //printf("Popped element: %d\n\n", popped_el);

    StackDump(&stk, __FILE__, __LINE__, __func__);

    StackDtor(&stk);

    printf("Zenit champion\n");

    return 0;
}
