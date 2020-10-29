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
* Permet de créer un nouveau compte utilisateur
* 
* \param username nom d'utilisateur
* \param password le mot de passe de l'utilisateur
* \return la réponse du serveur
*/
void * create_account(char * username, char * password) {
    /*
    Ici on effectue toutes les actions à effectuer pour créer un nouveau compte
    Comme par exemple, vérifie que le joueur n'existe pas déjà.
    */
    //...
    //Par Exemple : 
    if(strcmp(username, "buzzromain") == 0 && strcmp(password, "superpassword") == 0) {
        //On peut mettre des printf ici pour afficher des logs sur le serveur.
        return reply_create_account("USER_ALREADY_EXIST");
    }
    else {
        //On peut mettre des printf ici pour afficher des logs sur le serveur.
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

    //Initialise le plateau de jeu.
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