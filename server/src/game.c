/*******************************************************
Nom ......... : game.c
Role ........ : Gère la logique du jeu
Auteur ...... : X
********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"

/**
* Permet de déplacer un pion
*
* \param current_game une partie.
* \param initial_position position initiale du pion.
* \param new_position la nouvelle position du pion.
*/
void move_draughts(game * current_game, int * initial_position, int * new_position) {
    /*
    Fonction a améliorer plus tard pour tenir en compte des règles du jeu.
    (paramètre à changer : prendra en parametre un plateau de jeu plutot que la structure game)
    */
    int draughts_value = current_game->board[initial_position[0]][initial_position[1]];
    current_game->board[initial_position[0]][initial_position[1]] = 0;
    current_game->board[new_position[0]][new_position[1]] = draughts_value;
}

/*
    /!\
    TODO : 
        -Factoriser le code de certaines fonctions liés à la gestion utilisateur
        qui ont du code qui fait la même chose (à ce stade l'implementation des fonctionnalités).
*/

/**
* Permet de créer un nouveau compte utilisateur
* 
* \param username nom d'utilisateur
* \param password le mot de passe de l'utilisateur
* \return la réponse du serveur
*/
void * create_account(char * username, char * password) {
    //Enregiste un nouvel utilisateur dans la base de donnée.
    char * id = db_register_new_user(username, password);

    //Si id vaut NULL, alors l'utilisateur existe déjà.
    if(id == NULL) {
        //On renvoie un code d'erreur spécifique
        return reply_create_account("USER_ALREADY_EXIST");
    }
    else {
        return reply_create_account("OK"); 
    }
    
    //Libération de mémoire.
    free(username);
    free(password);

    /*
    Retourne une réponse en appelant la fonction reply_create_account
    qui est chargé de construire la réponse vers le client.
    */
    return reply_create_account("ERROR");
}

/**
* Permet de connecter un utilisateur à son compte
* 
* \param username nom d'utilisateur
* \param password le mot de passe de l'utilisateur
* \return la réponse du serveur
*/
void * login(char * username, char * password) {
    //Recupère l'identifiant de l'utilisateur dans la base de données.
    char * id = db_login_user(username, password);

    //Si id vaut NULL, alors l'utilisateur n'existe déjà.
    if(id == NULL) {
        //On renvoie un code d'erreur spécifique
        return reply_login("INVALID_LOGIN");
    }
    else {
        return reply_login("OK"); 
    }
    
    //Libération de mémoire.
    free(username);
    free(password);

    /*
    Retourne une réponse en appelant la fonction reply_create_account
    qui est chargé de construire la réponse vers le client.
    */
    return reply_login("ERROR");
}

/**
* Permet de déconnecter un utilisateur de son compte
* 
* \param username nom d'utilisateur
* \param password le mot de passe de l'utilisateur
* \return la réponse du serveur
*/

void * disconnect(char * username, char * password) {
    //Enregiste un nouvel utilisateur dans la base de donnée.
    char * id = db_login_user(username, password);

    //Si id vaut NULL, alors l'utilisateur n'existe pas.
    if(id == NULL) {
        //On renvoie un code d'erreur spécifique
        return reply_disconnect("INVALID_LOGIN");
    }
    else {
        return reply_disconnect("OK"); 
    }
    
    /*
    Rajouter plus tard ici, d'autres actions à effectuer
    lorsqu'un utilisateur se deconnecte.
    */

    //Libération de mémoire.
    free(username);
    free(password);

    /*
    Retourne une réponse en appelant la fonction reply_create_account
    qui est chargé de construire la réponse vers le client.
    */
    return reply_disconnect("ERROR");
}

/**
* Initialise le plateau de jeu.
*
*/
void init_board() {
    //Alloue la mémoire au plateau de jeu.
    current_game->board = (int **)malloc(sizeof(int *) * NB_COLUMNS);
    for(int i = 0; i < NB_COLUMNS; i++) {
        current_game->board[i] = (int *)malloc(sizeof(int) * NB_LINES);
    }
    
    for(int j = 0; j < NB_COLUMNS; j++) {
        for(int i = 0; i < NB_LINES; i++) {
            if(i <= 3) {
                if((i + j) % 2) {
                    current_game->board[j][i] = 1;
                }
            }
            else if(i > 5) {
                if((i + j) % 2) {
                    current_game->board[j][i] = -1;
                }
            }
            else {
                current_game->board[j][i] = 0;
            }
        }
    }
}

/**
* Permet de déplacer un pion.
* 
* \param username nom d'utilisateur
* \param password le mot de passe de l'utilisateur
* \param game_id l'identifiant de la partie
* \param initial_position position initial du pion
* \param new_position nouvelle position du pion
* \return la réponse du serveur
*/
void * move_game(char * username, char * password, char * game_id, int * initial_position, int * new_position) {
    //Pour le moment on renvoie le même plateau de jeu.
    move_draughts(current_game, initial_position, new_position);
    return reply_move_game("OK", current_game->board); 
}

/**
* Permet de lancer une partie.
* 
* \param username nom d'utilisateur
* \param password le mot de passe de l'utilisateur
* \param game_id l'identifiant de la partie
* \return la réponse du serveur
*/
void * start_game(char * username, char * password, char * game_id) {
    /*
    Pour la demo, on ne fait rien des parametre que la fonction prend.
    et on ne gère pas encore les erreurs.
    */

    //Initialise le plateau de jeu (à enlever car cela génère un nouveau plateau à chaque fois)
    init_board();

    /*
    On renvoie simplement le plateau de jeu de la structure game
    que l'on a initialise au début du programme.
    A changer plus tard pour prendre en compte les utilisateurs et les differentes
    parties qui se deroulent simultannement sur le serveur.
    */
    return reply_start_game("OK", current_game->board); 
}

void init_game() {
    current_game = malloc(sizeof(game));
}