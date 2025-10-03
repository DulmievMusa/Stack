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
#include "byte_code_read.h"
//#include "compiler.h"


int DoCommand(Stack* stk, char* command, int value, int how_much_read, int* errors);
int RunProgramm(Stack* stk, int* byte_code, int number_of_elements);

int main() {
    Stack stk = {};
    StackInit(&stk, 6);
    StackDump(&stk);
    /*char input[100];
    char command[30];
    int how_much_read = 0;
    int value = 0;
    //stk.data[0] = 666;
    // stk.data = NULL;
    // stk.size = -1;
    // stk.capacity = -1;
    int errors = 0;
    PrintErrorsInfo(errors);

    int need_to_finish = 0;

    while (need_to_finish == 0) {
        fgets(input, sizeof(input), stdin);
        how_much_read = sscanf(input, "%29s %d", command, &value);
        need_to_finish = DoCommand(&stk, command, value, how_much_read, &errors);
        // StackDump(&stk);
    }*/
   //char* byte_code = ReadByteCode(ByteCodeFile);

   /*char *token;
    
    // Получаем первую подстроку
    token = strtok(byte_code, "\n");
    
    // Получаем остальные подстроки
    while (token != NULL) {
        printf("Найдена строка: '%s'\n", token);
        token = strtok(NULL, "\n");
    }*/
   int number_of_elements;
   int* byte_code = ReadByteCode(ByteCodeFile, &number_of_elements);
   RunProgramm(&stk, byte_code, number_of_elements);
   /*for (int i = 0; i < number_of_elements; i++) {
        printf("%d\n", *(byte_code + i));
   }*/

   
}

int RunProgramm(Stack* stk, int* byte_code, int number_of_elements) {
    /*for (int i = 0; i < number_of_elements; i++) {
        printf("%d\n", *(byte_code + i));
    }*/

    int errors = StackVerify(stk);
    int index = 0;
    int command = 0;
    while (index < number_of_elements) {
        
        command = byte_code[index];
        printf("num %d, index %d, command %d\n", number_of_elements, index, command);
        int a = 0;
        int b = 0;
        switch (command) {
        case 0:
            return 0;
        case 1: 
            index++;
            StackPush(stk, byte_code[index]);
            break;
        case 2:
            a = StackPop(stk, &errors);
            b = StackPop(stk, &errors);
            StackPush(stk, a * b);
            break;
        case 3:
            a = StackPop(stk, &errors);
            b = StackPop(stk, &errors);
            StackPush(stk, b - a);
            break;
        case 4:
            printf("%d\n", StackPop(stk, &errors));
            break;
        case 5:
            a = StackPop(stk, &errors);
            b = StackPop(stk, &errors);
            StackPush(stk, b + a);
            break;
        case 6:
            a = StackPop(stk, &errors);
            b = StackPop(stk, &errors);
            StackPush(stk, (int) ((double) b / a));
            break;
        case 7:
            StackPush(stk, (int) sqrt(StackPop(stk, &errors)));
            break;
        default:
            printf("Unknown command\n");
            break;
        }
        index++;
    }
    return 0;
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