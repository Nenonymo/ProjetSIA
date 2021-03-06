#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "plateauDeJeu.h"
#include "jeu.h"
#include "bot.h"

#define profMax 20

float tickToSec(clock_t ticks)
{
    return (((float)(ticks)) / CLOCKS_PER_SEC);
}


int main () {
    int profExplo = 12;
    struct plateau plat; //Stockage du plateau de jeu principal
    InitPlateau(&plat); //Initialisation du plateau de jeu
    clock_t t;
    float t_sec;
    int sens;

    struct plateau tablePlatExplo[profMax]; //Creation de la table de stockage des situations en cours d'exploration

    //Demande premier joueur
    int choixFP;
    printf("Qui est le premier joueur ? (0=bot, 1=humain) ");
    scanf("%d", &sens);
    plat.nxtPlayer = sens;


    afficherPlateau(&plat, sens);

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
                    scanf("%d", &choix); //Recuperation du choix

                    choix--;
                    if (sens == 1) {choix = inversionCase(choix);}

                } while(moveValide(&plat, choix) != 0);
                coup(&plat, choix);
            }
        }


        else //Joueur = Bot
        {
            t = clock(); //Temps avant exploration
            choix = analyseBestMove(&plat, tablePlatExplo, profExplo);
            t_sec = tickToSec(clock() - t);
            if (choix == -1) {printf("Je passe mon tour (aucun mouvement possible)...\n");} //Aucun mouvements
            else //Mouvement possible
            {
                if (sens == 1) {printf("Explored %d layers in %.4f seconds, the best move is %d...\n",profExplo, t_sec, inversionCase(choix)+1);} //Affichage des résultats
                else {printf("Explored %d layers in %.4f seconds, the best move is %d...\n",profExplo, t_sec, choix+1);}
                coup(&plat, choix);
            }
            if (t_sec <= 0.3 && profExplo < profMax) {profExplo++;}
            
        }
        

        plat.nxtPlayer = alternatePlayer(plat.nxtPlayer); //Changement du joueur

        afficherPlateau(&plat, sens); //Affichage du plateau après le round joué
        printf("\n\n\n");

    } while (gameFinished(&plat) == 2);

    if (gameFinished(&plat) == 0) {printf("Je vous ai battu de %d points...\n", (plat.seed[0] - plat.seed[1]));}
    else {printf("Félicitation, vous m'avez battu...\n");}


    return(0);
}
