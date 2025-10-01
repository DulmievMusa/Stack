#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


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
    ERROR_ZERO_SIZE = 2,
    ERROR_CANARY_DIED = 666
} StackErrorCode;


const int CANARY = 56191;
int err = 0;


// int StackPop(Stack* stk, int* err=NULL);
StackErrorCode StackInit(Stack* stk, int capacity);
StackErrorCode StackPush(Stack* stk, int value);
StackErrorCode StackDestroy(Stack* stk);
int StackPop(Stack* stk, int* err);
StackErrorCode CheckCanary(Stack* stk);
int DoCommand(Stack* stk, char* command, int value, int how_much_read);

int PrintErrorsofStack(Stack* stack, const char* file, const char* function, int line);




int main() {
    Stack stk1 = {};
    StackInit(&stk1, 6);
    /*
     int size = stk1.size;
    for (int i = 0, value; i < size; i++) {
        value = StackPop(&stk1, &err);
        printf("%d\n", value);
    }
    StackPush(&stk1, 666);
    StackPush(&stk1, 333);
    StackPush(&stk1, 111);
    printf("--------------------------------------------\n");
    for (int i = 0, value; i < 3; i++) {
        value = StackPop(&stk1, &err);
        printf("%d\n", value);
    } 
        */
    // PrintErrorsofStack(&stk1, NULL, NULL, NULL);
    char input[100];
    char command[30];
    int how_much_read = 0;
    int value = 0;
    StackDump(&stk1);
    int need_to_finish = 0;
    while (need_to_finish == 0) {
        fgets(input, sizeof(input), stdin);
        how_much_read = sscanf(input, "%29s %d", command, &value);
        need_to_finish = DoCommand(&stk1, command, value, how_much_read);
        StackDump(&stk1);
    }


}

int DoCommand(Stack* stk, char* command, int value, int how_much_read) {
    if (strcmp(command, "PUSH") == 0 && how_much_read == 2) {
        StackPush(stk, value);
    } else if (strcmp(command, "OUT") == 0 && how_much_read == 1 && stk->size > 0) {
        printf("%d\n", StackPop(stk, &err));
    } else if (strcmp(command, "SUB") == 0 && how_much_read == 1 && stk->size > 1) {
        int a = StackPop(stk, &err);
        int b = StackPop(stk, &err);
        StackPush(stk, b - a);
    } else if (strcmp(command, "HLT") == 0 && how_much_read == 1) {
        return 1;
    } else if (strcmp(command, "MUL") == 0 && how_much_read == 1 && stk->size > 1) {
        int a = StackPop(stk, &err);
        int b = StackPop(stk, &err);
        StackPush(stk, a * b);
    } else if (strcmp(command, "SQRT") == 0 && how_much_read == 1 && stk->size > 0) {
        StackPush(stk, (int) sqrt(StackPop(stk, &err)));
    } else if (strcmp(command, "DIV") == 0 && how_much_read == 1 && stk->size > 1) {
        int a = StackPop(stk, &err);
        int b = StackPop(stk, &err);
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
    if (CheckCanary(stack)) {
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
            for (int index = 0; index < stack->capacity + 2; index++) {
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
    stk->data = (int*) calloc(sizeof(int), capacity + 2);
    stk->capacity = capacity;
    stk->size = 0;
    stk->data[0] = CANARY;
    stk->data[capacity + 1] = CANARY;
    return SUCCESS;
}

StackErrorCode StackPush(Stack* stk, int value) { // stack verify, propagate_error? fail_if_error? assert_never_fsils? ignore_error?
    if (CheckCanary(stk) == ERROR_CANARY_DIED) {
        return ERROR_CANARY_DIED;
    }


    if (stk == NULL || stk->data == NULL) {
        return ERROR_NULL_POINTER;
    }
    if (stk->size < 0) {
        return ERROR_ZERO_SIZE;
    }
    if (stk->size == stk->capacity) {
        stk->data[stk->capacity + 1] = 0;
        stk->data = (int*) realloc(stk->data, sizeof(int) * (stk->capacity * 2)  + 2);
        stk->capacity = stk->capacity * 2;
        stk->data[stk->capacity + 1] = CANARY;
    }
    stk->data[stk->size + 1] = value;   
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
    *err = SUCCESS;
    if (CheckCanary(stk) == ERROR_CANARY_DIED) {
        *err = ERROR_CANARY_DIED;
        return ERROR_CANARY_DIED;
    }

    if (stk == NULL || stk->data == NULL) {
        *err = ERROR_CANARY_DIED;
        return ERROR_NULL_POINTER;
    }
    if (stk->size == 0) {
        *err = ERROR_ZERO_SIZE;
        return ERROR_ZERO_SIZE;
    }
    int value = stk->data[stk->size];
    stk->data[stk->size] = 0;
    stk->size = stk->size - 1;
    *err = SUCCESS;

    return value;
}

StackErrorCode CheckCanary(Stack* stk) {
    if (stk->data[0] != CANARY || stk->data[stk->capacity + 1] != CANARY) {
        return ERROR_CANARY_DIED;
    }
    return SUCCESS;
}