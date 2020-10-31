/*******************************************************
Nom ......... : request_handler.c
Role ........ : Gère les requêtes qui arrive sur le
serveur.
Auteur ...... : X
********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "request_handler.h"

/**
* Permet de récupérer le type de message reçu.
* 
* \return le type de message
*/
void * get_message_type(char * request) {
    char *p, *temp, *first_part, *sec_part;
    char * tmp_req = malloc(sizeof(char) * 1024);
    strcpy(tmp_req, request);

    //Lit la première ligne
    p = strtok_r(tmp_req, "\n", &temp);

    //Lit la première partie (avant le caractère ': ')
    first_part = strtok(p, ": ");

    //Lit la deuxième partie (après le caractère ': ')
    sec_part = strtok(NULL, ": ");

    //Libere mémoire.
    free(tmp_req);
    
    //Retourne la seconde partie
    return sec_part;
}

/**
* Permet de gérer une demande de création de compte
* 
* \return la réponse à la requête.
*/
void * handle_create_account(char * request) {
    char * username = malloc(sizeof(char) * 100);
    char * password = malloc(sizeof(char) * 100);
    char * tmp_req = malloc(sizeof(char) * 1024);
    strcpy(tmp_req, request);

    //Parse la requête reçu par le serveur.
    char *p, *temp, *first_part, *sec_part;
    p = strtok_r(tmp_req, "\n", &temp);
    do {
        first_part = strtok(p, ": ");
        sec_part = strtok(NULL, ": ");
        if(strcmp("username", first_part) == 0) {
            strcpy(username, sec_part);
        }
        else if(strcmp("password", first_part) == 0) {
            strcpy(password, sec_part);
        }
    } while ((p = strtok_r(NULL, "\n", &temp)) != NULL);

    //Libere la mémoire.
    free(p);
    free(temp);
    free(tmp_req);

    return create_account(username, password);
}

/**
* Permet de gérer une connexion à un compte
* 
* \return la réponse à la requête.
*/
void * handle_login(char * request) {
    char * username = malloc(sizeof(char) * 100);
    char * password = malloc(sizeof(char) * 100);
    char * tmp_req = malloc(sizeof(char) * 1024);
    strcpy(tmp_req, request);

    //Parse la requête reçu par le serveur.
    char *p, *temp, *first_part, *sec_part;
    p = strtok_r(tmp_req, "\n", &temp);
    do {
        first_part = strtok(p, ": ");
        sec_part = strtok(NULL, ": ");
        if(strcmp("username", first_part) == 0) {
            strcpy(username, sec_part);
        }
        else if(strcmp("password", first_part) == 0) {
            strcpy(password, sec_part);
        }
    } while ((p = strtok_r(NULL, "\n", &temp)) != NULL);

    //Libere la mémoire.
    free(p);
    free(temp);
    free(tmp_req);

    return login(username, password);
}

/**
* Permet de gérer une déconnexion d'un compte
* 
* \return la réponse à la requête.
*/
void * handle_disconnect(char * request) {
    char * username = malloc(sizeof(char) * 100);
    char * password = malloc(sizeof(char) * 100);
    char * tmp_req = malloc(sizeof(char) * 1024);
    strcpy(tmp_req, request);

    //Parse la requête reçu par le serveur.
    char *p, *temp, *first_part, *sec_part;
    p = strtok_r(tmp_req, "\n", &temp);
    do {
        first_part = strtok(p, ": ");
        sec_part = strtok(NULL, ": ");
        if(strcmp("username", first_part) == 0) {
            strcpy(username, sec_part);
        }
        else if(strcmp("password", first_part) == 0) {
            strcpy(password, sec_part);
        }
    } while ((p = strtok_r(NULL, "\n", &temp)) != NULL);

    //Libere la mémoire.
    free(p);
    free(temp);
    free(tmp_req);

    return disconnect(username, password);
}

/**
* Permet de gérer la création d'une partie
* 
* \return la réponse à la requête.
*/
void * handle_create_game(char * request) {
    char * username = malloc(sizeof(char) * 100);
    char * password = malloc(sizeof(char) * 100);
    char * tmp_req = malloc(sizeof(char) * 1024);
    strcpy(tmp_req, request);

    //Parse la requête reçu par le serveur.
    char *p, *temp, *first_part, *sec_part;
    p = strtok_r(tmp_req, "\n", &temp);
    do {
        first_part = strtok(p, ": ");
        sec_part = strtok(NULL, ": ");
        if(strcmp("username", first_part) == 0) {
            strcpy(username, sec_part);
        }
        else if(strcmp("password", first_part) == 0) {
            strcpy(password, sec_part);
        }
    } while ((p = strtok_r(NULL, "\n", &temp)) != NULL);

    //Libere la mémoire.
    free(p);
    free(temp);
    free(tmp_req);

    return create_game(username, password);
}

/**
* Permet de lancer une partie.
* 
* \return la réponse à la requête.
*/
void * handle_join_game(char * request) {
    char * username = malloc(sizeof(char) * 100);
    char * password = malloc(sizeof(char) * 100);
    char * tmp_req = malloc(sizeof(char) * 1024);
    strcpy(tmp_req, request);

    //Parse la requête reçu par le serveur.
    char *p, *temp, *first_part, *sec_part;
    p = strtok_r(tmp_req, "\n", &temp);
    do {
        first_part = strtok(p, ": ");
        sec_part = strtok(NULL, ": ");
        if(strcmp("username", first_part) == 0) {
            strcpy(username, sec_part);
        }
        else if(strcmp("password", first_part) == 0) {
            strcpy(password, sec_part);
        }
    } while ((p = strtok_r(NULL, "\n", &temp)) != NULL);

    //Libere la mémoire.
    free(p);
    free(temp);
    free(tmp_req);

    return join_game(username, password);
}

/**
* Permet de recuperer une mise à jour de l'état de la partie
* 
* \return la réponse à la requête.
*/
void * handle_get_last_game_update(char * request) {
    char * game_id = malloc(sizeof(char) * 10);
    char * tmp_req = malloc(sizeof(char) * 1024);
    strcpy(tmp_req, request);

    //Parse la requête reçu par le serveur.
    char *p, *temp, *first_part, *sec_part;
    p = strtok_r(tmp_req, "\n", &temp);
    do {
        first_part = strtok(p, ": ");
        sec_part = strtok(NULL, ": ");
        if(strcmp("game_id", first_part) == 0) {
            strcpy(game_id, sec_part);
        }
    } while ((p = strtok_r(NULL, "\n", &temp)) != NULL);

    //Libere la mémoire.
    free(p);
    free(temp);
    free(tmp_req);

    return get_last_game_update(game_id);
}


/**
* Permet de deplacement le pion d'une partie.
* 
* \return la réponse à la requête.
*/
void * handle_move_game(char * request) {
    /*
    A faire pour ce genre de fonction : bien gérer les erreurs
    et la mémoire (dans toutes les fonctions qui utilisent les variables
    déclarés ici).
    */
    char * username = malloc(sizeof(char) * 100);
    char * password = malloc(sizeof(char) * 100);
    char * game_id = malloc(sizeof(char) * 10);
    int * initial_position = malloc(sizeof(int) * 2);
    int * new_position = malloc(sizeof(int) * 2);
    char * tmp_req = malloc(sizeof(char) * 1024);
    strcpy(tmp_req, request);

    //Parse la requête reçu par le serveur.
    char *p, *temp, *first_part, *sec_part;
    p = strtok_r(tmp_req, "\n", &temp);
    do {
        first_part = strtok(p, ": ");
        sec_part = strtok(NULL, ": ");
        if(strcmp("username", first_part) == 0) {
            strcpy(username, sec_part);
        }
        else if(strcmp("password", first_part) == 0) {
            strcpy(password, sec_part);
        }
        else if(strcmp("game_id", first_part) == 0) {
            strcpy(game_id, sec_part);
        }
        else if(strcmp("from", first_part) == 0) {
            initial_position = parse_position(sec_part);
        }
        else if(strcmp("to", first_part) == 0) {
            new_position = parse_position(sec_part);
        }
    } while ((p = strtok_r(NULL, "\n", &temp)) != NULL);

    //Libere la mémoire.
    free(p);
    free(temp);
    free(tmp_req);

    return move_game(username, password, game_id, initial_position, new_position);
}

/**
* Permet de gérer les requêtes en provenance des clients
* 
* \return la réponse à la requête.
*/
void * handle_request(char * request) {
    /*
        TODO :
            -Gestion d'erreur
    */

    /*
    Recupère le type de message d'appeler la bonne fonction pour 
    gérer la requête
    */
    char * message_type = get_message_type(request);
    if(strcmp("CREATE_ACCOUNT", message_type) == 0) {
        return handle_create_account(request);
    }
    else if(strcmp("LOGIN", message_type) == 0) {
        return handle_login(request);
    }
    else if(strcmp("DISCONNECT", message_type) == 0) {
        return handle_disconnect(request);
    }
    else if(strcmp("CREATE_GAME", message_type) == 0) {
        return handle_create_game(request);
    }
    else if(strcmp("MOVE_GAME", message_type) == 0) {
        return handle_move_game(request);
    }
    else if(strcmp("GET_LAST_GAME_UPDATE", message_type) == 0) {
        return handle_get_last_game_update(request);
    }
    else if(strcmp("JOIN_GAME", message_type) == 0) {
        return handle_join_game(request);
    }
    
    return "Error";
}