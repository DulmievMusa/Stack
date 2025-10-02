#include <stdio.h>
#include <stdlib.h>

#include "data_types.h"
#include "macros.h"
#include "constants.h"
#include "stack_operations.h"


StackErrorCode CheckCanary(Stack* stk) {
    if (stk->data[0] != CANARY || stk->data[stk->capacity + 1] != CANARY) {
        return ERROR_CANARY_DIED;
    }
    return SUCCESS;
}


int StackPush(Stack* stk, int value) { // stack verify, propagate_error? fail_if_error? assert_never_fsils? ignore_error?
    int errors = StackVerify(stk);
    if (errors) {
        return errors; 
    }

    if (stk->size == stk->capacity) {
        stk->data[stk->capacity + 1] = 0;
        stk->data = (int*) realloc(stk->data, sizeof(int) * (stk->capacity * 2)  + 2);
        stk->capacity = stk->capacity * 2;
        stk->data[stk->capacity + 1] = CANARY;
    }
    stk->data[stk->size + 1] = value;   
    stk->size = stk->size + 1;

    errors = StackVerify(stk);
    return errors;
 
}

int StackVerify(Stack* stack) {
    int errors = 0;
    if (stack == NULL) {
        SetStackIsNullError(errors);
        return errors;
    }
    if (stack->data == NULL) {
        SetStackDataisNullError(errors);
    } else {
        if (CheckCanary(stack)) {
            SetCanaryDiedError(errors); 
        }
    }
    if (stack->size < 0) {
        SetSizeisNegativeError(errors);
    }
    if (stack->capacity < 0) {
        SetCapacityIsNegativeError(errors);
    }

    return errors;
}


int StackPop(Stack* stk, int* errors) {
    *errors = StackVerify(stk);
    if (stk->size == 0) {
        SetSizeIsNullError(*errors);
    }
    if (*errors) {
        return *errors;
    }
    int value = stk->data[stk->size];
    stk->data[stk->size] = 0;
    stk->size = stk->size - 1;
    *errors = StackVerify(stk);
    return value;
}