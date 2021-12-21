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