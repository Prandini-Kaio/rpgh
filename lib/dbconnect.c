#include <stdio.h>
#include <mysql/mysql.h>
#include <string.h>

#include "../include/dbconnect.h"

//Cria o banco de dados
int CreateDB(MYSQL *conn){


    conn = mysql_init(NULL);
    if (conn == NULL) {
        FinishWithErrors(conn);
        return 0;
    }
    //Faz a conexao real com o banco
    if (mysql_real_connect(conn, SERVER, USERNAME, PASS, DB, 0, NULL, 0) == NULL) {
        FinishWithErrors(conn);
        return 0;
    }
    //Cria o banco caso ele nao exista
    if (mysql_query(conn, "CREATE DATABASE IF NOT EXISTS RPG")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }
    //Fecha a conexao
    mysql_close(conn);
    fprintf(stderr, "%s\n", mysql_error(conn));

    printf("\nDatabase created successfully\n");
    return(0);
}

//Encerra a conexao e mostra os erros caso existam
void FinishWithErrors(MYSQL *conn){

    //A funcao exit da lib mysql, faz com que o programa
    //feche ao terminar a leitura da funcao, opte
    //pelo retorno inteiro
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
}
