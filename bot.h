#ifndef BOT_HEADER
#define BOT_HEADER

int etatFinal (struct plateau* pPlateau);

int evaluation (struct plateau* pPlateau);

void nextMove (struct plateau* pPlateau, int move);

int alphaBeta (struct plateau* pPlateau, struct plateau* tableExplo, signed int alpha, signed int beta, int numJoueur, int p);

int analyseBestMove (struct plateau* pPlateau, struct plateau* tableExplo);
#endif