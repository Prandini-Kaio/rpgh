#include <malloc.h>
#include <time.h>
#include "stdio.h"
#include "../headers/section.h"

void CreateSectionList(SectionList *sectionList){
    sectionList->start = NULL;
    sectionList->end = NULL;
}

int InsertInSectionList(SectionList *sectionList, Section section){
    struct NoSection *aux;
    aux = (struct NoSection *)malloc(sizeof(struct NoSection));
    aux->section = section;
    if(sectionList->start == NULL){

        sectionList->start = aux;
        sectionList->end = aux;
        aux->next = sectionList->start;
        aux->prev = sectionList->end;
        return 1;
    }

    aux->prev = sectionList->end;
    sectionList->end->next = aux;
    aux->next = sectionList->start;
    sectionList->start->prev = aux;
    sectionList->end = aux;
    if(aux == NULL) return 0;
    return 1;
}

void ShowSectionList(SectionList sectionList){
    struct NoSection *aux;
    if(sectionList.start == NULL) printf("LISTA VAZIA");
    aux = sectionList.start;

    do {
        printf("\n--------------------SECTION %d--------------------\n", aux->section.index);
        printf("Open In: %d / %d / %d. %d:%d:%d \n",
               aux->section.day,aux->section.mounth,
               aux->section.year,aux->section.hours,
               aux->section.minutes, aux->section.seconds);
        printf("\n--------------------------------------------------\n");
        aux = aux->next;
    } while (aux != sectionList.start);
}

int CreateSection(Section *section, int lastIndex){

    time_t t = time(NULL);

    section->index = lastIndex + 1;

    section->year = localtime(&t)->tm_year + 1900;
    section->mounth = localtime(&t)->tm_mon + 1;
    section->day = localtime(&t)->tm_mday;

    section->hours = localtime(&t)->tm_hour;
    section->minutes = localtime(&t)->tm_min;
    section->seconds = localtime(&t)->tm_sec;

    return 1;
}