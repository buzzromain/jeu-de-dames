#ifndef connector_h
#define connector_h
#include "client.h"
/* 
    Structure des réponses
*/
struct mes_account_type1 {
    char * message_type;
    char * code;
};
typedef struct mes_account_type1 mes_create_account;
typedef struct mes_account_type1 mes_delete_account;
typedef struct mes_account_type1 mes_login;
typedef struct mes_account_type1 mes_disconnect;

struct mes_game_type1 {
    char * message_type;
    char * code;
};
typedef struct mes_game_type1 mes_quit_game;
typedef struct mes_game_type1 mes_play_game;
typedef struct mes_game_type1 mes_delete_game;

struct mes_game_type2 {
    char * message_type;
    char * code;
    int game_id;
    int ** board;
};
typedef struct mes_game_type2 mes_create_game;
typedef struct mes_game_type2 mes_get_last_board_update;

struct mes_game_type3 {
    char * message_type;
    char * code;
    int ** board;
};
typedef struct mes_game_type3 mes_start_game;
typedef struct mes_game_type3 mes_view_game;

struct mes_game_type4 {
    char * message_type;
    char * code;
    int * games_id;
};
typedef struct mes_game_type4 mes_list_game;

/*
    Fonctions utilitaires (à changer de fichier plus tard)
*/
int ** parse_stringify_board(char * stringify_board);

/*
    Gestion utilisateur
*/
void * req_create_account();
void * req_delete_account();
void * req_login();
void * req_disconnect();

/*
    Gestion d'une partie
*/
void * req_create_game();
void * req_delete_game();
void * req_start_game();
void * req_quit_game();
void * req_view_game();
void * req_list_game();
void * req_get_last_board_update();
void * req_play_game();

#endif /* connector_h */
