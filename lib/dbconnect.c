#include <stdio.h>
#include <mysql/mysql.h>
#include <string.h>

#include "../include/dbconnect.h"
int CreateDB(MYSQL *conn){

    conn = mysql_init(NULL);
    if (conn == NULL) {
        FinishWithErrors(conn);
        return 0;
    }

    if (mysql_real_connect(conn, SERVER, USERNAME, PASS, DB, 0, NULL, 0) == NULL) {
        FinishWithErrors(conn);
        return 0;
    }

    if (mysql_query(conn, "CREATE DATABASE IF NOT EXISTS RPG")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    mysql_close(conn);
    fprintf(stderr, "%s\n", mysql_error(conn));

    printf("\nDatabase created successfully\n");
    return(0);
}

void FinishWithErrors(MYSQL *conn){

    //A funcao exit da lib mysql, faz com que o programa
    //feche ao terminar a leitura da funcao, opte
    //pelo retorno inteiro
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
}
