#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "plateauDeJeu.h"
#include "jeu.h"
#include "bot.h"

#define profMax 6


int main () {
    struct plateau plat;
    InitPlateau(&plat);

    struct plateau tablePlatExplo[profMax];

    afficherPlateau(&plat);

    do
    {
        int choix;
        if (plat.nxtPlayer == 1) //Joueur = humain
        {
            printf("Prochain move: ");
            scanf("%d", &choix);
        }
        else
        {
            choix = analyseBestMove(&plat, tablePlatExplo);
        }
        
        /*
        printf("Prochain move: ");
        scanf("%d", &choix);
        */

        coup(&plat, choix);
        
        plat.nxtPlayer = alternatePlayer(plat.nxtPlayer);

        afficherPlateau(&plat);

    } while (gameFinished(&plat) == 2);
    

    return(0);
}
