#include <stdio.h>
#include "../include/ficha.h"

//Cria a lista de fichas
int CreateSheetList(SheetList *sheetList){
    sheetList->start = NULL;
    sheetList->end = NULL;

    return 1;
}

//Insere na lista de fichas
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
    }

    aux->previous = sheetList->end;
    sheetList->end->next = aux;
    aux->next = sheetList->start;
    sheetList->start->previous = aux;
    sheetList->end = aux;
    if(aux == NULL) return 0;
    return 1;
}

//Mostra a lista de fichas
void ShowSheetList(SheetList sheetList){
    struct NoSheet *aux;
    if(sheetList.start == NULL) {
        printf("EMPTY SHEET LIST\n");
        return;
    }
    aux = sheetList.start;
    do{
        printf("\n--------------------%d--------------------\n", aux->sheet.age);
        printf("Nome Do Jogador: %s\n", aux->sheet.playerName);
        printf("Nome Do Investigador: %s\n", aux->sheet.investigatorName);
        printf("Ocupacao do Investigador: %s\n", aux->sheet.ocupation.name);
        printf("Idade do Investigador: %d\n", aux->sheet.age);
        printf("Sexo do Investigador: %d\n", aux->sheet.sex);
        printf("\n-----------------------------------------\n");
        aux = aux->next;
        getchar();
        scanf("%*c");
    } while (aux != sheetList.start);
}

//Cria uma nova ficha
void CreateSheet(MYSQL *conn, Sheet *sheet, int ocupationID){
    CreateSheetDB(conn);

    sheet->ocupation = GetOcupationByID(conn, ocupationID);

    InsertInSheetDB(conn, sheet);
}

/*
 *
 * DATABASE
 *
 */

//Cria a tabela da ficha no banco
int CreateSheetDB(MYSQL *conn){
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
    if(mysql_query(conn, "CREATE TABLE IF NOT EXISTS sheet(ID int PRIMARY KEY AUTO_INCREMENT, IDTable int NOT NULL, playerName VARCHAR( 150 ) NOT NULL, investigatorName VARCHAR( 150 ) NOT NULL, IDOcupation int NOT NULL, age int NOT NULL, sex int)"))
    {
        FinishWithErrors(conn);
        return 0;
    }

    printf("\nTable sheet created\n");
    FinishWithErrors(conn);
    return 1;
}

//Insere a tabela da ficha no banco
int InsertInSheetDB(MYSQL *conn, Sheet *sheet){
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
    sprintf(query, "INSERT INTO sheet(ID, IDTable, playerName, investigatorName, IDOcupation, age, sex) VALUES(0, %d, '%s', '%s', %d, %d, %d)",
            sheet->idTable, sheet->playerName, sheet->investigatorName, sheet->ocupation.ID, sheet->age, sheet->sex);

    int res = mysql_query(conn, query);

    if(res)
        FinishWithErrors(conn);

    sheet->id = (int)mysql_insert_id(conn);

    printf("Fichas inseridas: %d\n", (int)mysql_affected_rows(conn));
    FinishWithErrors(conn);
    return 1;
}

//Atualiza a tabela da ficha no banco
int SetSheetDB(MYSQL *conn, Sheet sheet){
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
    sprintf(query, "UPDATE sheet SET IDTable = %d, playerName = '%s', investigatorName = '%s', IDOcupation = %d, age = %d, sex = %d WHERE ID = %d",
            sheet.idTable, sheet.playerName, sheet.investigatorName, sheet.ocupation.ID, sheet.age, sheet.sex, sheet.id);

    int res = mysql_query(conn, query);

    if(res)
        FinishWithErrors(conn);

    printf("Atualizados: %d\n", (int)mysql_affected_rows(conn));
    return 1;
}

//Carrega a tabela da ficha no banco
int LoadSheets(MYSQL *conn, SheetList *sheetList, int tableID){
    CreateSheetList(sheetList);
    //Ler os dados do BD e popular a lista
    conn = mysql_init(NULL);
    if (conn == NULL) {
        FinishWithErrors(conn);
        return 1;
    }

    if (mysql_real_connect(conn, SERVER, USERNAME, PASS, DB, 0, NULL, 0) == NULL) {
        FinishWithErrors(conn);
        return 1;
    }
    char query[100];
    sprintf(query, "SELECT * FROM sheet WHERE IDTable = %d", tableID);
    if(mysql_query(conn, query)){
        FinishWithErrors(conn);
        return 1;
    }
    MYSQL_RES *res = mysql_store_result(conn);

    if(!res)//Se nao obtiver dados no retorno
    {
        printf("EMPTY TABLE\n");
        FinishWithErrors(conn);
        return 1;
    }
    //Armazena as colunas da tabela
    MYSQL_ROW row;
    Sheet sheet;

    //Percorre todas as rows retornadas no resultado
    while ((row = mysql_fetch_row(res)))
    {
        sheet.id = atoi(row[0]);
        sheet.idTable = atoi(row[1]);
        strcpy(sheet.playerName, row[2]);
        strcpy(sheet.investigatorName, row[3]);
        sheet.ocupation = GetOcupationByID(conn, atoi(row[4]));
        sheet.age = atoi(row[5]);
        sheet.sex = atoi(row[6]);


        InsertInSheetList(sheetList, sheet);
    }

    mysql_free_result(res);
    FinishWithErrors(conn);
    return 0;
}