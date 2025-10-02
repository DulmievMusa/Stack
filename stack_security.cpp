#include <stdio.h>

#include "data_types.h"
#include "constants.h"
#include "stack_security.h"
#include "macros.h"
#include "asserts.h"

StackErrorCode CheckCanary(Stack* stk) {
    if (stk->data[0] != CANARY || stk->data[stk->capacity + 1] != CANARY) {
        return ERROR_CANARY_DIED;
    }
    return SUCCESS;
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

int PreparationForStackDump(Stack* stack, const char* file, const char* function, int line) {
    printf("\n" FG_BG_ANSI "<StackDump>" RESET_ANSI "\n");
    if (function != NULL) {
        printf("StackDump called from %s file\n", file);
    } else {
        printf("Link to file name is NULL. Info: ");
        AssertOfMusa(0, file, function, line);
    }

    if (line > 0) {
        printf("Line: %d\n", line);
    } else {
        printf("Line number is incorrect: %d. Info: ", line);
        AssertOfMusa(0, file, function, line);
    }

    if (function != NULL) {
        printf("Function: %s\n", function);
    } else {
        printf("Link to function name is NULL. Info: ");
        AssertOfMusa(0, file, function, line);
    }

    if (stack != NULL) { //
        printf("Stack [%p]\n", stack);
    } else {
        printf("Link to stack link is NULL. Info: ");
        AssertOfMusa(0, file, function, line);
    }

    if (stack != NULL) {
        printf("{\n");
        if (stack->size >= 0) {
            printf("\tsize = %d\n", stack->size);
        } else {
            printf("Stack size is incorrect: %d. Info: ", stack->size);
            AssertOfMusa(0, file, function, line);
        }

        if (stack->capacity > 0) {
            printf("\tcapacity = %d\n", stack->capacity);
        } else {
            printf("Stack capacity is incorrect: %d. Info: ", stack->capacity);
            AssertOfMusa(0, file, function, line);
        }

        if ((*stack).data != NULL) {
            if (CheckCanary(stack)) { // 
                printf("\n" FG_BG_ANSI "The edges of the stack are damaged" RESET_ANSI "\n");
            }
            printf("\tdata [%p]\n", (*stack).data);
        } else {
            printf("Link to stack.data is NULL. Info: ");
            AssertOfMusa(0, file, function, line);
        }
    
        if ((*stack).data != NULL) {
            printf("\t{\n");
            for (int index = 0; index < stack->capacity + 2; index++) {
                printf("\t\t*[%d] = %d\n", index, stack->data[index]);
            }
            printf("\t}\n");
        }
        printf("}\n");
    }
    return 0;
}


int PrintErrorsInfo(int errors) {
    if (IsCanaryDiedError(errors)) {
        printf("Canary died\n"); 
    }
    if (IsStackNullError(errors)) {
        printf("Stack pointer is null\n");
    }
    if (IsSizeNegativeError(errors)) {
        printf("Size is Negative\n");
    }
    if (IsCapacityNegativeError(errors)) {
        printf("Capacity is Negative\n");
    }
    if (IsStackDataNullError(errors)) {
        printf("Data pointer is null\n");
    }
    return 0;
}