#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct {
    char date[11];
    int nbAmb;
    int nbInc;
    int nbDec;
    int nbInterv; // Fonction STAT
}Intervention;

typedef struct {
    char id[10];
    char location[10];
    int nbAff;
    int nbInterv;
    int nbjrsInterv;
    Intervention **ppTinterv;
}Caserne;

int CaserneAlloc(Caserne ***pppCaserne, int *pNbCaserne);
int IntervAlloc(Intervention ***pppInterv, int *pNbInterv);
void CaserneAquisition(Caserne *pcasern);
void IntervAquisition(Intervention *pInterv);
void AffichageInformation(Caserne **pCaserne, int nombreCaserne);
void StatGlobale(Caserne **ppCasernen);
void FreeMemory(Caserne **ppCaserneLib, int nbCaserneLib);

int main(void) {
    char encoCaserne, encoInterv;
    int nbCaserne = 0;
    Caserne **ppcaserne = NULL;

    do {
        // DEBUG // printf("\n! REALLOC CASERNE");
        int errorCode = CaserneAlloc(&ppcaserne, &nbCaserne); // Allocation Caserne
        ppcaserne[nbCaserne - 1]->nbInterv = 0;
        CaserneAquisition(ppcaserne[nbCaserne - 1]);  // Aquissitons Caserne information
        // DEBUG // printf("%s", ppcaserne[nbCaserne - 1]->id);
        if (errorCode != 0) {
            return errorCode;
        }
        else { // Allocation Caserne reussis
            // DEBUG // printf("\n!! REALLOC CASERRNE REUSSIS");
            ppcaserne[nbCaserne - 1]->ppTinterv = NULL;
            do {
                // DEBUG // printf("\n! REALLOC INTERV");
                int errorCode = IntervAlloc(&ppcaserne[nbCaserne - 1]->ppTinterv, &ppcaserne[nbCaserne-1]->nbInterv);
                if (errorCode != 0) {
                    return errorCode;
                }
                else {
                    IntervAquisition(ppcaserne[nbCaserne - 1]->ppTinterv[ppcaserne[nbCaserne-1]->nbInterv - 1]); //
                    // DEBUG // ("%s", ppcaserne[nbCaserne - 1]->ppTinterv[ppcaserne[nbCaserne-1]->nbInterv - 1]->date);
                    printf("\nEncore une intervention ? :");
                    encoInterv = getche();

                }
            }while (encoInterv =='y' || encoInterv == 'Y');
        }
        printf("\nEncore Caserne ? : ");
        encoCaserne = getche();
    }while(encoCaserne == 'y' || encoCaserne == 'Y');

    AffichageInformation(ppcaserne, nbCaserne);
    FreeMemory(ppcaserne, nbCaserne);
    getch();
    return 0;
}

int CaserneAlloc(Caserne ***pppcaserne, int *pNbCaserne) {
    (*pNbCaserne)++;
    Caserne **ppcaserneS = *pppcaserne;

    *pppcaserne = (Caserne **) realloc(*pppcaserne, (*pNbCaserne) * sizeof(Caserne *));
    if (!(*pppcaserne)) {
        (*pNbCaserne)--;
        *pppcaserne = ppcaserneS;
        return -1;
    }

    (*pppcaserne)[*pNbCaserne - 1] = (Caserne *) malloc(sizeof(Caserne));
    if (!(*pppcaserne)[*pNbCaserne - 1]) {
        return -2;
    }

    return 0;
}

int IntervAlloc(Intervention ***pppInterv, int *pNbInterv) {
    (*pNbInterv)++;
    *pppInterv = (Intervention **) realloc(*pppInterv, (*pNbInterv) * sizeof(Intervention *));
    if (!(*pppInterv)) {
        return -3;
    }
    (*pppInterv)[*pNbInterv - 1] = (Intervention * ) malloc(sizeof(Intervention));
    if (!(*pppInterv)[*pNbInterv - 1]) {
        return -4;
    }
    return 0;
}

void CaserneAquisition(Caserne *pcasern) {
    printf("\nID Caserne");
    gets(pcasern->id);
    printf("\nLocation Caserne");
    gets(pcasern->location);
}
// REVOIR + REFAIRE BOUCLE AFFICHAGE
void IntervAquisition(Intervention *pInterv) {
    printf("\nDate intervention");
    gets(pInterv->date);
    printf("\nNombre intervention AMB : ");
    scanf("%d", &pInterv->nbAmb); getchar();
    printf("\nNombre intervention INC : ");
    scanf("%d", &pInterv->nbInc); getchar();
    printf("\nNombre intervention DEC : ");
    scanf("%d", &pInterv->nbDec); getchar();
}


void AffichageInformation(Caserne **ppCasern, int nombreCaserne) {
    system("cls");
    for (int z = 0; z < nombreCaserne; z++) {
        printf("\n--- Caserne %d ---", z + 1);
        printf("\nID Caserne : %s", ppCasern[z]->id);
        printf("\nLocation Caserne : %s", ppCasern[z]->location);

        for (int i = 0; i < ppCasern[z]->nbInterv; i++) {
            printf("\n  > Intervention %d :", i + 1);
            printf("\n    Date : %s", ppCasern[z]->ppTinterv[i]->date);
            printf("\n    Nombre AMB : %d", ppCasern[z]->ppTinterv[i]->nbAmb);
            printf("\n    Nombre INC : %d", ppCasern[z]->ppTinterv[i]->nbInc);
            printf("\n    Nombre DEC : %d", ppCasern[z]->ppTinterv[i]->nbDec);
        }
    }
    getch();
}

void FreeMemory(Caserne **ppCaserneLib, int nbCaserneLib) {
    for (int y = 0; y < nbCaserneLib; y++) {
        for (int x = 0; x < ppCaserneLib[y]->nbInterv; x++) {
            free(ppCaserneLib[y]->ppTinterv[x]);
        }
        free(ppCaserneLib[y]->ppTinterv);
        free(ppCaserneLib[y]);
    }
    free(ppCaserneLib);
}

