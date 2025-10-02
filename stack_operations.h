#ifndef STACK_OPERATIONS_H
#define STACK_OPERATIONS_H

#include "data_types.h"

int StackPop(Stack* stk, int* errors);
int StackPush(Stack* stk, int value);
int StackInit(Stack* stk, int capacity);
int StackDestroy(Stack* stk);

#endif