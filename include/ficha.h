#ifndef RPG2_FICHA_H
#define RPG2_FICHA_H

typedef struct{
    int id;
    int idTable;
    //atributos
    char playerName[100];
    char investigatorName[100];
    //Ocupacao
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
#endif //RPG2_FICHA_H
