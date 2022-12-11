#include <stdio.h>
#include <malloc.h>
#include "../include/ficha.h"

int CreateSheetList(SheetList *sheetList){
    sheetList->start = NULL;
    sheetList->end = NULL;

    return 1;
}

int InsertInSheetList(SheetList *sheetList, Sheet sheet){
    struct NoSheet *aux;
    aux = (struct NoSheet *)malloc(sizeof(struct NoSheet));
    aux->sheet = sheet;
    if(sheetList->start == NULL){
        sheetList->start = aux;
        sheetList->end = aux;
        aux->next = sheetList->start;
        aux->previous = sheetList->end;
        return 1;
    }else if(sheetList->start != NULL){
        aux->previous = sheetList->end;
        sheetList->end->next = aux;
        aux->next = sheetList->start;
        sheetList->start->previous = aux;
        sheetList->end = aux;
        return 1;
    }
    return 0;
}

void ShowSheetList(SheetList sheetList){
    struct NoSheet *aux;
    if(sheetList.start == NULL) {
        printf("EMPTY SHEET LIST\n");
        return;
    }
    aux = sheetList.start;
    do{
        printf("DADOS\n\n");
    } while (aux != sheetList.start);
}