#ifndef game_h
#define game_h

#include "response_handler.h"

#define NB_SIMULTANEOUS_GAME 3
#define BOARD_SIZE 100

//A faire plus tard
struct game {
    int board[BOARD_SIZE];
};
typedef struct game game;

/*
Structure qui contient :
-une liste de partie.
-le nombre de partie.
-TODO :
    -une liste de joueur.
    -le nombre de joueur.
*/
struct checkers {
    game * games;
    int nb_game;
};
typedef struct checkers checkers;

static checkers * current_checkers;

void * create_account(char * username, char * password);
void test_function(char * response_buffer);

#endif /* game_h */
