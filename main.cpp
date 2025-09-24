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
int StackPop(stack_t* stk, int* err);



int main() {
    stack_t stk1 = {};
    StackInit(&stk1, 10);
    StackPush(&stk1, 5);
    StackPush(&stk1, 3);
    StackPush(&stk1, 2);
    StackPush(&stk1, 7);
    int value = StackPop(&stk1);
    printf("%d\n", value);



}



StackErr_t StackInit(stack_t* stk, int capacity) {
    stk->data = (int*) calloc(sizeof(int), capacity);
    stk->size = 0;
}

StackErr_t StackPush(stack_t* stk, int value) {
    stk->data[stk->size++] = value;   
}

int StackPop(stack_t* stk, int* err) {
    int value = stk->data[stk->size - 1];
    if (stk->size = 0) {
        *err = 11;
        return 0;
    }
    stk->size--;
    return value;
}