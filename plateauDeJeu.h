#ifndef PLATEAU_HEADER
#define PLATEAU_HEADER

typedef struct plateau 
{
    int grid[16];
    unsigned short int nxtPlayer;
    unsigned short int seed[2];
} plateau;

void InitPlateau(struct plateau* pPlateau);

#endif