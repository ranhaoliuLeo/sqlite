// input.h 输入相关函数声明
#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    // buffer 输入缓冲指针
    char *buffer;
    // buffer_length 缓冲长度
    size_t buffer_length;
    // input_length 输入长度
    ssize_t input_length;
} InputBuffer;

InputBuffer *new_input_buffer();

void print_prompt();

void read_input(InputBuffer *inputBuffer);

void closeInputBuffer(InputBuffer *inputBuffer);

#endif