#include <stdlib.h>



typedef struct plateau 
{
    int grid[16];
    int nxtPlayer;
    int seed[2];
} plateau;

void InitPlateau(struct plateau* pPlateau)
{
    for(int i = 0; i < 16; i++) {(*pPlateau).grid[i] = 4;}
    (*pPlateau).nxtPlayer = 0;
    for(int i = 0; i<2; i++) {(*pPlateau).seed[i] = 0;}
}