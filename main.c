#include <stdio.h>
#include "headers/mesa.h"

TableList tableList;
Table currentTable;

int inTable = 0;

void CriarMesa();
void EntrarNaMesa();
void NaMesa();
void ClearScr();

int main() {
    char op;
    CreateTableList(&tableList);

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
    char nome[50];
    char title[50];
    printf("--------------------Criar uma nova mesa--------------------");
    getchar();
    printf("\nQual o nome do mestre?\n");
    scanf("%[^\n]", &nome);
    getchar();
    printf("\nQual o nome da mesa?\n");
    scanf("%[^\n]", &title);
    printf("-----------------------------------------------------------");
    Table tb;

    SectionList sectionList;
    CreateSectionList(&sectionList);

    int succesCreate = CreateTable(&tb, sectionList, nome, title, 0);
    if(succesCreate){
        succesCreate = InsertInTableList(&tableList, tb);
        if(succesCreate) printf("\nSucesso ao criar a mesa\n");
        else printf("Falha ao criar Table\n");
    }
    ClearScr();
}

void EntrarNaMesa(){
    ClearScr();
    int mesaID;
    printf("\n-----------------------------------------------------------\n");
    printf("Qual mesa deseja entrar?\n");
    ShowTableList(tableList);
    scanf("%d", &mesaID);
    printf("\n-----------------------------------------------------------\n");
    currentTable = GetTableById(tableList, mesaID);
    inTable = 1;
    NaMesa();
}

void NaMesa(){
    ClearScr();
    int op, i = 0;
    Section section;
    do{
        printf("\n\n-----------------------------------------------------------\n\n");
        printf("\nBem vindo %s - %s\n", currentTable.masterName, currentTable.title);
        printf("\nO que deseja fazer?\n"
               "1 - Iniciar uma nova secao\n2 - Sair da mesa\n");
        scanf("%d", &op);
        printf("\n\n-----------------------------------------------------------\n\n");

        switch (op) {
            case 1:
                CreateSection(&section, i);
                i++;
                int succes = InsertInSectionList(&currentTable.sectionList, section);
                if(succes) printf("Sucesso em abrir secao");
                //ShowSectionList(currentTable.sectionList);
                ClearScr();
                break;
            case 2:
                inTable = 0;
                break;
            default:
                printf("Opcao invalida");
                break;
        }
        ShowSectionList(currentTable.sectionList);
    } while (inTable);
}

void ClearScr(void) {
    printf("\033c");
    printf("\033[H\033[J");
    return;
}