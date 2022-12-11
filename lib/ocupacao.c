#include "../include/ocupacao.h"

int CreateOcupation(ocupation *ocupation,enum ocp ocupationE, int creditLvl, int ocupationPoints){
    ocupation->ocupation = ocupationE;
    ocupation->creditLevel = creditLvl;
    ocupation->ocupationalPoints = ocupationPoints;
    return 1;
}