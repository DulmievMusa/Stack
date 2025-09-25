#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int* data;
    int size;
    int capacity; 
} stack_t;

typedef enum {
    FIRST,
    SECOND,
    THIRD
} StackErr_t;


int StackPop(stack_t* stk, int* err=NULL);
StackErr_t StackInit(stack_t* stk, int capacity);
StackErr_t StackPush(stack_t* stk, int value);
StackErr_t StackDestroy(stack_t* stk);
int StackPop(stack_t* stk, int* err);

int PrintErrorsofStack(stack_t* stack, const char* file, const char* function, int line);
#define StackDump(stack) PrintErrorsofStack(stack, __FILE__, __PRETTY_FUNCTION__, __LINE__)



int main() {
    stack_t stk1 = {};
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


int PrintErrorsofStack(stack_t* stack, const char* file, const char* function, int line) {
    printf("StackDump called from %s: %d\n", file, line);
    printf("Function: %s\n", function);
    printf("Stack [%p]\n", stack);
    printf("{\n");
    printf("\tsize = %d\n", stack->size);
    printf("\tcapacity = %d\n", stack->capacity);
    printf("\tdata [%p]\n", (*stack).data);
    printf("\t{\n");
    for (int index = 0; index < stack->capacity; index++) {
        printf("\t\t*[%d] = %d\n", index, stack->data[index]);
    }
    printf("\t}\n");
    printf("}\n");

}

StackErr_t StackInit(stack_t* stk, int capacity) {
    stk->data = (int*) calloc(sizeof(int), capacity);
    stk->capacity = capacity;
    stk->size = 0;
}

StackErr_t StackPush(stack_t* stk, int value) {
    stk->data[stk->size] = value;   
    stk->size = stk->size + 1;
    return THIRD;
 
}


StackErr_t StackDestroy(stack_t* stk) {
    free(stk->data);
    stk->data = NULL;
}


int StackPop(stack_t* stk, int *err) {
    if (stk->size == 0) {
        *err = FIRST;
        return 0;
    }
    int value = stk->data[stk->size - 1];
    stk->data[stk->size] = 0;
    stk->size = stk->size - 1;

    return value;
}