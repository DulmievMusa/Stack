#ifndef DATA_TYPES_H
#define DATA_TYPES_H

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

#endif