#include "stdio.h"
#include "compiler.h"
#include <sys/stat.h>
#include <stdlib.h>
#include <assert.h>
#include "macros.h"
#include <string.h>

#define MAX_LINE_LENGTH 100
#define MAX_COMMAND_LENGTH 15



/*long GetFileSize(const char* source) {

    const char *filename = source;
    struct stat file_info;
    stat(filename, &file_info);
    return file_info.st_size;
}
*/

int main() {
    CreateByteCodeFile(AsmCodeFile, ByteCodeFile);
}


/*int CreateByteCodeFile(const char* asm_code_file_name, const char* byte_code_file_name) {
    printf("\n\n\n");
    long file_size = GetFileSize(source);
    char* text = GetText(source, file_size);

    printf("%s", text);
    return NULL;

    FILE *asm_code_file = fopen(asm_code_file_name, "r");
    FILE *byte_code_file = fopen(byte_code_file_name, "w");
    if (asm_code_file == NULL || byte_code_file == NULL) {
        printf("Can\'t open file\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH] = {0};
    char command[MAX_COMMAND_LENGTH] = {0};
    int number = 0;

    while (fgets(line, sizeof(line), asm_code_file)) {
        line[strcspn(line, "\n")] = '\0';
        int how_much_read = sscanf(line, "%s %d", command, &number);
        int error = AddCommandToFile(byte_code_file, how_much_read, command, number);
        if (error) {
            printf("ERROR\n");
            break;
        }


    }

    fclose(asm_code_file);
    fclose(byte_code_file);
    return 0;
}*/

int CreateByteCodeFile(const char* asm_code_file_name, const char* byte_code_file_name) {
    FILE *asm_code_file = fopen(asm_code_file_name, "r");
    FILE *byte_code_file = fopen(byte_code_file_name, "w");
    int how_many_read = 0;
    char command[20];
    int number = 0;
    while (((how_many_read = fscanf(asm_code_file, "%s", &command)) > 0)) {
        if (strcmp(command, "PUSH") == 0) {
            fscanf(asm_code_file, "%d", &number);
            how_many_read++;
        }
        AddCommandToFile(byte_code_file, how_many_read, command, number);
    }
    fclose(asm_code_file);
    fclose(byte_code_file);
    return 0;
}



int AddCommandToFile(FILE *byte_code_file, int how_much_read, const char* command, int number) {
    int command_code = CommandToNumber(command);
    if (command_code == -1) {
        return 1;
    }
    if (how_much_read == 2) {
        fprintf(byte_code_file, "%d %d\n", command_code, number);
    } else if (how_much_read == 1) {
        fprintf(byte_code_file, "%d\n", command_code);
    }
    return 0;
}


int CommandToNumber(const char* command) {
    if (strcmp(command, "HLT") == 0){
        return 0;
    } else if (strcmp(command, "PUSH") == 0) {
        return 1;
    } else if (strcmp(command, "MUL") == 0){
        return 2;
    } else if (strcmp(command, "SUB") == 0){
        return 3;
    } else if (strcmp(command, "OUT") == 0){
        return 4;
    } else if (strcmp(command, "ADD") == 0){
        return 5;
    } else if (strcmp(command, "DIV") == 0){
        return 6;
    } else if (strcmp(command, "SQRT") == 0){
        return 7;
    }
    return -1;
}