#ifndef EXECUTE_H
#define EXECUTE_H

#include "input.h"
#include "memstore.h"
typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNKNOWN
} MetaCommandResult;

typedef enum {
    PREPARE_SUCCESS,
    PREPARE_UNKNOWN,
    PREPARE_SYNTAX_ERR,
} PrepareResult;

typedef enum {
    EXECUTE_TABLE_FULL = 1,
} ExcuteResult;

typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

typedef struct {
    StatementType type;
    Row rowToInsert;
} Statement;

ExcuteResult executeStatement(Statement* statement, Table* table);

MetaCommandResult doMetaCommand(InputBuffer* inputBuffer);

PrepareResult prepareStatement(InputBuffer* inputBuffer, Statement* statement);

ExcuteResult executeInsert(Statement* statement, Table* table);

ExcuteResult executeSelect(Statement* statement, Table* table);

#endif