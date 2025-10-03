#ifndef BYTE_CODE_READ_H
#define BYTE_CODE_READ_H

long GetFileSize(const char* source);
int* ReadByteCode(const char* byte_code_file_name, int* number_of_elements);

#endif