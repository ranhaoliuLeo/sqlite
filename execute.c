// execute.c 虚拟机执行命令相关逻辑
#include <stdio.h>
#include <stdlib.h>
#include "execute.h"
#include "input.h"
#include <string.h>


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
        int argsAssigned = sscanf(
            inputBuffer->buffer, "insert %d %s %s", 
            &(statement->rowToInsert.id), 
            &(statement->rowToInsert.username), 
            &(statement->rowToInsert.email)
        );
        if (argsAssigned < 3) {
            return PREPARE_SYNTAX_ERR;
        }
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