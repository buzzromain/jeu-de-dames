/*******************************************************
Nom ......... : game.c
Role ........ : Gère la logique du jeu
Auteur ...... : X
********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"


/*
    Gestion des joueurs.
*/

/**
* Initialise le tableau de joueur connecté
*/
void init_connected_player() {
    connected_players = (player **)malloc(sizeof(player *) * MAX_USER);
    for(int i = 0; i < MAX_USER; i++) {
        connected_players[i] = NULL;
    }
}

/**
* Renvoi un pointeur sur un joueur connecté sur le serveur.
* 
* \param username le nom d'utilisateur
* \param password le mot de passe
* \return un pointeur sur le joueur connecté, null si on ne peut pas recuperer le joueur (mauvais username et/ou password)
*/ 
void * get_connected_player(char * username, char * password) {
    //Parcours le tableau de joueur connectés.
    for(int i = 0; i < MAX_USER; i++) {
        //Si la case du tableau n'est pas null
        if(connected_players[i] != NULL) {
            //Verifie qu'il s'agit bien d'un bon nom d'utilisateur et mot de passe
            if(strcmp(connected_players[i]->username, username) == 0 && strcmp(connected_players[i]->password, password) == 0) {
                return connected_players[i];
            }
        }
    }
    return NULL;
}

/**
* Ajouter un nouveau joueur connecté
* 
* \param user structure db_user
* \return 0 si l'opération s'est bien déroulé, -1 si une erreur est survenu.
*/
int add_connected_player(db_user * user) {
    int found = -1;
    int i = 0;

    while(i < MAX_USER && found == -1) {
        if(connected_players[i] == NULL) {
            found = i;
        }
        i++;
    }


    if(found != -1) {
        //Allocation de mémoire.
        connected_players[found] = malloc(sizeof(player));
        connected_players[found]->user_id = malloc(sizeof(char) * 10);
        connected_players[found]->username = malloc(sizeof(char) * 255);
        connected_players[found]->password = malloc(sizeof(char) * 255);

        strcpy(connected_players[found]->user_id, user->id);
        strcpy(connected_players[found]->username, user->username);
        strcpy(connected_players[found]->password, user->password);
        connected_players[found]->nb_won_game = user->nb_won_game;

        return 0;
    }
    else {
        return -1;
    }
}

/**
* Enlever un nouveau joueur connecté
* 
* \param player un joueur connecté
* \return 0 si l'opération s'est bien déroulé, -1 si une erreur est survenu.
*/
int remove_connected_player(player * current_player) {
    int found = -1;
    int i = 0;
    while(i < MAX_USER && found == -1) {
        if(connected_players[i] == current_player) {
            found = i;
        }
        i++;
    }

    if(found != -1) {
        connected_players[found] = NULL;
        free(current_player);
        return -1;
    }
    else {

        return 0;
    }
}

/**
* Test si l'utilisateur est connecté au serveur.
* 
* \param username nom d'utilisateur
* \return 1 si l'utilisateur est connecté, 0 si l'utilisateur n'est pas connecté.
*/
int is_connected_player(char * username) {
    for(int i = 0; i < MAX_USER; i++) {
        if(connected_players[i] != NULL) {
            if(strcmp(connected_players[i]->username, username) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

/**
* Obtenir une partie à partir de son identifiant
* 
* \param game_id identifiant de la partie
* \return une partie, null si la partie n'existe pas.
*/
void * get_game_by_id(char * game_id) {
    for(int i = 0; i < SIMULTANEOUS_GAME; i++) {
        if(active_games[i] != NULL) {
            if(strcmp(active_games[i]->game_id, game_id) == 0) {
                return active_games[i];
            }
        }
    }
    return NULL;
}

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

    /*
    Ici mettre à jour, le joueur qui doit jouer en fonction du déplacement.
    */
    int draughts_value = current_game->board[initial_position[0]][initial_position[1]];
    current_game->board[initial_position[0]][initial_position[1]] = 0;
    current_game->board[new_position[0]][new_position[1]] = draughts_value;
}

/*
    Gestion des utilisateurs
*/

/**
* Permet de créer un nouveau compte utilisateur
* 
* \param username nom d'utilisateur
* \param password le mot de passe de l'utilisateur
* \return la réponse du serveur
*/
void * create_account(char * username, char * password) {
    //Recupère une structure db_user contenant les informations sur l'utilisateur.
    db_user * user = db_register_new_user(username, password);

    //Libération de mémoire.
    free(username);
    free(password);

    //Si user vaut NULL, alors l'utilisateur existe déjà.
    if(user == NULL) {
        //On renvoie un code d'erreur spécifique.
        return reply_create_account("USER_ALREADY_EXIST");
    }
    else {
        //Ajoute un nouveau joueur connecté sur le serveur.
        add_connected_player(user);
        free(user);

        //Notifie l'utilisateur du bon déroulement de l'opération
        return reply_create_account("OK"); 
    }
    
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
    //Recupère une structure db_user contenant les informations sur l'utilisateur.
    db_user * user = db_login_user(username, password);

    //Libération de mémoire.
    free(username);
    free(password);

    /*
    Si user vaut NULL, alors les identifiants ne sont pas correctes
    ou une erreur est survenue lors de la récupération des données.
    */
    if(user == NULL) {
        //On renvoie un code d'erreur spécifique
        return reply_login("INVALID_LOGIN", -1);
    }
    else {
        //Ajoute un nouveau joueur connecté sur le serveur.
        add_connected_player(user);
        int nb_won_game = user->nb_won_game;
        free(user);

        /*
        Notifie l'utilisateur du bon déroulement de l'opération
        en lui envoyant le code OK et le nombre de parties gagnés.
        */
        return reply_login("OK", nb_won_game); 
    }
    
    return reply_login("ERROR", -1);
}

/**
* Permet de déconnecter un utilisateur de son compte
* 
* \param username nom d'utilisateur
* \param password le mot de passe de l'utilisateur
* \return la réponse du serveur
*/

void * disconnect(char * username, char * password) {
    //Recupère une structure db_user contenant les informations sur l'utilisateur.
    db_user * user = db_login_user(username, password);

    //Libération de mémoire.
    free(password);

    /*
    Si user vaut NULL, alors les identifiants ne sont pas correctes
    ou une erreur est survenue lors de la récupération des données.
    */    
    if(user == NULL) {
        //On renvoie un code d'erreur spécifique
        return reply_disconnect("INVALID_LOGIN");
    }
    else {
        //On vérifie si l'utilisateur est déjà connecté.
        if(is_connected_player(username) == 1) {
            //Retire l'utilisateur de la liste des joueur connectés.
            remove_connected_player(get_connected_player(user->username, user->password));
            free(username);
            free(user);
            return reply_disconnect("OK"); 
        } else {
            return reply_disconnect("NOT_CONNECTED");
        }
    }
    
    return reply_disconnect("ERROR");
}

/*
    Gestion du jeu
*/

/**
* Initialise le tableau de partie en cours.
*/
void init_active_games() {
    active_games = (game **)malloc(sizeof(game *) * SIMULTANEOUS_GAME);
    for(int i = 0; i < SIMULTANEOUS_GAME; i++) {
        active_games[i] = NULL;
    }
    nb_active_games = 0;
}

/**
* Creer un nouveau plateau de jeu.
*
* \return un nouveau plateau de jeu
*/
int ** create_new_board() {
    //Alloue la mémoire au plateau de jeu.
    int ** board = (int **)malloc(sizeof(int *) * NB_COLUMNS);
    for(int i = 0; i < NB_COLUMNS; i++) {
        board[i] = (int *)malloc(sizeof(int) * NB_LINES);
    }
    
    //Initialise le plateau de jeu
    for(int j = 0; j < NB_COLUMNS; j++) {
        for(int i = 0; i < NB_LINES; i++) {
            if(i <= 3) {
                if((i + j) % 2) {
                    board[j][i] = 1;
                }
            }
            else if(i > 5) {
                if((i + j) % 2) {
                    board[j][i] = -1;
                }
            }
            else {
                board[j][i] = 0;
            }
        }
    }
    return board;
}

/**
* Verifie si un mouvement est autorisé
* 
* \param board nom d'utilisateur
* \param must_play le joueur qui a la main pour jouer
* \param player_side le mot de passe de l'utilisateur
* \param initial_position position initial du pion
* \param new_position nouvelle position du pion
* \return 1 si le déplacement est valide, 0 sinon.
*/
int is_valid_move(int ** board, int must_play, int player_side, int * initial_position, int * new_position) {
    //Pour l'instant, tout les mouvements sont autorisés.
    //Implementer la fonction plus tard.
    return 1;
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
    //Recuperation de la partie en fonction de son identifiant
    game * current_game = get_game_by_id(game_id);

    //Si la partie n'existe pas
    if(current_game == NULL) {
        return reply_move_game("NOT_EXIST", NULL);  
    }
    else {
        //Verifie si le joueur est connecté
        if(is_connected_player(username) == 1) {
            //Recupère le joueur dans la liste de joueur connecté.
            player * current_player = get_connected_player(username, password);
            int player_side = -1;
            
            //On recupere le côté du joueur sur le plateau.
            if(current_game->first_player == current_player) {
                player_side = 1;
            }
            else if(current_game->second_player == current_player) {
                player_side = 2;
            } 

            /*
            Si le joueur n'est pas sur un deux côte, il ne participe pas 
            à la partie
            */
            if(player_side == -1) {
                //Envoie un message d'erreur pour indiquer qu'il n'est pas autorisé.
                return reply_move_game("NOT_AUTHORIZED_USER", current_game->board); 
            }
            
            else {
                //Si il s'agit d'un mouvement autorisé
                if(is_valid_move(current_game->board, current_game->must_play, player_side, initial_position, new_position) == 1) {
                    //On déplace le pion
                    move_draughts(current_game, initial_position, new_position);

                    //On met à jour le joueur qui doit jouer (penser à le changer de place pour mettre dans move)
                    if(current_game->must_play == 1) {
                        current_game->must_play = 2;
                    }
                    else {
                        current_game->must_play = 1;
                    }
                    return reply_move_game("OK", current_game->board); 
                }
                else {
                    //Le mouvement n'est pas autorisé 
                    return reply_move_game("NOT_AUTHORIZED_MOVE", current_game->board); 
                }
            }
        }
    }
    return reply_move_game("ERROR", current_game->board); 
}

/**
* Permet d'obtenir des informations sur une partie en cours
* 
* \param game_id l'identifiant de la partie
* \return la réponse du serveur
*/
void * get_last_game_update(char * game_id) {
    //Recuperation de la partie en fonction de son identifiant
    game * current_game = get_game_by_id(game_id);

    //Si la partie n'existe pas
    if(current_game == NULL) {
        return reply_get_last_game_update("NOT_EXIST", NULL);  
    }
    else {
        //Si il n'y pas de joueur 2 dans la partie.
        if(current_game->second_player == NULL) {
            return reply_get_last_game_update("WAIT_FOR_SECOND_PLAYER", current_game->board);
        }
        else {
            if(current_game->must_play == 1) {
                return reply_get_last_game_update("WAIT_FIRST_PLAYER_MOVE", current_game->board);
            }
            else if(current_game->must_play == 2){
                return reply_get_last_game_update("WAIT_SECOND_PLAYER_MOVE", current_game->board);
            }
        }
        //Si la partie existe, on envoie le plateau de jeu.
        return reply_get_last_game_update("OK", current_game->board); 
    }

    return reply_get_last_game_update("ERROR", NULL); 
}

/**
* Permet de creer une partie.
* 
* \param username nom d'utilisateur
* \param password le mot de passe de l'utilisateur
* \return la réponse du serveur
*/
void * create_game(char * username, char * password) {
    player * current_player = get_connected_player(username, password);
    printf("%s\n", current_player->username);
    fflush(stdout);
    

    //Libere la mémoire.
    free(username);
    free(password);

    //Verifie si l'utilisateur est bien authentifié sur le serveur
    if(current_player == NULL) {
        //On notifie l'utilisateur que l'utilisateur n'est pas connecté sur le serveur
        return reply_create_game("NOT_CONNECTED", NULL, NULL, NULL);
    }
    else {
        //Verifie si le nombre maximale de parties simultanées n'a pas été atteint.
        if(nb_active_games < SIMULTANEOUS_GAME && current_player != NULL) {
            srand(time(NULL));
            int found = -1;
            int i = 0;

            //Trouve le première emplacement vide pour allouer mémoire pour la partie
            while(i < SIMULTANEOUS_GAME && found == -1) {
                if(active_games[i] == NULL) {
                    found = i;
                }
                i++;
            }

            active_games[found] = malloc(sizeof(game));
            char * game_id = malloc(sizeof(char) * 10);
            sprintf(game_id, "%d", rand() % 1000);
            active_games[found]->game_id = game_id;
            active_games[found]->board = create_new_board();
            active_games[found]->first_player = current_player;
            active_games[found]->second_player = NULL;
            active_games[found]->must_play = 1;

            return reply_create_game("OK", game_id, "1", active_games[found]->board);
        } 
        else {
            //On notifie l'utilisateur qu'il a trop de parties actives sur le serveur.
            return reply_create_game("TOO_MANY_ACTIVE_GAME", NULL, NULL, NULL);
        }
    }

    return reply_create_game("ERROR", NULL, NULL, NULL);
}

/**
* Permet à un joueur de rejoindre une partie.
* 
* \param username nom d'utilisateur
* \param password le mot de passe de l'utilisateur
* \return la réponse du serveur
*/
void * join_game(char * username, char * password) {
    player * current_player = get_connected_player(username, password);

    //Libere la mémoire.
    free(username);
    free(password);

    //Verifie si l'utilisateur est bien authentifié sur le serveur
    if(current_player == NULL) {
        //On notifie l'utilisateur que l'utilisateur n'est pas connecté sur le serveur
        return reply_join_game("NOT_CONNECTED", NULL, NULL);
    }
    else {
        //On cherche la première partie sans joueur.
        int i = 0;
        int found = -1;
        while(i < SIMULTANEOUS_GAME && found == -1) {
            if(active_games[i] != NULL) {
                if(active_games[i]->second_player == NULL) {
                    found = i;
                }
            }
            i++;
        }

        if(found != -1) {
            active_games[found]->second_player = current_player;
            return reply_join_game("OK", active_games[found]->game_id, active_games[found]->board);
        }
        else {
            return reply_join_game("NO_GAME_AVAILABLE", NULL, NULL);
        }
    }

    return reply_join_game("OK", NULL, NULL);
}


void init_game() {
    init_active_games();
    init_connected_player();    
}