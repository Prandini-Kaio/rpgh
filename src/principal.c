#include <stdio.h>
#include "../include/mesa.h"

MYSQL *conn;

TableList tableList;
Table currentTable;

OcupationList ocupationList;

void CriarMesa();
void EntrarNaMesa();
void NaMesa();

void NaSecao();

void CriarFicha();
void AlterarFicha();

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

    CreateTable(conn, &currentTable, nome, title);
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
    NaMesa();
}

void NaMesa(){
    ClearScr();
    int op;
    Section section;

    inTable = 1;

    do{
        LoadSectionList(conn, &currentTable.sectionList, currentTable.id);
        printf("\n\n-----------------------------------------------------------\n\n");
        printf("\nBem vindo %s - %s\n", currentTable.masterName, currentTable.title);
        printf("\nO que deseja fazer?\n"
               "1 - Iniciar uma secao\n2 - Ver secoes\n3 - Voltar\n");
        scanf("%d", &op);
        printf("\n\n-----------------------------------------------------------\n\n");
        ClearScr();
        switch (op) {
            case 1:
                CreateSection(conn, &section, currentTable.id);
                LoadSectionList(conn, &currentTable.sectionList, currentTable.id);
                ShowSection(currentTable.sectionList, section.id);
                getchar();
                scanf("%*c");
                NaSecao();
                CloseSection(conn, &section);
                ClearScr();
                break;
            case 2:
                LoadSectionList(conn, &currentTable.sectionList, currentTable.id);
                ShowSectionList(currentTable.sectionList);
                printf("\nPressione qualquer tecla...\n");
                getchar();
                scanf("%*c");
                ClearScr();
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

    inSection = 1;

    do{
        ClearScr();
        printf("\nSecao aberta.. Aproveite!!\n");
        printf("\n1 - Criar Ficha\n2 - Alterar Ficha\n3 - Sair\n");
        scanf("%d", &op);

        switch (op) {
            case 1:
                //Criar nova ficha
                CriarFicha();
                break;
            case 2:
                AlterarFicha();
                break;
            case 3:
                inSection = 0;
                break;
            default:
                printf("Opcao Invalida\n");
        }
    } while (inSection);
}

void CriarFicha(){
    //Auxiliar
    Sheet sheet;
    int ocpID;

    LoadOcupation(conn, &ocupationList);

    printf("\n----------/----------\n");
    printf("\nQual o nome do jogador?\n");
    scanf("%s", sheet.playerName);
    printf("\nQual o nome do investigador?\n");
    scanf("%s", sheet.investigatorName);
    printf("\nQual a idade do investigador?\n");
    scanf("%d", &sheet.age);
    printf("\nQual o sexo do investigador?(1 - Masculino 2 - Feminino)\n");
    scanf("%d", &sheet.sex);
    printf("\nQual a ocupacao do investigador?\n");
    ShowOcupationList(ocupationList);
    scanf("%d", &ocpID);
    printf("\n----------/----------\n");

    sheet.idTable = currentTable.id;
    CreateSheet(conn, &sheet, ocpID);
    LoadSheets(conn, &currentTable.sheetList, currentTable.id);
    ShowSheetList(currentTable.sheetList);

    printf("\n\nPressione qualquer tecla para continuar\n\n");
    getchar();
    scanf("%*c");
}

void AlterarFicha(){
    //Auxiliar
    Sheet sheet;
    int ocpID;

    LoadOcupation(conn, &ocupationList);

    printf("\n----------/----------\n");
    printf("\nQual o nome do jogador?\n");
    scanf("%s", sheet.playerName);
    printf("\nQual o nome do investigador?\n");
    scanf("%s", sheet.investigatorName);
    printf("\nQual a idade do investigador?\n");
    scanf("%d", &sheet.age);
    printf("\nQual o sexo do investigador?(1 - Masculino 2 - Feminino)\n");
    scanf("%d", &sheet.sex);
    printf("\nQual a ocupacao do investigador?\n");
    ShowOcupationList(ocupationList);
    scanf("%d", &ocpID);
    printf("\n----------/----------\n");

    sheet.idTable = currentTable.id;
    SetSheetDB(conn, sheet);
    LoadSheets(conn, &currentTable.sheetList, currentTable.id);
    ShowSheetList(currentTable.sheetList);
    getchar();
    scanf("%*c");
}

void ClearScr(void) {
    printf("\033c");
    printf("\033[H\033[J");
}