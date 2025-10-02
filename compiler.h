#ifndef COMPILER_H
#define COMPILER_H


char* GetText(const char* source, int file_size);
long GetFileSize(const char* source);
int* get_byte_code(const char * source);

#endif