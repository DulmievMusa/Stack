#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "macros.h"
#include "data_types.h"
#include "constants.h"
#include "asserts.h"
#include "stack_operations.h"
#include "stack_security.h"
#include "compiler.h"


int DoCommand(Stack* stk, char* command, int value, int how_much_read, int* errors);

int main() {
    Stack stk = {};
    StackInit(&stk, 6);
    char input[100];
    char command[30];
    int how_much_read = 0;
    int value = 0;
    //stk.data[0] = 666;
    // stk.data = NULL;
    // stk.size = -1;
    // stk.capacity = -1;
    int errors = 0;
    PrintErrorsInfo(errors);
    StackDump(&stk);
    int need_to_finish = 0;

    get_byte_code(SOURCE);

    while (need_to_finish == 0) {
        fgets(input, sizeof(input), stdin);
        how_much_read = sscanf(input, "%29s %d", command, &value);
        need_to_finish = DoCommand(&stk, command, value, how_much_read, &errors);
        // StackDump(&stk);
    }
}



int DoCommand(Stack* stk, char* command, int value, int how_much_read, int* errors) {
    *errors = StackVerify(stk);
    if (strcmp(command, "PUSH") == 0 && how_much_read == 2) {
        StackPush(stk, value);
    } else if (strcmp(command, "OUT") == 0 && how_much_read == 1 && stk->size > 0) {
        printf("%d\n", StackPop(stk, errors));
    } else if (strcmp(command, "SUB") == 0 && how_much_read == 1 && stk->size > 1) {
        int a = StackPop(stk, errors);
        int b = StackPop(stk, errors);
        StackPush(stk, b - a);
    } else if (strcmp(command, "ADD") == 0 && how_much_read == 1 && stk->size > 1) {
        int a = StackPop(stk, errors);
        int b = StackPop(stk, errors);
        StackPush(stk, b + a);
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
    if (!(*errors))  {
        *errors = StackVerify(stk);
    }
    return 0;
}