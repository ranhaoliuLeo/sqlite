#ifndef MEMSTORE_H
#define MEMSTORE_H
#include <stdlib.h>
#include <stdio.h>

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

void printRow(Row* row);

extern const uint32_t ID_SIZE;
extern const uint32_t USERNAME_SIZE;
extern const uint32_t EMAIL_SIZE;; 
extern const uint32_t ID_OFFSET; 
extern const uint32_t USERNAME_OFFSET;
extern const uint32_t EMAIL_OFFSET; 
extern const uint32_t ROW_SIZE; 

void serializeRow(Row* row, void* destination);
void deserializeRow(void* row, Row* destination);

// Keep tracing data of mem
// we decide a page size is 4kb, every page will store many db data.
// this is because that is same as most cirtual memory system's page.Os will operate all 4kb at once.
// shortly, we do it for the performance. 
// and we give a limit of page's num, we can not contain too many data
extern const uint32_t PAGE_SIZE;
#define TABLE_MAX_PAGES 100
extern const uint32_t ROWS_PER_PAGE;
extern const uint32_t TABLE_MAX_ROWS;

typedef struct {
    uint32_t numRows;
    void* pages[TABLE_MAX_PAGES];
} Table;

void* rowSlot(Table* table, uint32_t rowNum);
Table* newTable();
void freeTable(Table *table);

#endif