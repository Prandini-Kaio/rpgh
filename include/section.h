#ifndef RPG2_SECTION_H
#define RPG2_SECTION_H
#include <mysql/mysql.h>
#include "time.h"
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
    int id;
    int numberSec;
    int idTable;
    int idAnotation;
    char openDate[50];
    char closeDate[50];
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

//List
void CreateSectionList(SectionList *);
int InsertInSectionList(SectionList *, Section);
void ShowSectionList(SectionList);

//Section
int CreateSection(MYSQL *, Section *, int);

//Database
int CreateSectionDB(MYSQL *conn);
int InsertSectionDB(MYSQL *conn, Section *section);
int GetSection(MYSQL *);
int SetSection(MYSQL *, Section);

int GetLastSectionID(MYSQL *, int tableID);
int PopulateSectionList(MYSQL *, SectionList *, int);
#endif //RPG2_SECTION_H
