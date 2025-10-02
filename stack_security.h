#ifndef STACK_SECURITY_H
#define STACK_SECURITY_H


#include "data_types.h"

StackErrorCode CheckCanary(Stack* stk);
int StackVerify(Stack* stack);
int PreparationForStackDump(Stack* stack, const char* file, const char* function, int line);
int PrintErrorsInfo(int errors);

#endif