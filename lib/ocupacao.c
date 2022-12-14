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

//

//int CreateOcupation(MYSQL *conn, Ocupation *ocupation){
//    CreateOcupationDB(conn);
//    conn = mysql_init(NULL);
//    if (conn == NULL) {
//        FinishWithErrors(conn);
//        return 0;
//    }
//
//    if (mysql_real_connect(conn, SERVER, USERNAME, PASS, DB, 0, NULL, 0) == NULL) {
//        FinishWithErrors(conn);
//        return 0;
//    }
//    char query[100];
//    sprintf(query, "SELECT * FROM periciaBase WHERE ID = %d", pericia->IDPericia);
//
//    if(mysql_query(conn, query)){
//        FinishWithErrors(conn);
//        return 0;
//    }
//    MYSQL_RES *res = mysql_store_result(conn);
//
//    if(!res)//Se nao obtiver dados no retorno
//    {
//        FinishWithErrors(conn);
//        return 0;
//    }
//    //Armazena as colunas da tabela
//    MYSQL_ROW row = mysql_fetch_row(res);
//
//    pericia->baseValue = atoi(row[1]);
//    pericia->metade = (pericia->baseValue + pericia->inteiro) / 2;
//    pericia->quinto = (pericia->baseValue + pericia->inteiro) / 5;
//    return 1;
//}

//

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

int InsertOcupationDB(MYSQL *conn, Ocupation ocupation){
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

    char query[230];
    sprintf(query, "INSERT INTO ocupacao( ID, nome, minCreditValue, maxCreditValue, IDPericia1, IDPericia2, IDPericia3, IDPericia4, IDPericia5, IDPericia6, IDPericia7, IDPericia8, IDPericia9)"
                   " VALUES ( 0, '%s', %d, %d)",
            ocupation.name, ocupation.minCreditLevel, ocupation.maxCreditLevel);
    int res = mysql_query(conn, query);
    if(res)
        FinishWithErrors(conn);

    ocupation.ID = mysql_insert_id(conn);

    printf("Inseridos: %d\n", (int)mysql_affected_rows(conn));
    FinishWithErrors(conn);
    return 1;
}