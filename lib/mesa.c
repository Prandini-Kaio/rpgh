#include <stdio.h>
#include <time.h>
#include <string.h>

#include "../include/mesa.h"

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
    }else if(tableList->start != NULL){
        aux->prev = tableList->end;
        tableList->end->next = aux;
        aux->next = tableList->start;
        tableList->start->prev = aux;
        tableList->end = aux;
        return 1;
    }
    return 0;
}

void ShowTableList(TableList tableList){
    struct NoTable *aux;
    if(tableList.start == NULL) printf("LISTA VAZIA\n");
    aux = tableList.start;

    do {
        printf("\n--------------------%d--------------------\n", aux->table.id);
        printf("\nMaster: %s\n", aux->table.masterName);
        printf("Title: %s\n", aux->table.title);
        printf("Open IN: %s\n", aux->table.openDate);
        printf("\n------------------------------------------\n");
        aux = aux->next;
    } while (aux != tableList.start);
}

Table *GetTableById(TableList tableList, int id){
    struct NoTable *aux;
    if(tableList.start == NULL) printf("\nEMPTY LIST\n");
    aux = tableList.start;
    do {
        if(aux->table.id == id){
            printf("\nFOUND TABLE\n");
            return &aux->table;
        }
        aux = aux->next;
    } while (aux != tableList.start);
    printf("\nTABLE NOT EXISTS\n");
    return &aux->table;
}

int CreateTable(MYSQL *conn, Table *table, char masterName[100], char title[100]){
    CreateTableDB(conn);

    time_t t = time(NULL);

    char d[20];
    strcpy(d, asctime(localtime(&t)));
    strcpy(table->openDate, d);

    CreateSectionList(&table->sectionList);

    strcpy(table->masterName, masterName);
    strcpy(table->title, title);

    InsertTableDB(conn, table);
    return 1;
}

/*
 *
 * DATABASE
 *
 */

int CreateTableDB(MYSQL *conn){
    //Inicia conexao
    conn = mysql_init(NULL);
    if (conn == NULL) {
        FinishWithErrors(conn);
        return 0;
    }
    //Faz a conexao ao banco de dados com as informações necessarias
    if (mysql_real_connect(conn, SERVER, USERNAME, PASS, DB, 0, NULL, 0) == NULL) {
        FinishWithErrors(conn);
        return 0;
    }
    //Query SQL
    if(mysql_query(conn, "CREATE TABLE IF NOT EXISTS mesa(ID int PRIMARY KEY AUTO_INCREMENT, title VARCHAR(150) NOT NULL, masterName VARCHAR(150) NOT NULL, openDate VARCHAR(50) NOT NULL, sheetsID int NOT NULL, sectionsID int)"))
    {
        FinishWithErrors(conn);
        return 0;
    }

    printf("\nTable mesa created\n");
    FinishWithErrors(conn);
    return 1;
}

int InsertTableDB(MYSQL *conn, Table *table){
    conn = mysql_init(NULL);
    if (conn == NULL) {
        FinishWithErrors(conn);
        return 0;
    }

    if (mysql_real_connect(conn, SERVER, USERNAME, PASS, DB, 0, NULL, 0) == NULL) {
        FinishWithErrors(conn);
        return 0;
    }

    char query[200];
    sprintf(query, "INSERT INTO mesa(ID, title, masterName, openDate, sheetsID, sectionsID) VALUES(0, '%s', '%s', '%s', %d, %d)",
            table->title, table->masterName, table->openDate, table->sheetsID, table->sectionsID);

    int res = mysql_query(conn, query);

    if(res)
        FinishWithErrors(conn);

    table->id = (int)mysql_insert_id(conn);

    printf("Mesas inseridas: %d\n", (int)mysql_affected_rows(conn));
    FinishWithErrors(conn);
    return 1;
}


int LoadTableList(MYSQL *conn, TableList *tableList){
    CreateTableList(tableList);

    //Ler os dados do BD e popular a lista
    conn = mysql_init(NULL);
    if (conn == NULL) {
        FinishWithErrors(conn);
        return 0;
    }

    if (mysql_real_connect(conn, SERVER, USERNAME, PASS, DB, 0, NULL, 0) == NULL) {
        FinishWithErrors(conn);
        return 0;
    }

    if(mysql_query(conn, "SELECT * FROM mesa")){
        FinishWithErrors(conn);
        return 0;
    }

    MYSQL_RES *res = mysql_store_result(conn);

    if(!res){
        printf("EMPTY TABLE\n");
        FinishWithErrors(conn);
        return 0;
    }

    MYSQL_ROW row;
    Table table;
    while((row = mysql_fetch_row(res))){
        table.id = atoi(row[0]);
        strcpy(table.title, row[1]);
        strcpy(table.masterName, row[2]);
        strcpy(table.openDate, row[3]);
        table.sheetsID = atoi(row[4]);
        table.sectionsID = atoi(row[5]);
        InsertInTableList(tableList, table);
    }

    mysql_free_result(res);
    FinishWithErrors(conn);
    return 1;
}