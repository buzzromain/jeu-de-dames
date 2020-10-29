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
    Fonctions utilitaires (à changer de fichier plus tard)
*/

/**
* Parse une chaîne de caractère correspondant au plateau
* de jeu reçu par le programme depuis le serveur en plateau de jeu sous forme
* de tableau d'entier manipulable par le programme.
*/
int ** parse_stringify_board(char * stringify_board) {
    //Alloue mémoire au tableau à deux dimensions
    int ** board = (int **)malloc(sizeof(int *) * 10);
    for(int i = 0; i < 10; i++) {
        board[i] = (int *)malloc(sizeof(int) * 10);
    }

    /*
    Parse la réponse reçu par le serveur.
    On récupère tous les elements (des chiffres) sauf les espaces.
    */
    char * token = strtok(stringify_board, ",");
    int i = 0, j = 0, k = 0;
    //j correspond à l'axe colonne
    //i correspond à l'axe ligne
    while(token != NULL) {
        /*
        On convertir les caractères lus en entiers et on les 
        stocke dans le tableau à deux dimensions board.
        */
        board[j][i] = atoi(token);
    
        i++;
        k++;   

        if((k % 10) == 0){
            j++;
            i=0;
        } 
        
        token = strtok(NULL, ",");
    }

    return board;
}

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

void * req_start_game(char * username, char * password, char * game_id) {
    //Construction de la requête vers le serveur 
    char * req = malloc(sizeof(char) * 1024);
    strcat(req, "message_type: START_GAME\n");
    strcat(req, "\nusername: ");
    strcat(req, username);
    strcat(req, "\n");
    strcat(req, "password: ");
    strcat(req, password);
    strcat(req, "game_id: ");
    strcat(req, game_id);
    strcat(req, "\n");

    //Envoie de la requête et récupération des données.
    char * res = request(req);

    //Affiche la réponse complète pour debugger (à enlever).
    //printf("%s", res);

    //Structure facilement manipulable.
    mes_start_game * mes = malloc(sizeof(mes_start_game));
    mes->message_type = malloc(sizeof(char) * 100);
    mes->code = malloc(sizeof(char) * 100);

    /*
    Parse la réponse reçu par le serveur.
    Code à factoriser plus tard.
    */
    char *p, *temp, *first_part, *sec_part;
    
    /*
    Erreur pour récupérer board (le plateau de jeu) dans la requête ici.
    A traiter.
    */
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

void * req_play_game() {
    return NULL;
    //TODO
}