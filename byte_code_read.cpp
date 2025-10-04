
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

/*int* ReadByteCode(const char* byte_code_file_name, int* number_of_elements) {
    FILE *byte_code_file = fopen(byte_code_file_name, "r");
    long file_size = GetFileSize(byte_code_file_name);
    char* data = (char*) calloc(sizeof(char), (file_size + 1)); // TODO: text == NULL? + calloc
    int byte_code_size = 10;
    int elements_in_byte_code = 0;
    int* byte_code = (int*) calloc(sizeof(int), byte_code_size);
    fread(data, 1, file_size, byte_code_file);
    fclose (byte_code_file);
    data[file_size] = '\0';
    int command = 0;
    int number = 0;
    int how_many_read = 0;
    int index = 0;
    data[strcspn(data, "\n")] = '\0';
    //printf("%s", data);
    
    while (((how_many_read = sscanf(data, "%d %d", &command, &number)) > 0)) {
        //printf("debug: %d,  %d\n", command, number);
        //printf("how_many_read: %d\n", how_many_read);
        if (elements_in_byte_code + 2 >= byte_code_size) {
            elements_in_byte_code *= 2;
            byte_code = (int*) realloc(byte_code, byte_code_size * sizeof(int));
        }
        data = strchr(data + 1, '\0') + 1;
        //printf("data %s", data);
        data[strcspn(data, "\n")] = '\0';
        *(byte_code + index) = command;
        index++;
        //printf("*byte_code %d\n", *byte_code);
        elements_in_byte_code++;
        if (how_many_read == 2) {
            //printf("HERE\n");
            *(byte_code + index) = number;
            index++;
            elements_in_byte_code++;
        }
        //printf("%s\n", data);
    }
    //printf("NEW *byte_code %d\n", *byte_code);
    *number_of_elements = elements_in_byte_code;
    return byte_code;
    //ferror/feof
    

    
}*/


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