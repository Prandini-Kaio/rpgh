#ifndef RPG2_MESA_H
#define RPG2_MESA_H

#include <time.h>
#include <mysql/mysql.h>
#include "section.h"

typedef struct{
    int id;
    char openDate[50];
    char masterName[50];
    char title[50];
    int sheetsID;
    int sectionsID;

    SectionList sectionList;
}Table;

struct NoTable{
    struct NoTable *next;
    Table table;
    struct NoTable *prev;
};

typedef struct {
    struct NoTable *start;
    struct NoTable *end;
} TableList;

//TableList
void CreateTableList(TableList *);
int InsertInTableList(TableList *, Table);
void ShowTableList(TableList);
Table *GetTableById(TableList, int);

int CreateTable(MYSQL *, Table *, char[], char[],int);

//Database
int CreateTableDB(MYSQL *);

int InsertTableDB(MYSQL *connection, Table *table);
int GetTableDB(MYSQL *connection);
int SetTableDB(MYSQL *connection, Table table);

int PopulateTableList(MYSQL *connection, TableList *tableList);
#endif //RPG2_MESA_H
