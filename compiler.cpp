#include "stdio.h"
#include "compiler.h"
#include <sys/stat.h>
#include <stdlib.h>
#include <assert.h>
#include "macros.h"

long GetFileSize(const char* source) {

    const char *filename = source;
    struct stat file_info;
    stat(filename, &file_info);
    return file_info.st_size;
}



int* get_byte_code(const char * source) {
        printf("\n\n\n");
    long file_size = GetFileSize(source);
    char* text = GetText(source, file_size);

    printf("%s", text);
    return NULL;
}

char* GetText(const char* source, int file_size) {
    assert(source != NULL);

    FILE* source_file = fopen(source, "r" );
    char* text = (char*) calloc(sizeof(char), (file_size + 1)); 
    fread(text, 1, file_size, source_file); 
    fclose (source_file);
    text[file_size] = '\0';
    return text;
}