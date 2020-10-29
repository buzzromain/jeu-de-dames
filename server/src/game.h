#ifndef game_h
#define game_h

#include "response_handler.h"

#define NB_SIMULTANEOUS_GAME 3
#define NB_LINES 10
#define NB_COLUMNS 10

//Pour la démo, structure de données simple (à completer plus tard).
struct game {
    int ** board;
};
typedef struct game game;

//Variable globale au fichier.
static game * current_game;

/*
Structure qui contient :
-une liste de partie.
-le nombre de partie.
-TODO :
    -une liste de joueur.
    -le nombre de joueur.

struct checkers {
    game * games;
    int nb_game;
};
typedef struct checkers checkers;

static checkers * current_checkers;
*/

void init_board();
void * start_game(char * username, char * password, char * game_id);
void * create_account(char * username, char * password);
void init_game();

#endif /* game_h */
