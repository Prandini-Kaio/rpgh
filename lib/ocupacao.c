#include "../include/ocupacao.h"

//Lista
void CreateOcupationList(OcupationList *ocupationList){
    ocupationList->start = NULL;
    ocupationList->end = NULL;
}

int InsertInOcupationList(OcupationList *ocupationList, Ocupation ocupation){
    struct NoOcupation *aux;
    aux = (struct NoOcupation *)malloc(sizeof(struct NoOcupation));
    aux->ocupation = ocupation;
    if(ocupationList->start == NULL){
        ocupationList->start = aux;
        ocupationList->end = aux;
        aux->next = ocupationList->start;
        aux->prev = ocupationList->end;
        return 1;
    }

    aux->prev = ocupationList->end;
    ocupationList->end->next = aux;
    aux->next = ocupationList->start;
    ocupationList->start->prev = aux;
    ocupationList->end = aux;
    return 0;
}

void ShowOcupationList(OcupationList ocupationList){
    struct NoOcupation *aux;
    if(ocupationList.start == NULL){
        printf("\nLista Vazia\n");
        return;
    }
    aux = ocupationList.start;
    do {
        printf("\n--------------------%s--------------------\n", aux->ocupation.name);
        printf("ID: %d\n", aux->ocupation.ID);
        printf("Credit Level: %d / %d\n", aux->ocupation.minCreditLevel, aux->ocupation.maxCreditLevel);
        printf("\n--------------------------------------------------\n");
        aux = aux->next;
    } while (aux != ocupationList.start);
}

Ocupation GetOcupationByID(MYSQL *conn, int id){
    Ocupation ocupation;
    strcpy(ocupation.name, "NULL");
    conn = mysql_init(NULL);
    if (conn == NULL) {
        FinishWithErrors(conn);
        return ocupation;
    }

    if (mysql_real_connect(conn, SERVER, USERNAME, PASS, DB, 0, NULL, 0) == NULL) {
        FinishWithErrors(conn);
        return ocupation;
    }
    char query[100];
    sprintf(query, "SELECT * FROM ocupacao WHERE ID = %d", id);
    if(mysql_query(conn, query)){
        FinishWithErrors(conn);
        return ocupation;
    }
    MYSQL_RES *res = mysql_store_result(conn);

    if(!res)//Se nao obtiver dados no retorno
    {
        FinishWithErrors(conn);
        return ocupation;
    }
    //Armazena as colunas da tabela
    MYSQL_ROW row;

    //Percorre todas as rows retornadas no resultado
    while ((row = mysql_fetch_row(res)))
    {
        ocupation.ID = atoi(row[0]);
        strcpy(ocupation.name, row[1]);
        ocupation.minCreditLevel = atoi(row[2]);
        ocupation.maxCreditLevel = atoi(row[3]);
        return ocupation;
    }

    mysql_free_result(res);
    FinishWithErrors(conn);
    return ocupation;
}

int LoadOcupation(MYSQL *conn, OcupationList *ocupationList){
    CreateOcupationDB(conn);
    CreateOcupationList(ocupationList);
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
    char query[100] = "SELECT * FROM ocupacao";
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
    //Armazena as colunas da tabela
    MYSQL_ROW row;

    Ocupation ocupation;
    //Percorre todas as rows retornadas no resultado
    while ((row = mysql_fetch_row(res)))
    {
        ocupation.ID = atoi(row[0]);
        strcpy(ocupation.name, row[1]);
        ocupation.minCreditLevel = atoi(row[2]);
        ocupation.maxCreditLevel = atoi(row[3]);
        InsertInOcupationList(ocupationList, ocupation);
    }

    mysql_free_result(res);
    FinishWithErrors(conn);
    return 1;
}

int CreateOcupationDB(MYSQL *conn){
    conn = mysql_init(NULL);
    if (conn == NULL) {
        FinishWithErrors(conn);
        return 0;
    }

    if (mysql_real_connect(conn, SERVER, USERNAME, PASS, DB, 0, NULL, 0) == NULL) {
        FinishWithErrors(conn);
        return 0;
    }

    if(mysql_query(conn, "CREATE TABLE IF NOT EXISTS ocupacao(ID int auto_increment primary key,nome VARCHAR ( 150 ) UNIQUE NOT NULL,minCreditValue int NOT NULL,maxCreditValue int NOT NULL,IDPericia1 int,IDPericia2 int,IDPericia3 int,IDPericia4 int,IDPericia5 int,IDPericia6 int,IDPericia7 int, IDPericia8 int,IDPericia9 int)")){
        FinishWithErrors(conn);
        return 0;
    }
    FinishWithErrors(conn);
    return 1;
}