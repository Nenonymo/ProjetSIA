#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "plateauDeJeu.h"

int caseCoup(int move)
{
    move = move % 16;
    if (move <= 7) {return move;}
    else {return 23-move;}
}

void afficherPlateau(struct plateau* pPlateau)
{
    for (int i=0; i<2; i++)
    {
        
        for (int j=0; j<8; j++)
        {
            int nI = i*8 + j;
            printf("%d",caseCoup(nI));
            printf("[%d] ", (*pPlateau).grid[caseCoup(nI)]);
        }
        printf("\n");
    }
    printf("Player 1 : %d\nPlayer2 : %d\nNext Plater : %d\n\n", (*pPlateau).seed[0], (*pPlateau).seed[1], (*pPlateau).nxtPlayer);
}

int numJoueur(int move)
{
    if (move <= 7) {return(0);}
    else {return(1);}
}


void coup(struct plateau* pPlateau, int move)
{
    int nbGraines = (*pPlateau).grid[move];
    (*pPlateau).grid[move] = 0;
    do
    {
        move = (move+1) % 16;
        (*pPlateau).grid[move] += 1;
        if (((*pPlateau).grid[move] == 2 || (*pPlateau).grid[move] == 3) && numJoueur(move) != (*pPlateau).nxtPlayer)
        {
            printf("points %d\n", move);
            (*pPlateau).seed[(*pPlateau).nxtPlayer] += (*pPlateau).grid[move];
            (*pPlateau).grid[move] = 0;
        }
        nbGraines--;
    } while (nbGraines > 0);
}

int gameFinished(struct plateau* pPlateau)
{
    if ((*pPlateau).seed[0] + (*pPlateau).seed[1] >= 24)
    {
        if ((*pPlateau).seed[0] >= (*pPlateau).seed[1]) {return 0;}
        else {return 0;}
    }
    else {return 2;}
}

int moveValide(struct plateau* pPlateau, int move)
{
    if (numJoueur(move) == (*pPlateau).nxtPlayer) {return 0;}
    return 1;
}

int alternatePlayer (int nbr)
{
    if (nbr == 1) {return 0;}
    return 1;
}
