#ifndef RPG2_MESA_H
#define RPG2_MESA_H

#include <time.h>
#include "section.h"

typedef struct{
    int id;
    int year, mounth, day, hours, minutes, seconds;
    char masterName[50];
    char title[50];
    //Lista De Jogadores
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

void CreateTableList(TableList *);
int InsertInTableList(TableList *, Table);
void ShowTableList(TableList);
Table GetTableById(TableList, int);

int CreateTable(Table *, SectionList, char[], char[],int);
#endif //RPG2_MESA_H
