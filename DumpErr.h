#ifndef __DUMPERR_H__
#define __DUMPERR_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Globals.h"
#include "OutputColours.h"

void StackDump(Stk_t* stk);
int  StackError(Stk_t* stk, int process);
void PrintError(int error_code, int process);

#endif
