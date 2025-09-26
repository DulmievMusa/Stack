#include <stdio.h>
#include <stdlib.h>


#define FG_BG_ANSI "\033[41;97m"
#define RESET_ANSI "\033[0m"
#define TEST_FALED_ANSI "\033[44;97m"
#define MyAssert(need_to_call_assert) AssertOfMusa(need_to_call_assert, __FILE__, __PRETTY_FUNCTION__, __LINE__)
#define StackDump(stack) PrintErrorsofStack(stack, __FILE__, __PRETTY_FUNCTION__, __LINE__)

typedef struct {
    int* data;
    int size;
    int capacity; 
} Stack;

typedef enum {
    SUCCESS = 0,
    ERROR_NULL_POINTER = 1, 
    ERROR_ZERO_SIZE = 2
} StackErrorCode;


int StackPop(Stack* stk, int* err=NULL);
StackErrorCode StackInit(Stack* stk, int capacity);
StackErrorCode StackPush(Stack* stk, int value);
StackErrorCode StackDestroy(Stack* stk);
int StackPop(Stack* stk, int* err);

int PrintErrorsofStack(Stack* stack, const char* file, const char* function, int line);




int main() {
    Stack stk1 = {};
    int err = 0;
    StackInit(&stk1, 11);
    StackPush(&stk1, 5);
    /*
    StackPush(&stk1, 3);
    StackPush(&stk1, 2);
    StackPush(&stk1, 7);
    for (int i = 0, value; i < 3; i++) {
        value = StackPop(&stk1, &err);
        
    }
    StackDump(&stk1);
    StackDestroy(NULL);
    printf("\n\n\n\n\n\n\n\n\n");*/
    // PrintErrorsofStack(&stk1, NULL, NULL, NULL);


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

    if (stack != NULL) {
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
            printf("\t{hello\n");
            for (int index = 0; index < stack->capacity; index++) {
                printf("\t\t*[%d] = %d\n", index, stack->data[index]);
            }
            printf("\t}\n");
        }
        printf("}\n");
    }

}

StackErrorCode StackInit(Stack* stk, int capacity) {
    if (stk == NULL) {
        return ERROR_NULL_POINTER;
    }
    // stk->data = (int*) calloc(sizeof(int), capacity);
    stk->data = NULL;
    stk->capacity = capacity;
    stk->size = 0;
    return SUCCESS;
}

StackErrorCode StackPush(Stack* stk, int value) {
    if (stk == NULL || stk->data == NULL) {
        return ERROR_NULL_POINTER;
    }
    if (stk->size < 0) {
        return ERROR_ZERO_SIZE;
    }
    stk->data[stk->size] = value;   
    stk->size = stk->size + 1;
    return SUCCESS;
 
}


StackErrorCode StackDestroy(Stack* stk) {
    if (stk == NULL) {
        StackDump(stk);
        return ERROR_NULL_POINTER;
    }

    if (stk->data == NULL) {
        StackDump(stk);
        return ERROR_NULL_POINTER;
    }

    free(stk->data);
    stk->data = NULL;
}


int StackPop(Stack* stk, int *err) {

    if (stk == NULL || stk->data == NULL) {
        return ERROR_NULL_POINTER;
    }
    if (stk->size < 0) {
        return ERROR_ZERO_SIZE;
    }

    if (stk->size == 0) {
        *err = ERROR_ZERO_SIZE;
        return ERROR_ZERO_SIZE;
    }
    int value = stk->data[stk->size - 1];
    stk->data[stk->size] = 0;
    stk->size = stk->size - 1;

    return value;
}