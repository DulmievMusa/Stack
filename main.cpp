#include <stdio.h>
#include <stdlib.h>


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
#define StackDump(stack) PrintErrorsofStack(stack, __FILE__, __PRETTY_FUNCTION__, __LINE__)



int main() {
    Stack stk1 = {};
    int err = 0;
    StackInit(&stk1, 11);
    StackPush(&stk1, 5);
    StackPush(&stk1, 3);
    StackPush(&stk1, 2);
    StackPush(&stk1, 7);
    for (int i = 0, value; i < 3; i++) {
        value = StackPop(&stk1, &err);
        
    }
    StackDump(&stk1);
    StackDestroy(&stk1);


}


int PrintErrorsofStack(Stack* stack, const char* file, const char* function, int line) {
    if (function != NULL) {
        printf("StackDump called from %s file\n", file);
    } else {
        printf("Sorry, but the link to file name is NULL\n");
    }

    if (line > 0) {
        printf("Line: %d\n", line);
    } else {
        printf("Sorry, but the line number is incorrect.\n");
    }

    if (function != NULL) {
        printf("Function: %s\n", function);
    } else {
        printf("Sorry, but the link to function name is NULL\n");
    }

    if (stack != NULL) {
        printf("Stack [%p]\n", stack);
    } else {
        printf("Sorry, but the link to stack link is NULL\n");
    }

    printf("{\n");

    if (stack->size > 0) {
        printf("\tsize = %d\n", stack->size);
    } else {
        printf("Sorry, but the stack size is incorrect.\n");
    }

    if (stack->capacity > 0) {
        printf("\tcapacity = %d\n", stack->capacity);
    } else {
        printf("Sorry, but the stack capacity is incorrect.\n");
    }

    if ((*stack).data != NULL) {
        printf("\tdata [%p]\n", (*stack).data);
    } else {
        printf("Sorry, but the link to stack.data is NULL\n");
    }
    
    printf("\t{\n");
    for (int index = 0; index < stack->capacity; index++) {
        if ((*stack).data != NULL) {
            printf("\t\t*[%d] = %d\n", index, stack->data[index]);
        } else {
            printf("Sorry, but the link to stack.data is NULL\n");
        }
    }
    printf("\t}\n");
    printf("}\n");

}

StackErrorCode StackInit(Stack* stk, int capacity) {
    stk->data = (int*) calloc(sizeof(int), capacity);
    stk->capacity = capacity;
    stk->size = 0;
}

StackErrorCode StackPush(Stack* stk, int value) {
    stk->data[stk->size] = value;   
    stk->size = stk->size + 1;
    return SUCCESS;
 
}


StackErrorCode StackDestroy(Stack* stk) {
    free(stk->data);
    stk->data = NULL;
}


int StackPop(Stack* stk, int *err) {
    if (stk->size == 0) {
        *err = ERROR_ZERO_SIZE;
        return ERROR_ZERO_SIZE;
    }
    int value = stk->data[stk->size - 1];
    stk->data[stk->size] = 0;
    stk->size = stk->size - 1;

    return value;
}