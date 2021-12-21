#ifndef EXECUTE_H
#define EXECUTE_H

#include "input.h"

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

void executeStatement(Statement* statement);

MetaCommandResult doMetaCommand(InputBuffer* inputBuffer);

PrepareResult prepareStatement(InputBuffer* inputBuffer, Statement* statement);

#endif