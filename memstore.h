#ifndef MEMSTORE_H
#define MEMSTORE_H
#include <stdlib.h>
// micro func for us to get the struct member size
#define sizeOfAttribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute);

// test data, hard code table, we limit size blow
#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

typedef struct {
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE];
    char email[COLUMN_EMAIL_SIZE];
} Row;

const uint32_t ID_SIZE = sizeOfAttribute(Row, id);
const uint32_t USERNAME_SIZE = sizeOfAttribute(Row, username);
const uint32_t EMAIL_SIZE = sizeOfAttribute(Row, email);
const uint32_t ID_OFFSET = 0;
const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

void serializeRow(Row* row, void* destination);
void deserializeRow(void* row, Row* destination);

#endif