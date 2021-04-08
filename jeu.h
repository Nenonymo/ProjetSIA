#ifndef JEU_HEADER
#define JEU_HEADER


void afficherPlateau(struct plateau* pPlateau);

int coupPossibles(struct plateau* pPlateau);

void coup(struct plateau* pPlateau, int move);

int numJoueur(int move);

int gameFinished(struct plateau* pPlateau);

int moveValide(struct plateau* pPlateau, int move);

int alternatePlayer (int nbr);

#endif