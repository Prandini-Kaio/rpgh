#ifndef RPG2_OCUPACAO_H
#define RPG2_OCUPACAO_H
enum ocp{
    Antiquario, Artista, Jornalista, Missionario
}ocp;

typedef struct{
    enum ocp ocupation;
    //Lista De Pericias permitidas
    int creditLevel;
    int ocupationalPoints;
}ocupation;

int CreateOcupation(ocupation *ocupation, enum ocp, int credit, int ocupationPoints);
#endif //RPG2_OCUPACAO_H
