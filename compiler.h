#ifndef COMPILER_H
#define COMPILER_H


int AddCommandToFile(FILE *byte_code_file, int how_much_read, const char* command, int number);
int CreateByteCodeFile(const char* asm_code_file_name, const char* byte_code_file_name);
int CommandToNumber(const char* command);

#endif