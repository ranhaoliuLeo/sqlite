#include "memstore.h"
#include <string.h>


const uint32_t ID_SIZE = sizeOfAttribute(Row, id);
const uint32_t USERNAME_SIZE = sizeOfAttribute(Row, username);
const uint32_t EMAIL_SIZE = sizeOfAttribute(Row, email);
const uint32_t ID_OFFSET = 0;
const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;
const uint32_t PAGE_SIZE = 4096;
const uint32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;
const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

// row serialize date to db, for we store
void serializeRow(Row* row, void* destination) {
    memcpy(destination + ID_OFFSET, &(row->id), ID_SIZE);
    memcpy(destination + USERNAME_OFFSET, &(row->username), USERNAME_SIZE);
    memcpy(destination + EMAIL_OFFSET, &(row->email), EMAIL_SIZE);
}

// row deserialize from db to a dest, for we read
void deserializeRow(void* row, Row* destination) {
    memcpy(&(destination->id), row + ID_OFFSET, ID_SIZE);
    memcpy(&(destination->username), row + USERNAME_OFFSET, USERNAME_SIZE);
    memcpy(&(destination->email), row + EMAIL_OFFSET, EMAIL_SIZE);
}

// printRow it will print row data
void printRow(Row* row) {
    printf("(%d, %s, %s)\n", row->id, row->username, row->email);
}

// rowSlot get a slot begin ptr of new data, then we can fill it in mem.
void* rowSlot(Table* table, uint32_t rowNum) {
    // get the position of this row should be.
    uint32_t pageNum = rowNum / ROWS_PER_PAGE;
    void* page = table->pages[pageNum];
    if (page == NULL) {
        // Allocate memory only when we try to access page
        page = table->pages[pageNum] = malloc(PAGE_SIZE);
    }
    uint32_t rowOffset = rowNum % ROWS_PER_PAGE;
    uint32_t byteOffset = rowOffset * ROW_SIZE;
    return page + byteOffset;
}

// newTable create a new Table, and pages will all set to NULL.
Table* newTable() {
    Table* table = malloc(sizeof(Table));
    table->numRows = 0;
    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
        table->pages[i] = NULL;
    }
    return table;
}

// freeTable free the table in the mem, and note the pages ptr, we need to free them too. 
void freeTable(Table *table) {
    for (int i = 0; table->pages[i]; i++) {
        free(table->pages[i]);
    }
    free(table);
}

