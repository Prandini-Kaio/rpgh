#include <stdio.h>
#include <mysql/mysql.h>
#include "../include/mesa.h"
#ifdef HAVE_SQL
#include "hellosql.h"
#endif

TableList tableList;
Table *currentTable;

MYSQL *conn;

int inTable = 0;
int inSection = 0;

void CriarMesa();
void EntrarNaMesa();
void NaMesa();
void NaSecao();

void ClearScr();

int main() {
    char op;
    CreateTableList(&tableList);

    PopulateTableList(conn, &tableList);

    do {
        ClearScr();
        printf("\nBem vindo\n");
        getchar();
        printf("O que deseja fazer?\n"
               "1 - Criar uma nova mesa\n"
               "2 - Entrar em uma mesa\n"
               "3 - Sair\n");
        scanf("%c", &op);
        switch (op) {
            case '1':
                fflush(stdin);
                CriarMesa();
                break;
            case '2':
                EntrarNaMesa();
                break;
            case '3':
                printf("Finalizando...\n");
                break;
            default:
                printf("Opcao Invalida!\n");
                break;
        }
    } while (op != '3');

    return 0;
}

void CriarMesa(){
    ClearScr();
    char *nome[100];
    char title[100];
    printf("\n--------------------Criar uma nova mesa--------------------\n");
    getchar();
    printf("                      Qual o nome do mestre                  \n");
    scanf("%[^\n]", &nome);
    getchar();
    printf("                      Qual o nome da mesa?                   \n");
    scanf("%[^\n]", &title);
    printf("\n-----------------------------------------------------------\n");

    Table tb;

    SectionList sectionList;
    CreateSectionList(&sectionList);

    CreateTable(conn, &tb, nome, title, 0);
    PopulateTableList(conn, &tableList);
    ClearScr();
}

void EntrarNaMesa(){
    ClearScr();
    // O ID da mesa em que quero entrar
    int mesaID;
    printf("\n-----------------------------------------------------------\n");
    printf("Qual mesa deseja entrar?\n");
    ShowTableList(tableList);
    scanf("%d", &mesaID);
    printf("\n-----------------------------------------------------------\n");
    currentTable = GetTableById(tableList, mesaID);
    //Variavel que define que estamos "Jogando" a mesa
    inTable = 1;
    NaMesa();
}

void NaMesa(){
    ClearScr();
    int op;
    Section section;
    do{
        PopulateSectionList(conn, &currentTable->sectionList, currentTable->id);
        printf("\n\n-----------------------------------------------------------\n\n");
        printf("\nBem vindo %s - %s\n", currentTable->masterName, currentTable->title);
        printf("\nO que deseja fazer?\n"
               "1 - Iniciar uma nova secao\n2 - Ver secoes\n3 - Voltar\n");
        scanf("%d", &op);
        printf("\n\n-----------------------------------------------------------\n\n");

        switch (op) {
            case 1:
                CreateSection(conn, &section, currentTable->id);
                PopulateSectionList(conn, &currentTable->sectionList, currentTable->id);
                inSection = 1;
                NaSecao();
                ClearScr();
                break;
            case 2:
                PopulateSectionList(conn, &currentTable->sectionList, currentTable->id);
                ShowSectionList(currentTable->sectionList);
                break;
            case 3:
                inTable = 0;
                break;
            default:
                printf("Opcao invalida");
                break;
        }
    } while (inTable);
}

void NaSecao(){
    ClearScr();
    int op;
    printf("\nSecao aberta\n");
    do{
        printf("1 - Alterar Ficha\n");
        scanf("%d", &op);

        switch (op) {
            case 1:
                printf("Alterar Ficha\n");
                break;
            case 2:
                inSection = 0;
                break;
        }
    } while (inSection);
}

void ClearScr(void) {
    printf("\033c");
    printf("\033[H\033[J");
    return;
}

#ifdef HAVE_SQL
helloSQL();
#endif