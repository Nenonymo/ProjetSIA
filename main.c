#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "plateauDeJeu.h"
#include "jeu.h"
#include "bot.h"

#define profMax 14


int main () {

    struct plateau plat; //Stockage du plateau de jeu principal
    InitPlateau(&plat); //Initialisation du plateau de jeu
    clock_t t;

    struct plateau tablePlatExplo[profMax]; //Creation de la table de stockage des situations en cours d'exploration

    afficherPlateau(&plat);

    do
    {
        int choix;


        if (plat.nxtPlayer == 1) //Joueur = humain
        {
            //printf("Coups possibles: %d\n", coupPossibles(&plat));
            if (coupPossibles(&plat) == 0) {printf("Vous ne pouvez pas jouer...\n");} 
            else 
            {
                do
                {
                    printf("Prochain move: ");
                    scanf("%d", &choix);
                } while(moveValide(&plat, choix) != 0);
                coup(&plat, choix);
            }
        }


        else //Joueur = Bot
        {
            t = clock(); //Temps avant exploration
            choix = analyseBestMove(&plat, tablePlatExplo);
            t = clock() - t; //Temps apres exploration
            if (choix == -1) {printf("Je passe mon tour (aucun mouvements possibles)...\n");} //Aucun mouvements
            else //Mouvement possible
            {
                printf("Explored %d layers in %.4f seconds, the best move is %d...\n",profMax, (((float)(t)) / CLOCKS_PER_SEC), choix); //Affichage des résultats
                coup(&plat, choix);
            }
            
        }
        

        plat.nxtPlayer = alternatePlayer(plat.nxtPlayer); //Changement du joueur

        afficherPlateau(&plat); //Affichage du plateau après le round joué
        printf("\n\n\n");

    } while (gameFinished(&plat) == 2);

    if (gameFinished(&plat) == 0) {printf("Je vous ai battu de %d points...\n", (plat.seed[0] - plat.seed[1]));}
    else {printf("Félicitation, vous m'avez battu...\n");}


    return(0);
}
