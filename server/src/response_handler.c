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
void * reply_login(char * code) {
    //Construction de la requête vers le serveur 
    char * response = malloc(sizeof(char) * 1024);
    response[0] = '\0';
    strcat(response, "message_type: LOGIN\n");
    strcat(response, "code: ");
    strcat(response, code);
    strcat(response, "\n");

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
    char * tmp = malloc(sizeof(char) * 3);
    char * stringify_board = malloc(sizeof(char) * 200);
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            sprintf(tmp, "%d,", board[i][j]);
            strcat(stringify_board, tmp);
        }
    }
    stringify_board[strlen(stringify_board) - 1] = '\0';

    strcat(response, "\n");
    strcat(response, "board: ");
    strcat(response, stringify_board);
    strcat(response, "\n");
    return response;
}

/**
* Construit la réponse pour le client.
* au lancement d'une partie.
* 
* \param code nom d'utilisateur
* \param board le plateau de jeu à envoyer
* \return la réponse du serveur
*/

void * reply_start_game(char * code, int ** board) {
    return reply_board_game("START_GAME", code, board);
}

/**
* Pour l'instant, cette fonction ne fait que renvoyer 
* le plateau de jeu (à améliorer plus tard).
*/
void * reply_move_game(char * code, int ** board) {
    return reply_board_game("MOVE_GAME", code, board);
}