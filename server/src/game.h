#ifndef game_h
#define game_h

#include "response_handler.h"
#include "db.h"

#define SIMULTANEOUS_GAME 3
#define MAX_USER 10
#define NB_LINES 10
#define NB_COLUMNS 10

struct player {
    char * user_id;
    char * username;
    char * password;
    int nb_won_game;
};
typedef struct player player;

//Structure de données representant une partie
struct game {
    char * game_id; //Identifiant de la partie.
    int ** board; //Plateau de jeu
    player * first_player; //Pointeur sur le premier joueur
    player * second_player; //Pointeur sur le second joueur
    int must_play; //Le numéro du joueur qui doit jouer
};
typedef struct game game;

//Variable globale au fichier.
static player ** connected_players;
static int nb_connected_players;

static game ** active_games;
static int nb_active_games;

void init_connected_player();
void * get_connected_player(char * username, char * password);
int add_connected_player(db_user * user);
int remove_connected_player(player * current_player);
int is_connected_player(char * username);

void * get_game_by_id(char * game_id);

void init_active_games();
int ** create_new_board();
void * join_game(char * username, char * password);
void * create_game(char * username, char * password);
void * start_game(char * username, char * password, char * game_id);
void * create_account(char * username, char * password);
void * login(char * username, char * password);
void * disconnect(char * username, char * password);
int is_valid_move(int ** board, int must_play, int player_side, int * initial_position, int * new_position);
void * move_game(char * username, char * password, char * game_id, int * initial_position, int * new_position);
void * get_last_game_update(char * game_id);
void init_game();

#endif /* game_h */
