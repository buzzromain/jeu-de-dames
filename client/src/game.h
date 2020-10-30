#ifndef game_h
#define game_h

#define NB_COLUMNS 10
#define NB_LINES 10

#include "connector.h"

struct user {
    char * username;
    char * password;
    //D'autres données sur l'utilisateur peuvent être ajouter ici (nombre de parties gagnés, ...)
};
typedef struct user user;

static user * current_user;
/**
* Structure de données (incomplete) representant le plateau
* de jeu.
*/
struct game {
    int ** board;
};
typedef struct game game;

static game * current_game;

void print_board(int ** board);
void create_new_account();
void disconnect();
void run_game();
void init_game();
int * parse_position(char * stringify_position);
int ** get_positions_by_parsing_user_input(char * user_input);
int is_valid_move(int * initial_position, int * new_position);

#endif /* game_h */
