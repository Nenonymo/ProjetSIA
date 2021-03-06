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

int coupPossibles(struct plateau* pPlateau)
{
    int nbMP = 0; //nombre Mouvements Possibles
    if (pPlateau->nxtPlayer == 0)
    {
        for (int i =0; i < 8; i++)
        {
            if (pPlateau->grid[i] != 0) {nbMP++;}
        }
    }
    else if (pPlateau->nxtPlayer == 1)
    {
        for (int i =8; i < 16; i++)
        {
            if (pPlateau->grid[i] != 0) {nbMP++;}
        }
    }
    return(nbMP);
}

int inversionCase(int i) 
{
    int case_[] = {8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8};
    return(case_[i]);
}

void afficherPlateau(struct plateau* pPlateau, int sens)
{
    char addr_[2];
    for (int i=0; i<2; i++) //ligne
    {
        for (int j=0; j<8; j++) //colonne
        {
            //printf("%d[%d] ", caseCoup(i*8+j), (*pPlateau).grid[caseCoup(i*8+j)]); //affiche case et numero

            int case_ = caseCoup(i*8 + j);
            int case__ = case_;
            if (sens == 1) {case__ = inversionCase(case_);}


            printf("\t%d [%d]", (case_ + 1), (*pPlateau).grid[case__]); //affiche case
        }
        printf("\n");
    }
    printf("Bot: %d\nPlayer: %d\nNext Player: %d\n\n", (*pPlateau).seed[0], (*pPlateau).seed[1], ((*pPlateau).nxtPlayer + 1));
}

int numJoueur(int move) //retourne le numéro du jouer associé à la case
{
    if (move <= 7) {return(0);}
    else {return(1);}
}

void coup(struct plateau* pPlateau, int move) //Effectue un coup, modifie la variable prise en entrée
{
    int nbGraines = (*pPlateau).grid[move]; //Calcul du nombre de graines à distribuer
    (*pPlateau).grid[move] = 0; //Vidage de la case
    if (nbGraines != 0)
    {
        do //Repartition des graines
        {
            move = (move+1) % 16;
            (*pPlateau).grid[move] += 1;
            nbGraines--;
        } while (nbGraines > 0);
        while ((pPlateau->grid[move] == 2 || pPlateau->grid[move] == 3) && numJoueur(move) != pPlateau->nxtPlayer) //Capture des graines
        {
            pPlateau->seed[pPlateau->nxtPlayer] += pPlateau->grid[move];
            pPlateau->grid[move] = 0;
            move = (move + 15) % 16;
        }
    }
}

int gameFinished(struct plateau* pPlateau) //Statut de partie
{
    /* Signaux:
        0 Si Le gagnant est le bot
        1 si le gagnant est le joueur
        2 si la partie n'est pas finie
    */
    if ((*pPlateau).seed[0] + (*pPlateau).seed[1] >= 56)
    {
        if ((*pPlateau).seed[0] > (*pPlateau).seed[1]) {return 0;}
        else {return 1;}
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
