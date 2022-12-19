#ifndef RPG2_OCUPACAO_H
#define RPG2_OCUPACAO_H
#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include "dbconnect.h"
typedef struct {
    int ID;
    char name[100];
    int minCreditLevel;
    int maxCreditLevel;
}Ocupation;

struct NoOcupation{
    struct NoOcupation *next;
    Ocupation ocupation;
    struct NoOcupation *prev;
};

typedef struct {
    struct NoOcupation *start;
    struct NoOcupation *end;
}OcupationList;

void CreateOcupationList(OcupationList *ocupationList);
int InsertInOcupationList(OcupationList *ocupationList, Ocupation ocupation);
void ShowOcupationList(OcupationList ocupationList);

Ocupation GetOcupationByID(MYSQL *, int);

int LoadOcupation(MYSQL *connection, OcupationList *ocupationList);
int CreateOcupationDB(MYSQL *connection);
#endif //RPG2_OCUPACAO_H
