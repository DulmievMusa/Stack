#include "data_types.h"

StackErrorCode CheckCanary(Stack* stk);
int StackVerify(Stack* stack);
int StackPop(Stack* stk, int* errors);
int StackPush(Stack* stk, int value);