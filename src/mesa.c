#include "stdio.h"
#include <malloc.h>
#include <time.h>
#include <string.h>

#include "../headers/mesa.h"

/*
 * Lista De Mesas
 *      - Table
 *          - ID
 *          - Data de abertura da mesa
 *          - Titulo
 *          - Nome do mestre
 *          - Lista De Jogadores
 *          - Lista De Secoes
 *              - Secao
 *                  - Data de abertura
 *                  - Numero da secao
 * */

//Criar uma mesa
//Criar uma lista de mesas
//Adicionar uma mesa na lista

void CreateTableList(TableList *tableList){
    tableList->start = NULL;
    tableList->end = NULL;
}

int InsertInTableList(TableList *tableList, Table table){
    struct NoTable *aux;
    aux = (struct NoTable *)malloc(sizeof(struct NoTable));
    aux->table = table;
    if(tableList->start == NULL){

        tableList->start = aux;
        tableList->end = aux;
        aux->next = tableList->start;
        aux->prev = tableList->end;
        return 1;
    }

    aux->prev = tableList->end;
    tableList->end->next = aux;
    aux->next = tableList->start;
    tableList->start->prev = aux;
    tableList->end = aux;
    return 1;
}

void ShowTableList(TableList tableList){
    struct NoTable *aux;
    if(tableList.start == NULL) printf("LISTA VAZIA\n");
    aux = tableList.start;

    do {
        printf("\n--------------------%d--------------------\n", aux->table.id);
        printf("\nMaster: %s\n", aux->table.masterName);
        printf("Title: %s\n", aux->table.title);
        printf("Open In: %d / %d / %d. %d:%d:%d \n", aux->table.day,
               aux->table.mounth, aux->table.year, aux->table.hours, aux->table.minutes, aux->table.seconds);
        printf("\n------------------------------------------\n");
        aux = aux->next;
    } while (aux != tableList.start);
}

Table GetTableById(TableList tableList,int id){
    struct NoTable *aux;
    if(tableList.start == NULL) printf("\nEMPTY LIST\n");
    aux = tableList.start;
    do {
        if(aux->table.id == id){
            printf("\nFOUND TABLE\n");
            return aux->table;
        }
        aux = aux->next;
    } while (aux != tableList.start);
    printf("\nTABLE NOT EXISTS\n");
}

int CreateTable(Table *table, SectionList sectionList, char masterName[50], char title[50], int lastID){
    time_t t = time(NULL);

    table->year = localtime(&t)->tm_year + 1900;
    table->mounth = localtime(&t)->tm_mon + 1;
    table->day = localtime(&t)->tm_mday;

    table->hours = localtime(&t)->tm_hour;
    table->minutes = localtime(&t)->tm_min;
    table->seconds = localtime(&t)->tm_sec;

    table->sectionList = sectionList;

    strcpy(table->masterName, masterName);
    strcpy(table->title, title);

    table->id = 1 + lastID;
    return 1;
}