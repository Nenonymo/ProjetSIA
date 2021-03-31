#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "plateauDeJeu.h"
#include "jeu.h"


int main () {
    struct plateau plat;
    InitPlateau(&plat);
    afficherPlateau(&plat);

    do
    {
        int choix;
        printf("Prochain move: ");
        scanf("%d", &choix);
        coup(&plat, choix);
        
        plat.nxtPlayer = alternatePlayer(plat.nxtPlayer);

        afficherPlateau(&plat);

    } while (gameFinished(&plat) == 2);
    

    return(0);
}
