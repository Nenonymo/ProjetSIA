#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "plateauDeJeu.h"
#include "jeu.h"

#define profMax 8

int etatFinal (struct plateau* pPlateau) {return((pPlateau->seed[0]+pPlateau->seed[1]) >= 56);}

int evaluation (struct plateau* pPlateau)
{
    if (etatFinal (pPlateau))
    {
        if (pPlateau->seed[0] > pPlateau->seed[1]) {return 96;}
        else {return -96;}
    }
    else {return(pPlateau->seed[0] - pPlateau->seed[1]);}
}

void nextMove(struct plateau* pPlateau, int move)
{
    coup(pPlateau, move);
    pPlateau->nxtPlayer = alternatePlayer(pPlateau->nxtPlayer);
}


int alphaBeta (struct plateau* pPlateau, struct plateau* tableExplo, signed int alpha, signed int beta,int p) 
{
    if (etatFinal(pPlateau) || p == profMax) {return(evaluation(pPlateau));} //Feuille (par profondeur ou fin de jeu)

    else //Noeud a explorer
    {
        int aB;
        signed int v;
        if (pPlateau->nxtPlayer == 0) //Noeud du bot / max
        {
            v = -16*16;
            for(int i = 0; i < 8; i++) //Moves 1 à 8
            {
                if(pPlateau->grid[i] == 0) {continue;} //Si case vide (mouvement invalide)

                tableExplo[p] = *pPlateau; //Copie du père dans le fils
                nextMove(&(tableExplo[p]), i); //Generation du mouvement
                aB = alphaBeta(&(tableExplo[p]), tableExplo, alpha, beta, p+1); //exploration de l'enfant
                //v = max(aB, v); //Stock maximum de aB et v dans v
                if (aB > v) {v = aB;} //Plus optimisé que v = max(aB, v), (attribution non nécéssaire)
                if (v >= beta) {return(v);} //Coupe beta
                //alpha = max(alpha, v); //Nouvelle valeur de la coupe alpha (v = max(a, v))
                if (v > alpha) {alpha = v;} //
            }
        } 

        else //Noeud du joueur / min
        {
            v = 16*16;
            for(int i = 8; i < 16; i++)
            {
                if(pPlateau->grid[i] == 0) {continue;}

                tableExplo[p] = *pPlateau;
                nextMove(&(tableExplo[p]), i);
                aB = alphaBeta(&(tableExplo[p]), tableExplo, alpha, beta, p+1);
                //v = min(aB, v); //Stock max de aB et de v dans v
                if (v > aB) {v = aB;} //Min de aB et v dans B
                if (alpha >= v) {return(v);}
                //beta = min(beta, v);
                if (beta > v) {beta = v;} //beta = min(v, beta)
            }
        }
        return(v);
    }
}


int analyseBestMove(struct plateau* pPlateau, struct plateau* tableExplo)
{
    if (coupPossibles(pPlateau) == 0) {return(-1);} //Si aucun coup possibles
    int score[8];
    for (int i = 0; i < 8; i++)
    {
        if (pPlateau->grid[i] == 0) {score[i] = -100; continue;} //Score le plus petit = -96
        tableExplo[0] = *pPlateau;
        nextMove(&(tableExplo[0]), i);
        score[i] = alphaBeta(&(tableExplo[0]), tableExplo, -16*16, 16*16, 1);
    }


    //Calcul du score maximum
    int maxI = 0;
    for (int i = 1; i < 8; i++)
    {
        if (score[maxI] < score[i]) {maxI = i;}
    }


    //Si tout les scores sont à Zero
    if (score[maxI] == 0) 
    {
        srand(time(NULL));
        maxI = rand() % 8;
    }
    return(maxI);
}

