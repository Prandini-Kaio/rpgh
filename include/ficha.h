#ifndef RPG2_FICHA_H
#define RPG2_FICHA_H
#include "ocupacao.h"

typedef struct{
    int id;
    int idTable;
    //atributos
    char playerName[100];
    char investigatorName[100];
    Ocupation ocupation;
    int age;
    int sex;
    //Pericias
}Sheet;

struct NoSheet{
    struct NoSheet *next;
    Sheet sheet;
    struct NoSheet *previous;
};

typedef struct {
    struct NoSheet *start;
    struct NoSheet *end;
}SheetList;

//List
int CreateSheetList(SheetList *sheetList);
int InsertInSheetList(SheetList *sheetList, Sheet sheet);
void ShowSheetList(SheetList sheetList);

void CreateSheet(MYSQL *, Sheet *, int);

//DataBase

int CreateSheetDB(MYSQL *);
int InsertInSheetDB(MYSQL *, Sheet *);
int SetSheetDB(MYSQL *, Sheet);

int LoadSheets(MYSQL *, SheetList *, int);
#endif //RPG2_FICHA_H
