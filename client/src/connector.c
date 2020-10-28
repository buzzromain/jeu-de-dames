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

    //Affiche les champs de la structure (à enlever plus tard).
    //printf("message_type: %s\n", mes->message_type);
    //printf("code: %s\n", mes->code);

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
void * req_login() {
    return NULL;
    //TODO
}

/**
* Se déconnecter
*/
void * req_disconnect() {
    return NULL;
    //TODO
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

void * req_start_game() {
    return NULL;
    //TODO
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

void * req_play_game() {
    return NULL;
    //TODO
}