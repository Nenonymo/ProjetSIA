#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "plateauDeJeu.h"
#include "jeu.h"

#define profMax 6

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

int max(int a, int b)
{
    if (a < b) {return(a);}
    else {return(b);}
}

int min(int a, int b)
{
    if (a > b) {return(a);}
    else {return(b);}
}

int alphaBeta (struct plateau* pPlateau, struct plateau* tableExplo, signed int alpha, signed int beta, int numJoueur, int p) 
{
    if (etatFinal(pPlateau) || p == profMax) {return(evaluation(pPlateau));} //Feuille (par profondeur ou fin de jeu)

    else //Noeud a explorer
    {
        signed int v;
        if (numJoueur == 0) //Noeud du bot / max
        {
            v = -2^6;
            for(int i = 0; i < 8; i++) //Moves 1 à 8
            {
                if(pPlateau->grid[i] == 0) {continue;} //Si case vide (mouvement invalide)

                tableExplo[p] = *pPlateau; //Copie du père dans le fils
                nextMove(&(tableExplo[p]), i); //Generation du mouvement
                int aB = alphaBeta(&(tableExplo[p]), tableExplo, alpha, beta, alternatePlayer(numJoueur), p+1); //exploration de l'enfant
                v = max(aB, v); //Stock minimum de aB et v dans v
                if (v >= beta) {return(v);} //Coupe beta
                alpha = max(alpha, v); //Nouvelle valeur de la coupe alpha (v = max(a, v))
            }
        } 

        else //Noeud du joueur / min
        {
            v = 2^6;
            for(int i = 8; i < 16; i++)
            {
                if(pPlateau->grid[i] == 0) {continue;}

                tableExplo[p] = *pPlateau;
                nextMove(&(tableExplo[p]), i);
                int aB = alphaBeta(&(tableExplo[p]), tableExplo, alpha, beta, alternatePlayer(numJoueur), p+1);
                v = min(aB, v); //Stock max de aB et de v dans v
                if (alpha >= v) {return(v);}
                beta = min(beta, v);
            }
        }
        return(v);
    }
}


int analyseBestMove(struct plateau* pPlateau, struct plateau* tableExplo)
{
    int score[8];
    for (int i = 0; i < 8; i++)
    {
        if (pPlateau->grid[i] == 0) {score[i] = -1; continue;}
        tableExplo[0] = *pPlateau;
        nextMove(&(tableExplo[0]), i);
        tableExplo[0].nxtPlayer = alternatePlayer(tableExplo[0].nxtPlayer);
        score[i] = alphaBeta(&(tableExplo[0]), tableExplo, -2^6, 2^6, 0, 1);
        printf("Score %d: %d\n", i, score[i]);
    }


    int maxI = 0;
    for (int i = 1; i < 8; i++)
    {
        if (score[maxI] < score[i]) {maxI = i;}
    }

    if (score[maxI] == 0)
    {
        srand(time(NULL));
        maxI = rand() % 8;
        printf("Choix aléatoire: %d\n", maxI);
        return(maxI);
    }
    else
    {
        printf("Best move : %d with %d\n", maxI, score[maxI]);
        return(maxI);
    }
}




