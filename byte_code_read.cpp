
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <assert.h>

#include "byte_code_read.h"


long GetFileSize(const char* source) {
    assert(source != NULL);

    const char *filename = source;
    struct stat file_info;
    stat(filename, &file_info);
    return file_info.st_size;
}




int* ReadByteCode(const char* byte_code_file_name, int* number_of_elements) {
    FILE *byte_code_file = fopen(byte_code_file_name, "r");
    int byte_code_size = 10;
    int* byte_code = (int*) calloc(sizeof(int), byte_code_size);
    int elements_in_byte_code = 0;
    int how_many_read = 0;
    int command = 0;
    int number = 0;
    int index = 0;
    while (((how_many_read = fscanf(byte_code_file, "%d", &command)) > 0)) {

        if (elements_in_byte_code + 2 >= byte_code_size) {
            byte_code_size *= 2;
            byte_code = (int*) realloc(byte_code, byte_code_size * sizeof(int));
        }

        if (command == 1) {
            fscanf(byte_code_file, "%d", &number);
            how_many_read++;
        }
        if (how_many_read == 2) {
            byte_code[index] = command;
            index++;
            byte_code[index] = number;
            index++;
            *number_of_elements += 2;
        }
        else if (how_many_read == 1) {
            byte_code[index] = command;
            index++;
            *number_of_elements += 1;
        }
    }
    fclose(byte_code_file);
    return byte_code;

}