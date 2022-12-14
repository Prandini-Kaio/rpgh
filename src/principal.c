#include <stdio.h>
#include "../include/mesa.h"

MYSQL *conn;

TableList tableList;
Table *currentTable;

void CriarMesa();
void EntrarNaMesa();
void NaMesa();
void NaSecao();

void ClearScr();

int inTable = 0;
int inSection = 0;

int main() {
    char op;
    do {
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
                CriarMesa(conn, &tableList, currentTable);
                break;
            case '2':
                EntrarNaMesa(conn, tableList, currentTable);
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
    char nome[100];
    char title[100];
    printf("\n--------------------Criar uma nova mesa--------------------\n");
    getchar();
    printf("                      Qual o nome do mestre                  \n");
    scanf("%[^\n]", nome);
    getchar();
    printf("                      Qual o nome da mesa?                   \n");
    scanf("%[^\n]", title);
    printf("\n-----------------------------------------------------------\n");

    CreateSectionList(&currentTable->sectionList);

    CreateTable(conn, currentTable, nome, title);
    LoadTableList(conn, &tableList);
    ClearScr();
}

void EntrarNaMesa(){
    ClearScr();
    // O ID da mesa em que quero entrar
    LoadTableList(conn, &tableList);
    int mesaID;
    printf("\n-----------------------------------------------------------\n");
    printf("Qual mesa deseja entrar?\n");
    ShowTableList(tableList);
    scanf("%d", &mesaID);
    printf("\n-----------------------------------------------------------\n");
    currentTable = GetTableById(tableList, mesaID);
    //Variavel que define que estamos "Jogando" a mesa
    NaMesa(conn, currentTable);
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
        printf("1 - Alterar Ficha\n2 - Voltar\n");
        scanf("%d", &op);

        switch (op) {
            case 1:
                printf("Alterar Ficha\n");
                break;
            case 2:
                inSection = 0;
                break;
            default:
                printf("Opcao Invalida\n");
        }
    } while (inSection);
}

void ClearScr(void) {
    printf("\033c");
    printf("\033[H\033[J");
}