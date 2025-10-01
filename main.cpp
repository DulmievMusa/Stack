#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define FG_BG_ANSI "\033[41;97m"
#define RESET_ANSI "\033[0m"
#define TEST_FALED_ANSI "\033[44;97m"
#define MyAssert(need_to_call_assert) AssertOfMusa(need_to_call_assert, __FILE__, __PRETTY_FUNCTION__, __LINE__)
#define StackDump(stack) PrintErrorsofStack(stack, __FILE__, __PRETTY_FUNCTION__, __LINE__)


#define SetStackIsNullError(errors) errors |= (1 << 0)
#define SetCanaryDiedError(errors) errors |= (1 << 1)
#define SetSizeisNegativeError(errors) errors |= (1 << 2)
#define SetCapacityIsNegativeError(errors) errors |= (1 << 3)
#define SetStackDataisNullError(errors) errors |= (1 << 4)
#define SetSizeIsNullError(errors) errors |= (1 << 5)


#define IsStackNullError(errors) errors & (1 << 0)
#define IsCanaryDiedError(errors) errors & (1 << 1)
#define IsSizeNegativeError(errors) errors & (1 << 2)
#define IsCapacityNegativeError(errors) errors & (1 << 3)
#define IsStackDataNullError(errors) errors & (1 << 4)
#define IsSizeNullError(errors) errors & (1 << 5)




typedef struct {
    int* data;
    int size;
    int capacity; 
} Stack;

typedef enum {
    SUCCESS = 0,
    ERROR_NULL_POINTER = 1, 
    ERROR_ZERO_SIZE = 2,
    ERROR_CANARY_DIED = 666
} StackErrorCode;





const int CANARY = 56191;
// int err = 0;


// int StackPop(Stack* stk, int* err=NULL);
int StackInit(Stack* stk, int capacity);
int StackPush(Stack* stk, int value);
StackErrorCode StackDestroy(Stack* stk);
int StackVerify(Stack* stack);
int StackPop(Stack* , int* errors);
StackErrorCode CheckCanary(Stack* stk);
int DoCommand(Stack* stk, char* command, int value, int how_much_read, int* errors);

int PrintErrorsofStack(Stack* stack, const char* file, const char* function, int line);




int main() {
    Stack stk = {};
    StackInit(&stk, 6);
    char input[100];
    char command[30];
    int how_much_read = 0;
    int value = 0;
    /*stk.data[0] = 666;
    stk.data = NULL;
    stk.size = -1;
    stk.capacity = -1;*/
    int errors = 0;
    if (IsCanaryDiedError(errors)) {
        printf("Canary died\n"); // Выведет "Флаг 1 установлен"
    }
    if (IsStackNullError(errors)) {
        printf("Stack null\n");
    }
    if (IsSizeNegativeError(errors)) {
        printf("Size is not ok\n");
    }
    if (IsCapacityNegativeError(errors)) {
        printf("Capacity is not okey\n");
    }
    if (IsStackDataNullError(errors)) {
        printf("data null\n");
    }
    //printf("number %d\n", errors);
    StackDump(&stk);
    int need_to_finish = 0;
    while (need_to_finish == 0) {
        printf("WTF\n");
        fgets(input, sizeof(input), stdin);
        how_much_read = sscanf(input, "%29s %d", command, &value);
        need_to_finish = DoCommand(&stk, command, value, how_much_read, &errors);
        StackDump(&stk);
    }
   


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
    if (stack->size == 0) {
        SetSizeIsNullError(errors);
    }

    return errors;
}

int DoCommand(Stack* stk, char* command, int value, int how_much_read, int* errors) {
    // *errors = 0;
    if (strcmp(command, "PUSH") == 0 && how_much_read == 2) {
        StackPush(stk, value);
    } else if (strcmp(command, "OUT") == 0 && how_much_read == 1 && stk->size > 0) {
        printf("%d\n", StackPop(stk, errors));
    } else if (strcmp(command, "SUB") == 0 && how_much_read == 1 && stk->size > 1) {
        int a = StackPop(stk, errors);
        int b = StackPop(stk, errors);
        StackPush(stk, b - a);
    } else if (strcmp(command, "HLT") == 0 && how_much_read == 1) {
        return 1;
    } else if (strcmp(command, "MUL") == 0 && how_much_read == 1 && stk->size > 1) {
        int a = StackPop(stk, errors);
        int b = StackPop(stk, errors);
        StackPush(stk, a * b);
    } else if (strcmp(command, "SQRT") == 0 && how_much_read == 1 && stk->size > 0) {
        StackPush(stk, (int) sqrt(StackPop(stk, errors)));
    } else if (strcmp(command, "DIV") == 0 && how_much_read == 1 && stk->size > 1) {
        int a = StackPop(stk, errors);
        int b = StackPop(stk, errors);
        StackPush(stk, (int) ((double) b / a));
    } else {
        printf("Wrong command. Try Again\n");
    }
    return 0;
}


void AssertOfMusa(int need_to_call_assert, const char *file, const char *function, int line) {
    if (!need_to_call_assert) {
        //printf(FG_BG_ANSI "Assertion failed: ");
        printf(FG_BG_ANSI "File: %s, ", file);
        printf(FG_BG_ANSI "Function: %s, ", function);
        printf(FG_BG_ANSI "Line: %d " RESET_ANSI "\n", line);
        printf("\n");
    }
}


int PrintErrorsofStack(Stack* stack, const char* file, const char* function, int line) {
    printf("\n" FG_BG_ANSI "<StackDump>" RESET_ANSI "\n");
    if (CheckCanary(stack)) { // 
        printf("\n" FG_BG_ANSI "The edges of the stack are damaged" RESET_ANSI "\n");
    }
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
            printf("\tdata [%p]\n", (*stack).data);
        } else {
            printf("\tLink to stack.data is NULL. Info: ");
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

}

int StackInit(Stack* stk, int capacity) {
    int errors = 0;
    if (stk == NULL) {
        SetStackIsNullError(errors);
        return errors;
    }
    stk->data = (int*) calloc(sizeof(int), capacity + 2);
    stk->capacity = capacity;
    stk->size = 0;
    stk->data[0] = CANARY;
    stk->data[capacity + 1] = CANARY;
    return errors;
}

int StackPush(Stack* stk, int value) { // stack verify, propagate_error? fail_if_error? assert_never_fsils? ignore_error?
    int errors = StackVerify(stk);

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


StackErrorCode StackDestroy(Stack* stk) {
    int errors = StackVerify(stk);

    free(stk->data);
    stk->data = NULL;
}


int StackPop(Stack* stk, int* errors) {
    *errors = 0;
    *errors = StackVerify(stk);
    if (stk->size == 0) {
        SetSizeIsNullError(*errors);
    }
    int value = stk->data[stk->size];
    stk->data[stk->size] = 0;
    stk->size = stk->size - 1;
    return value;
}

StackErrorCode CheckCanary(Stack* stk) {
    if (stk == NULL) {
        return ERROR_NULL_POINTER;
    }
    if (stk->data[0] != CANARY || stk->data[stk->capacity + 1] != CANARY) {
        return ERROR_CANARY_DIED;
    }
    return SUCCESS;
}