#include "memstore.h"
#include <string.h>

// row serialize date to db, for we store
void serializeRow(Row* row, void* destination) {
    memcpy(destination + ID_OFFSET, &(row->id), ID_SIZE);
    memcpy(destination + USERNAME_OFFSET, &(row->username), USERNAME_SIZE);
    memcpy(destination + EMAIL_OFFSET, &(row->email), EMAIL_SIZE);
}

// row deserialize from db to a dest, for we read
void deserialize_row(void* row, Row* destination) {
    memcpy(&(destination->id), row + ID_OFFSET, ID_SIZE);
    memcpy(&(destination->username), row + USERNAME_OFFSET, USERNAME_SIZE);
    memcpy(&(destination->email), row + EMAIL_OFFSET, EMAIL_SIZE);
}

