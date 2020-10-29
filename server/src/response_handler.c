/*******************************************************
Nom ......... : response_handler.c
Role ........ : Gère les réponse à envoyer au client
Auteur ...... : X
********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "response_handler.h"

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
    //Construction de la requête vers le serveur 
    char * response = malloc(sizeof(char) * 1024);
    response[0] = '\0';
    strcat(response, "message_type: START_GAME\n");
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