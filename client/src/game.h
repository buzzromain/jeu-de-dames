#ifndef game_h
#define game_h

#define NB_COLUMNS 10
#define NB_LINES 10

#include "connector.h"

/**
* Structure de données (incomplete) representant le plateau
* de jeu.
*/
struct game {
    int ** board;
};
typedef struct game game;

static game * current_game;

void create_new_account();
void run_game();
void init_game();

#endif /* game_h */
