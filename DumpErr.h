#ifndef __DUMPERR_H__
#define __DUMPERR_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Globals.h"
#include "OutputColours.h"

void StackDump(Stk_t* stk, const char* file_name, const int line, const char* func_name);
int  StackError(Stk_t* stk);
void PrintError(int error_code);

#endif
