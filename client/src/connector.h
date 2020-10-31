#ifndef connector_h
#define connector_h
#include "client.h"
#include "connector_utils.h"
/* 
    Structure des réponses
*/
struct mes_account_type1 {
    char * message_type;
    char * code;
};
typedef struct mes_account_type1 mes_create_account;
typedef struct mes_account_type1 mes_delete_account;
typedef struct mes_account_type1 mes_disconnect;

struct mes_account_type2 {
    char * message_type;
    char * code;
    int nb_win_game;
};
typedef struct mes_account_type2 mes_login;

struct mes_game_type1 {
    char * message_type;
    char * code;
};
typedef struct mes_game_type1 mes_quit_game;
typedef struct mes_game_type1 mes_delete_game;

struct mes_game_type2 {
    char * message_type;
    char * code;
    char * game_id;
    int ** board;
};
typedef struct mes_game_type2 mes_join_game;

struct mes_game_type3 {
    char * message_type;
    char * code;
    int ** board;
};
typedef struct mes_game_type3 mes_get_last_game_update;
typedef struct mes_game_type3 mes_view_game;
typedef struct mes_game_type3 mes_move_game;

struct mes_game_type4 {
    char * message_type;
    char * code;
    int * active_games_id;
};
typedef struct mes_game_type4 mes_list_game;

struct mes_game_type5 {
    char * message_type;
    char * code;
    char * game_id;
    int player_side;
    int ** board;
};
typedef struct mes_game_type5 mes_create_game;

/*
    Fonctions utilitaires (à changer de fichier plus tard)
*/
int ** parse_stringify_board(char * stringify_board);

/*
    Gestion utilisateur
*/
void * req_create_account(char * username, char * password);
void * req_delete_account();
void * req_login(char * username, char * password);
void * req_disconnect(char * username, char * password);

/*
    Gestion d'une partie
*/
void * req_create_game(char * username, char * password);
void * req_join_game(char * username, char * password);
void * req_get_last_game_update(char * game_id);
void * req_move_game(char * username, char * password, char * game_id, int * initial_position, int * new_position);
void * req_quit_game();
void * req_list_game();
void * req_delete_game();

#endif /* connector_h */
