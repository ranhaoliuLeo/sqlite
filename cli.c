#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    // buffer 输入缓冲指针
    char *buffer;
    // buffer_length 缓冲长度
    size_t buffer_length;
    // input_length 输入长度
    ssize_t input_length;
} InputBuffer;

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNKNOWN
} MetaCommandResult;

typedef enum {
    PREPARE_SUCCESS,
    PREPARE_UNKNOWN,
} PrepareResult;

typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

typedef struct {
    StatementType type;
} Statement;

InputBuffer *new_input_buffer();

void print_prompt() { printf("db > "); }

void read_input(InputBuffer *inputBuffer);

void closeInputBuffer(InputBuffer *inputBuffer);

void executeStatement(Statement* statement);

MetaCommandResult doMetaCommand(InputBuffer* inputBuffer);

PrepareResult prepareStatement(InputBuffer* inputBuffer, Statement* statement);

int main(int argc, char *argv[]) {
    InputBuffer *input_buffer = new_input_buffer();
    while (true) {
        print_prompt();
        read_input(input_buffer);
        if ((input_buffer->buffer)[0] == '.') {
            switch (doMetaCommand(input_buffer)) {
            case (META_COMMAND_SUCCESS):
                continue;
            case (META_COMMAND_UNKNOWN):
                printf("Unkown command '%s'\n", input_buffer->buffer);
                continue;
            }
        }
        Statement statement;
        switch (prepareStatement(input_buffer, &statement)) {
        case (PREPARE_SUCCESS):
            break;
        case (PREPARE_UNKNOWN):
            printf("Unrecognize keyword at start of '%s'. \n", input_buffer->buffer);
            break;
        }
        executeStatement(&statement);
        printf("Executed.\n");
    }
}

// new_input_buffer 初始化用户输入缓冲
InputBuffer *new_input_buffer() {
    InputBuffer *input_buffer = malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;
    return input_buffer;
}

// read_input 从stdin读取输入，将内容放置到输入缓冲
void read_input(InputBuffer *input_buffer) {
    ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);
    if (bytes_read <= 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }
    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;
}

// closeInputBuffer 释放输入缓存的内存
void closeInputBuffer(InputBuffer *input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}

// doMetaCommand 匹配元命令
MetaCommandResult doMetaCommand(InputBuffer* inputBuffer) {
    if (strcmp(inputBuffer->buffer, ".exit") == 0) {
        exit(EXIT_SUCCESS);
        return META_COMMAND_SUCCESS;
    }
    return META_COMMAND_UNKNOWN;
}

// prepareStatement 处理器前端，转换字符串为命令
PrepareResult prepareStatement(InputBuffer* inputBuffer, Statement* statement) {
    if (strncmp(inputBuffer->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }
    if (strcmp(inputBuffer->buffer, "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }
    return PREPARE_UNKNOWN;
}

// executeStatement 虚拟机执行命令
void executeStatement(Statement* statement) {
    switch (statement->type) {
    case (STATEMENT_INSERT):
         printf("This is where we would do an insert.\n");
        break;
    
    case (STATEMENT_SELECT):
        printf("This is where we would do a select.\n");
        break;
    }
}