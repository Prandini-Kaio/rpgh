#include <stdio.h>
#include <mysql/mysql.h>
#include <string.h>
#include <time.h>

#include "../include/section.h"
#include "../include/dbconnect.h"

//Lista
void CreateSectionList(SectionList *sectionList){
    sectionList->start = NULL;
    sectionList->end = NULL;
}

int InsertInSectionList(SectionList *sectionList, Section section){
    struct NoSection *aux;
    aux = (struct NoSection *)malloc(sizeof(struct NoSection));
    aux->section = section;
    if(sectionList->start == NULL){

        sectionList->start = aux;
        sectionList->end = aux;
        aux->next = sectionList->start;
        aux->prev = sectionList->end;
        return 1;
    }

    aux->prev = sectionList->end;
    sectionList->end->next = aux;
    aux->next = sectionList->start;
    sectionList->start->prev = aux;
    sectionList->end = aux;
    if(aux == NULL) return 0;
    return 1;
}

void ShowSectionList(SectionList sectionList){
    struct NoSection *aux;
    if(sectionList.start == NULL) {
        printf("\nLISTA VAZIA\n");
        return;
    }
    aux = sectionList.start;
    do {
        printf("\n--------------------SECTION %d--------------------\n", aux->section.numberSec);
        printf("Open In: %s\n", aux->section.openDate);
        printf("Close In: %s\n", aux->section.openDate);
        printf("\n--------------------------------------------------\n");
        aux = aux->next;
    } while (aux != sectionList.start);
}
//

//Section
int CreateSection(MYSQL *conn, Section *section, int tableID){
    CreateSectionDB(conn);

    int nS = GetLastSectionID(conn, tableID);
    section->numberSec = nS + 1;
    section->idTable = tableID;
    section->idAnotation = 0;

    //OpenDate
    time_t t = time(NULL);
    char d[30];
    strcpy(d, asctime(localtime(&t)));
    strcpy(section->openDate, d);
    strcpy(section->closeDate, "");
    //
    InsertSectionDB(conn, section);
    return 1;
}

/*
 *
 * DATABASE
 *
 */

int CreateSectionDB(MYSQL *conn){
    conn = mysql_init(NULL);
    if (conn == NULL) {
        FinishWithErrors(conn);
        return 0;
    }

    if (mysql_real_connect(conn, SERVER, USERNAME, PASS, DB, 0, NULL, 0) == NULL) {
        FinishWithErrors(conn);
        return 0;
    }

    if(mysql_query(conn, "CREATE TABLE IF NOT EXISTS section(ID int PRIMARY KEY AUTO_INCREMENT, indexSec int NOT NULL, IDTable int NOT NULL,IDanotation int ,openDate VARCHAR(50) NOT NULL,closeDate VARCHAR(50))")){
        FinishWithErrors(conn);
        return 0;
    }
    FinishWithErrors(conn);
    return 1;
}

//CREATE
int InsertSectionDB(MYSQL *conn, Section *section){
    //Abre a conexao c o banco
    conn = mysql_init(NULL);
    if (conn == NULL) {
        FinishWithErrors(conn);
        return 0;
    }

    if (mysql_real_connect(conn, SERVER, USERNAME, PASS, DB, 0, NULL, 0) == NULL) {
        FinishWithErrors(conn);
        return 0;
    }

    char query[150];
    sprintf(query, "INSERT INTO section(ID, indexSec, IDTable, IDanotation, openDate, closeDate) VALUES(0, %d, %d, %d, '%s', '%s')",
            section->numberSec, section->idTable, 0, section->openDate, section->closeDate);
    int res = mysql_query(conn, query);
    if(res)
        FinishWithErrors(conn);

    section->id = mysql_insert_id(conn);

    printf("Inseridos: %d\n", (int)mysql_affected_rows(conn));
    FinishWithErrors(conn);
    return 1;
}
//READ
int GetSection(MYSQL *conn){

    conn = mysql_init(NULL);
    if (conn == NULL) {
        FinishWithErrors(conn);
        return 0;
    }

    if (mysql_real_connect(conn, SERVER, USERNAME, PASS, DB, 0, NULL, 0) == NULL) {
        FinishWithErrors(conn);
        return 0;
    }

    if(mysql_query(conn, "SELECT * FROM section")) {
        FinishWithErrors(conn);
        return 0;
    }

    MYSQL_RES *res = mysql_store_result(conn);

    if(!res)//Se nao obtiver dados no retorno
    {
        printf("EMPTY TABLE\n");
        FinishWithErrors(conn);
        return 0;
    }

    //Numero de titulos da tabela
    int num_fields = mysql_num_fields(res);

    //Armazena as colunas da tabela
    MYSQL_ROW row;

    printf("\n----------------------------------------\n");
    //Percorre todas as rows retornadas no resultado
    while ((row = mysql_fetch_row(res)))
    {
        for(int i = 0; i < num_fields; i++)
        {
            printf(" %s ", row[i] ? row[i] : "NULL");
        }
        printf("\n--------------------/-------------------\n");
    }

    mysql_free_result(res);
    FinishWithErrors(conn);
    return 1;
}
//UPDATE
int SetSection(MYSQL *conn, Section section){
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
    sprintf(query, "UPDATE section SET IDTable = %d, IDanotation = %d, openDate = '%s', closeDate = '%s' WHERE ID = %d",
            section.idTable, section.idAnotation,
            asctime(localtime((long *)&section.openDate)),
            asctime(localtime((long *)&section.closeDate)), section.id);


    int res = mysql_query(conn, query);

    if(res)
        FinishWithErrors(conn);

    printf("Atualizados: %d\n", (int)mysql_affected_rows(conn));
    return 1;
}
//

int GetLastSectionID(MYSQL *conn, int IDTable){
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

    char query[100];
    sprintf(query, "SELECT * FROM section WHERE IDTable = %d", IDTable);
    if(mysql_query(conn, query)) {
        FinishWithErrors(conn);
        return 0;
    }

    MYSQL_RES *res = mysql_store_result(conn);

    if(!res)//Se nao obtiver dados no retorno
    {
        printf("EMPTY TABLE\n");
        FinishWithErrors(conn);
        return 0;
    }
    //Armazena as colunas da tabela
    MYSQL_ROW row;

    int tmp = 0;

    //Percorre todas as rows retornadas no resultado
    while ((row = mysql_fetch_row(res)))
    {
        if(tmp < atoi(row[1]))
            tmp = atoi(row[1]);
    }
    mysql_free_result(res);
    FinishWithErrors(conn);
    return tmp;
}

int PopulateSectionList(MYSQL *conn, SectionList *sectionList, int tableID){
    CreateSectionDB(conn);
    CreateSectionList(sectionList);
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
    char query[100];
    sprintf(query, "SELECT * FROM section WHERE IDTable = %d", tableID);
    if(mysql_query(conn, query)){
        FinishWithErrors(conn);
        return 0;
    }
    MYSQL_RES *res = mysql_store_result(conn);

    if(!res)//Se nao obtiver dados no retorno
    {
        FinishWithErrors(conn);
        return 0;
    }

//    //Numero de titulos da tabela
//    int num_fields = mysql_num_fields(res);

    //Armazena as colunas da tabela
    MYSQL_ROW row;

    Section section;
    //Percorre todas as rows retornadas no resultado
    while ((row = mysql_fetch_row(res)))
    {
        section.id = atoi(row[0]);
        section.numberSec = atoi(row[1]);
        section.idTable = atoi(row[2]);
        section.idAnotation = atoi(row[3]);
        strcpy(section.openDate, row[4]);
        strcpy(section.closeDate, row[5]);
        InsertInSectionList(sectionList, section);
    }

    mysql_free_result(res);
    FinishWithErrors(conn);
    return 1;
}