#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "plateauDeJeu.h"

int caseCoup(int move)
{
    move = move % 16; //16 cases <- mise en boucle du mouvement (17 = 1)
    if (move <= 7) {return move;} // 8 premierees cases normales
    else {return 23-move;} // 8 derniers cases inversees -> mise en boucle
}

void afficherPlateau(struct plateau* pPlateau)
{
    for (int i=0; i<2; i++) //ligne
    {
        for (int j=0; j<8; j++) //colonne
        {
            //printf("%d[%d] ", caseCoup(i*8+j), (*pPlateau).grid[caseCoup(i*8+j)]); //affiche case et numero
            printf("[%d] ", (*pPlateau).grid[caseCoup(i*8+j)]); //affiche case
        }
        printf("\n");
    }
    printf("Player 1: %d\nPlayer 2: %d\nNext Player: %d\n\n", (*pPlateau).seed[0], (*pPlateau).seed[1], (*pPlateau).nxtPlayer);
}

int numJoueur(int move) //retourne le numéro du jouer associé à la case
{
    if (move <= 7) {return(0);}
    else {return(1);}
}

void coup(struct plateau* pPlateau, int move) //Effectue un coup, modifie la variable prise en entrée
{
    int nbGraines = (*pPlateau).grid[move];
    (*pPlateau).grid[move] = 0;
    do
    {
        move = (move+1) % 16;
        (*pPlateau).grid[move] += 1;
        nbGraines--;
    } while (nbGraines > 0);
    while ((pPlateau->grid[move] == 2 || pPlateau->grid[move] == 2) && numJoueur(move) != pPlateau->nxtPlayer)
    {
        pPlateau->seed[pPlateau->nxtPlayer] += pPlateau->grid[move];
        pPlateau->grid[move] = 0;
        move = (move + 15) % 16;
    }
}

int gameFinished(struct plateau* pPlateau)
{
    if ((*pPlateau).seed[0] + (*pPlateau).seed[1] >= 56)
    {
        if ((*pPlateau).seed[0] >= (*pPlateau).seed[1]) {return 0;}
        else {return 0;}
    }
    else {return 2;}
}

int moveValide(struct plateau* pPlateau, int move)
{
    if (numJoueur(move) == (*pPlateau).nxtPlayer && (*pPlateau).grid[move] != 0) {return 0;}
    return 1;
}

int alternatePlayer (int nbr)
{
    if (nbr == 1) {return 0;}
    return 1;
}
