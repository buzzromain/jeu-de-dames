#ifndef game_h
#define game_h

#define NB_COLUMNS 10
#define NB_LINES 10

#include "connector.h"
#include "utils.h"

struct player {
    char * username;
    char * password;
    int nb_win_game;
};
typedef struct player player;

static player * current_player;

struct game {
    char * game_id;
    int ** board;
    int player_side;
};
typedef struct game game;

static game * current_game;

void init_current_game();
void free_current_game();

void init_current_player();
int is_connected_player();
void free_current_player();

void create_new_account();
void disconnect();
void login();

void create_game();
void start_game();
void join_game();

void run_game();
int is_valid_move(int * initial_position, int * new_position);
void print_board(int ** board);

void print_connection_menu();

#endif /* game_h */
