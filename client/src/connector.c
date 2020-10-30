/*******************************************************
Nom ......... : connector.c
Role ........ : Gère les requêtes vers le serveur en
proposant une interface (ensemble de fonctions) simple.
Auteur ...... : X
********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "connector.h"

/*
TODO : 
    -En fonction de l'évolution des fonctionnalités :
    factoriser certaines parties du code qui font la même chose (voire fonction de gestion utilisateur).
*/

/*
    Gestion utilisateur
*/

/**
* Créer un nouveau compte
*/
void * req_create_account(char * username, char * password) {
    //Construction de la requête vers le serveur 
    char * req = malloc(sizeof(char) * 1024);
    strcat(req, "message_type: CREATE_ACCOUNT\n");
    strcat(req, "\nusername: ");
    strcat(req, username);
    strcat(req, "\n");
    strcat(req, "password: ");
    strcat(req, password);
    strcat(req, "\n");

    //Envoie de la requête et récupération des données.
    char * res = request(req);

    //Structure facilement manipulable.
    mes_create_account * mes = malloc(sizeof(mes_create_account));
    mes->message_type = malloc(sizeof(char) * 100);
    mes->code = malloc(sizeof(char) * 100);

    //Parse la réponse reçu par le serveur.
    char *p, *temp, *first_part, *sec_part;
    
    p = strtok_r(res, "\n", &temp);
    do {
        first_part = strtok(p, ": ");
        sec_part = strtok(NULL, ": ");
        if(strcmp("message_type", first_part) == 0) {
            strcpy(mes->message_type, sec_part);
        }
        else if(strcmp("code", first_part) == 0) {
            strcpy(mes->code, sec_part);
        }
    } while ((p = strtok_r(NULL, "\n", &temp)) != NULL);

    //Libere la mémoire.
    free(p);
    free(temp);
    free(req);
    free(res);

    //Retourne la structure.
    return mes;
}

/**
* Supprimer un compte
*/
void * req_delete_account() {
    return NULL;
    //TODO
}

/**
* Se connecter
*/
void * req_login(char * username, char * password) {
    //Construction de la requête vers le serveur 
    char * req = malloc(sizeof(char) * 1024);
    strcat(req, "message_type: LOGIN\n");
    strcat(req, "\nusername: ");
    strcat(req, username);
    strcat(req, "\n");
    strcat(req, "password: ");
    strcat(req, password);
    strcat(req, "\n");

    //Envoie de la requête et récupération des données.
    char * res = request(req);

    //Structure facilement manipulable.
    mes_login * mes = malloc(sizeof(mes_login));
    mes->message_type = malloc(sizeof(char) * 100);
    mes->code = malloc(sizeof(char) * 100);

    //Parse la réponse reçu par le serveur.
    char *p, *temp, *first_part, *sec_part;
    
    p = strtok_r(res, "\n", &temp);
    do {
        first_part = strtok(p, ": ");
        sec_part = strtok(NULL, ": ");
        if(strcmp("message_type", first_part) == 0) {
            strcpy(mes->message_type, sec_part);
        }
        else if(strcmp("code", first_part) == 0) {
            strcpy(mes->code, sec_part);
        }
    } while ((p = strtok_r(NULL, "\n", &temp)) != NULL);

    //Libere la mémoire.
    free(p);
    free(temp);
    free(req);
    free(res);

    //Retourne la structure.
    return mes;
}

/**
* Se déconnecter
*/
void * req_disconnect(char * username, char * password) {
    //Construction de la requête vers le serveur 
    char * req = malloc(sizeof(char) * 1024);
    strcat(req, "message_type: DISCONNECT\n");
    strcat(req, "\nusername: ");
    strcat(req, username);
    strcat(req, "\n");
    strcat(req, "password: ");
    strcat(req, password);
    strcat(req, "\n");

    //Envoie de la requête et récupération des données.
    char * res = request(req);

    //Structure facilement manipulable.
    mes_login * mes = malloc(sizeof(mes_login));
    mes->message_type = malloc(sizeof(char) * 100);
    mes->code = malloc(sizeof(char) * 100);

    //Parse la réponse reçu par le serveur.
    char *p, *temp, *first_part, *sec_part;
    
    p = strtok_r(res, "\n", &temp);
    do {
        first_part = strtok(p, ": ");
        sec_part = strtok(NULL, ": ");
        if(strcmp("message_type", first_part) == 0) {
            strcpy(mes->message_type, sec_part);
        }
        else if(strcmp("code", first_part) == 0) {
            strcpy(mes->code, sec_part);
        }
    } while ((p = strtok_r(NULL, "\n", &temp)) != NULL);

    //Libere la mémoire.
    free(p);
    free(temp);
    free(req);
    free(res);

    //Retourne la structure.
    return mes;
}

/*
    Gestion d'une partie
*/

/**
* Créer un nouveau compte
*/
void * req_create_game() {
    return NULL;
    //TODO
}

void * req_delete_game() {
    return NULL;
    //TODO
}

void * req_start_game(char * username, char * password, char * game_id) {
    //Construction de la requête vers le serveur 
    char * req = malloc(sizeof(char) * 1024);
    strcat(req, "message_type: START_GAME\n");
    strcat(req, "\nusername: ");
    strcat(req, username);
    strcat(req, "\n");
    strcat(req, "password: ");
    strcat(req, password);
    strcat(req, "\n");
    strcat(req, "game_id: ");
    strcat(req, game_id);
    strcat(req, "\n");

    //Envoie de la requête et récupération des données.
    char * res = request(req);

    //Structure facilement manipulable.
    mes_start_game * mes = malloc(sizeof(mes_start_game));
    mes->message_type = malloc(sizeof(char) * 100);
    mes->code = malloc(sizeof(char) * 100);

    /*
    Parse la réponse reçu par le serveur.
    Code à factoriser plus tard.
    */
    char *p, *temp, *first_part, *sec_part;
    
    p = strtok_r(res, "\n", &temp);
    do {
        first_part = strtok(p, ": ");
        sec_part = strtok(NULL, ": ");

        if(strcmp("message_type", first_part) == 0) {
            strcpy(mes->message_type, sec_part);
        }
        else if(strcmp("code", first_part) == 0) {
            strcpy(mes->code, sec_part);
        }
        else if(strcmp("board", first_part) == 0) {
            mes->board = parse_stringify_board(sec_part);
        }
    } while ((p = strtok_r(NULL, "\n", &temp)) != NULL);
   
    //Libere la mémoire.
    free(p);
    free(temp);
    free(req);
    free(res);

    return mes;

}

void * req_quit_game() {
    return NULL;
    //TODO
}

void * req_view_game() {
    return NULL;
    //TODO
}

void * req_list_game() {
    return NULL;
    //TODO
}

void * req_get_last_board_update() {
    return NULL;
    //TODO
}

void * req_move_game(char * username, char * password, char * game_id, int * initial_position, int * new_position) {
    char * stringify_initial_position = stringify_position(initial_position);
    char * stringify_new_position = stringify_position(new_position);
    
    //Construction de la requête vers le serveur 
    char * req = malloc(sizeof(char) * 1024);
    strcat(req, "message_type: MOVE_GAME\n");
    strcat(req, "\nusername: ");
    strcat(req, username);
    strcat(req, "\n");
    strcat(req, "password: ");
    strcat(req, password);
    strcat(req, "\n");
    strcat(req, "game_id: ");
    strcat(req, game_id);
    strcat(req, "\n");
    strcat(req, "from: ");
    strcat(req, stringify_initial_position);
    strcat(req, "\n");
    strcat(req, "to: ");
    strcat(req, stringify_new_position);
    strcat(req, "\n");

    //Envoie de la requête et récupération des données.
    char * res = request(req);

    //Structure facilement manipulable.
    mes_move_game * mes = malloc(sizeof(mes_move_game));
    mes->message_type = malloc(sizeof(char) * 100);
    mes->code = malloc(sizeof(char) * 100);

    /*
    Parse la réponse reçu par le serveur.
    Code à factoriser plus tard.
    */
    char *p, *temp, *first_part, *sec_part;
    
    p = strtok_r(res, "\n", &temp);
    do {
        first_part = strtok(p, ": ");
        sec_part = strtok(NULL, ": ");

        if(strcmp("message_type", first_part) == 0) {
            strcpy(mes->message_type, sec_part);
        }
        else if(strcmp("code", first_part) == 0) {
            strcpy(mes->code, sec_part);
        }
        else if(strcmp("board", first_part) == 0) {
            mes->board = parse_stringify_board(sec_part);
        }
    } while ((p = strtok_r(NULL, "\n", &temp)) != NULL);

    //Libere la mémoire.
    free(p);
    free(temp);
    free(req);
    free(res);
    free(stringify_initial_position);
    free(stringify_new_position);

    return mes;
}