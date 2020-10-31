/*******************************************************
Nom ......... : response_handler.c
Role ........ : Gère les réponse à envoyer au client
Auteur ...... : X
********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "response_handler.h"

/*
    /!\
    TODO : 
        -Factoriser certaines parties du code qui font la même chose
*/

/**
* Construit la réponse pour le client.
* à la création d'une compte.
* 
* \param code nom d'utilisateur
* \return la réponse du serveur
*/
void * reply_create_account(char * code) {
    //Construction de la requête vers le serveur 
    char * response = malloc(sizeof(char) * 1024);
    response[0] = '\0';
    strcat(response, "message_type: CREATE_ACCOUNT\n");
    strcat(response, "code: ");
    strcat(response, code);
    strcat(response, "\n");

    return response;
}

/**
* Construit la réponse pour le client.
* à la connexion d'un utilisateur
* 
* \param code nom d'utilisateur
* \return la réponse du serveur
*/
void * reply_login(char * code, int nb_won_game) {
    //Construction de la requête vers le serveur 
    char * response = malloc(sizeof(char) * 1024);
    response[0] = '\0';
    strcat(response, "message_type: LOGIN\n");
    strcat(response, "code: ");
    strcat(response, code);
    strcat(response, "\n");

    if(nb_won_game != -1) {
        char * tmp = malloc(sizeof(char) * 10);
        sprintf(tmp, "%d", nb_won_game);

        strcat(response, "\n");
        strcat(response, "nb_won_game: ");
        strcat(response, tmp);
        strcat(response, "\n");

        free(tmp);
    }

    return response;
}

/**
* Construit la réponse pour le client.
* à la déconnexion d'un utilisateur.
* 
* \param code nom d'utilisateur
* \return la réponse du serveur
*/
void * reply_disconnect(char * code) {
    //Construction de la requête vers le serveur 
    char * response = malloc(sizeof(char) * 1024);
    response[0] = '\0';
    strcat(response, "message_type: DISCONNECT\n");
    strcat(response, "code: ");
    strcat(response, code);
    strcat(response, "\n");

    return response;
}

void * reply_board_game(char * message_type, char * code, int ** board) {
    //Construction de la requête vers le serveur 
    char * response = malloc(sizeof(char) * 1024);
    response[0] = '\0';
    strcat(response, "message_type: ");
    strcat(response, message_type);
    strcat(response, "\n");
    strcat(response, "code: ");
    strcat(response, code);
    strcat(response, "\n");

    if(board != NULL) {
        strcat(response, "\n");
        strcat(response, "board: ");
        strcat(response, stringify_board(board));
        strcat(response, "\n");
    }
    
    return response;
}


void * reply_create_game(char * code, char * game_id, char * player_side, int ** board) {
    //Construction de la requête vers le serveur 
    char * response = malloc(sizeof(char) * 1024);
    response[0] = '\0';
    strcat(response, "message_type: ");
    strcat(response, "CREATE_GAME");
    strcat(response, "\n");
    strcat(response, "code: ");
    strcat(response, code);
    strcat(response, "\n");

    if(game_id != NULL && board != NULL) {
        strcat(response, "\n");
        strcat(response, "game_id: ");
        strcat(response, game_id);
        strcat(response, "\n");
        strcat(response, "player_side: ");
        strcat(response, player_side);
        strcat(response, "\n");
        strcat(response, "board: ");
        strcat(response, stringify_board(board));
        strcat(response, "\n");
    }
    return response;
}

/**
* Pour l'instant, cette fonction ne fait que renvoyer 
* le plateau de jeu (à améliorer plus tard si besoin).
*/
void * reply_get_last_game_update(char * code, int ** board) {
    return reply_board_game("GET_LAST_GAME_UPDATE", code, board);
}

/**
* Pour l'instant, cette fonction ne fait que renvoyer 
* le plateau de jeu (à améliorer plus tard si besoin).
*/
void * reply_move_game(char * code, int ** board) {
    return reply_board_game("MOVE_GAME", code, board);
}


/**
* Construit la réponse pour le client.
* à la demande de rejoindre une partie.
* 
* \param code nom d'utilisateur
* \param game_id identifiant de la partie
* \param board identifiant de la partie
* \return la réponse du serveur
*/
void * reply_join_game(char * code, char * game_id, int ** board) {
    //Construction de la requête vers le serveur 
    char * response = malloc(sizeof(char) * 1024);
    response[0] = '\0';
    strcat(response, "message_type: ");
    strcat(response, "JOIN_GAME");
    strcat(response, "\n");
    strcat(response, "code: ");
    strcat(response, code);
    strcat(response, "\n");

    if(game_id != NULL && board != NULL) {
        strcat(response, "\n");
        strcat(response, "game_id: ");
        strcat(response, game_id);
        strcat(response, "\n");
        strcat(response, "board: ");
        strcat(response, stringify_board(board));
        strcat(response, "\n");
    }
    return response;
}