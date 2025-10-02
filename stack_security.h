#ifndef STACK_SECURITY_H
#define STACK_SECURITY_H


#include "data_types.h"

StackErrorCode CheckCanary(Stack* stk);
int StackVerify(Stack* stack);
int PrintErrorsofStack(Stack* stack, const char* file, const char* function, int line);

#endif