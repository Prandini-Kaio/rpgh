#ifndef RPG2_SECTION_H
#define RPG2_SECTION_H
/*
 * Section
 *      - Numero da secao
 *      - Nome da secao ?
 *      - Data de abertura da secao
 *      - Anotacoes
 *          - Tipo da anotação
 *          - Anotacao
 * */
typedef struct{
    int index;
    int year, mounth, day, hours, minutes, seconds; //Abertura
}Section;

struct NoSection{
    struct NoSection *next;
    Section section;
    struct NoSection *prev;
};

typedef struct{
    struct NoSection *start;
    struct NoSection *end;
}SectionList;

void CreateSectionList(SectionList *);
int InsertInSectionList(SectionList *, Section);
void ShowSectionList(SectionList);

int CreateSection(Section *, int);

#endif //RPG2_SECTION_H
