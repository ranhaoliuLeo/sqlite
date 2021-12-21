#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "global.h"

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