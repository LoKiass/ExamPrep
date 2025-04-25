#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct {
    char data[11];
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


int main(void) {
    int nbCaserne = 0;
    Caserne **ppcaserne = NULL;

    do {
        int errorCode = CaserneAlloc(&ppcaserne, &nbCaserne);
        if (errorCode != 0) {
            return 1;
        }
        else { // Allocation Caserne reussis

        }
    }while(1);



    getch();
    return 0;
}

int CaserneAlloc(Caserne ***pppcaserne, int *pNbCaserne) {
    (*pNbCaserne)++;
    // DEBUG // printf("%d\n", *pNbCaserne);
    Caserne ***pppcaserneS = NULL;

    pppcaserneS = pppcaserne;
    *pppcaserne =  realloc(*pppcaserne, (*pNbCaserne) * sizeof(Caserne *));
    if (!(*pppcaserne)) {
        (*pNbCaserne)--;
        pppcaserne = pppcaserneS;
    }

    (*pppcaserne)[*pNbCaserne - 1] = malloc(sizeof(Caserne));
    if (!(*pppcaserne)[*pNbCaserne - 1]) {
        return 2;
    }
}


