/*******************************************************
Nom ......... : game.c
Role ........ : Gère la logique du jeu.
Auteur ...... : X
********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include "game.h"

/**
* Initialise le joueur.
*/
void init_current_player() {
    current_player = malloc(sizeof(player));
    current_player->username = malloc(sizeof(char) * 255);
    current_player->password = malloc(sizeof(char) * 255);
    current_player->nb_win_game = -1;
}

/**
* Enleve le joueur connecté
*/
void free_current_player() {
   if(is_connected_player() == 1) {
        free(current_player->username);
        free(current_player->password);
        free(current_player);
   }
}

/**
* Test si le joueur est connecté
* 
* \return 1 si le joueur est connecté, 0 sinon.
*/
int is_connected_player() {
    if(current_player != NULL) {
        return 1;
    }
    return 0;
}

/**
* Initialise la partie
*/
void init_current_game() {
    current_game = malloc(sizeof(game));
    current_game->game_id = malloc(sizeof(char) * 10);
    current_game->player_side = -1;
}

/**
* Supprime la partie
*/
void free_current_game() {
    free(current_game->board);
    free(current_game->game_id);
    free(current_game);
}

/**
* Affiche le plateau de jeu.
*
* \param board le plateau à afficher
*/
void print_board(int ** board) {
    system("clear");
    printf("    1    2     3    4    5    6    7    8    9   10\n");
    printf("   ─────────────────────────────────────────────────\n");
    for(int j = 0; j < NB_COLUMNS; j++) {
        printf("%c ┃ ", int_to_ascii(17 + j));
        for(int i = 0; i < NB_LINES; i++) {
            if(board[i][j] == 1) {
                print_black_draughts_man();
            }
            else if(board[i][j] == -1) {
                print_white_draughts_man();
            }
            else if(board[i][j] == 2) {
                print_black_draughts_king();
            }
            else if(board[i][j] == -2) {
                print_white_draughts_king();
            }
            else {
                printf("  ");
            }
            printf(" ┃ ");
        }
        printf("\n   ─────────────────────────────────────────────────\n");
    }
}

/**
* Création d'un nouveau compte
*/
void create_new_account() {
    char * username = malloc(sizeof(char) * 255);
    char * password = malloc(sizeof(char) * 255);

    //Demande à l'utilisateur de choisir un nom d'utilisateur et un mot de passe.
    system("clear");
    printf("=== Création d'un nouveau compte ===\n");
    printf("Nom d'utilisateur : ");
    scanf("%s", username);
    printf("Mot de passe : ");
    scanf("%s", password);
    printf("====================================\n");

    mes_create_account * res = req_create_account(username, password);

    /*
    On vérifie que la création du code s'est bien déroulé, 
    en testant si le code de retour est "OK".
    */
    if(strcmp(res->code, "OK") == 0) {
        /*
        Si l'opération s'est bien déroulé, on met à jour la structure de données.
        */
        //Libère la mémoire utilisé si un utilisateur est déjà connecté.
        free_current_player();
        init_current_player();
        strcpy(current_player->username, username);
        strcpy(current_player->password, password);
        current_player->nb_win_game = 0;
        free(username);
        free(password);
        printf("Compte créé avec succès !\n");
    }
    else if(strcmp(res->code, "USER_ALREADY_EXIST") == 0) {
        free(username);
        free(password);

        //L'utilisateur existe déjà.
        printf("Impossible de créer un compte. Ce compte existe déjà !\n");

        //On demande à l'utilisateur si il souhaite reessayer.
        int choice = 0;
        while(choice < 1 || choice > 2) {
            printf("Souhaitez-vous réessayer ?\n");
            printf("1. OUI\n");
            printf("2. NON\n");
            printf("Votre choix : ");
            scanf("%d", &choice);
            if(choice == 1) {
                create_new_account();
            }
            else if(choice == 2) {
                break;
            }
        }
    }
    else {
        printf("Une erreur du serveur est survenu\n");
    }
}

/**
* Connexion au compte
*/
void login() {
    char * username = malloc(sizeof(char) * 255);
    char * password = malloc(sizeof(char) * 255);

    //Demande à l'utilisateur de saisir son nom d'utilisateur et son mot de passe.
    system("clear");
    printf("=== Connexion ===\n");
    printf("Nom d'utilisateur : ");
    scanf("%s", username);
    printf("Mot de passe : ");
    scanf("%s", password);
    printf("====================================\n");

    mes_login * res = req_login(username, password);

    /*
    On vérifie que la création du code s'est bien déroulé, 
    en testant si le code de retour est "OK".
    */
    if(strcmp(res->code, "OK") == 0) {
        //Si l'opération s'est bien déroulé, on met à jour la structure
        free_current_player();
        init_current_player();
        strcpy(current_player->username, username);
        strcpy(current_player->password, password);
        current_player->nb_win_game = res->nb_win_game;
        free(username);
        free(password);
        printf("Connexion avec succès !\n");
    }
    else if(strcmp(res->code, "INVALID_LOGIN") == 0) {
        free(username);
        free(password);

        //L'utilisateur existe déjà.
        printf("Impossible de se connecter au compte. Les identifiants sont invalides.\n");

        //On demande à l'utilisateur si il souhaite reessayer.
        int choice = 0;
        while(choice < 1 || choice > 2) {
            printf("Souhaitez-vous réessayer ?\n");
            printf("1. OUI\n");
            printf("2. NON\n");
            printf("Votre choix : ");
            scanf("%d", &choice);
            if(choice == 1) {
                login();
            }
            else if(choice == 2) {
                break;
            }
        }
    }
    else {
        printf("Une erreur du serveur est survenu\n");
    }
}

/**
* Deconnexion de l'utilisateur
*/
void disconnect() {
    if(is_connected_player() == 1) {
        int choice = 0;
        //Demande à l'utilisateur de saisir son nom d'utilisateur et son mot de passe.
        system("clear");
        printf("=== Deconnexion ===\n");
        printf("Souhaitez-vous vraiment vous deconnecter ?\n");
        printf("1. OUI\n");
        printf("2. NON\n");
        while(choice < 1 || choice > 2) {
            printf("Votre choix : ");
            scanf("%d", &choice);
        }

        if(choice == 1) {
            mes_disconnect * res = req_disconnect(current_player->username, current_player->password);
            /*
            On vérifie que la création du code s'est bien déroulé, 
            en testant si le code de retour est "OK".
            */
            if(strcmp(res->code, "OK") == 0) {
                //Si l'opération s'est bien déroulé, on met à jour la structure
                free_current_player();
                printf("Deconnexion avec succès !\n");
            }
            else if(strcmp(res->code, "INVALID_LOGIN") == 0) {
                //L'utilisateur existe déjà.
                printf("Impossible de se deconnecter au compte. Les identifiants sont invalides.\n");
            }
            else {
                printf("Une erreur du serveur est survenu\n");
            }
        }
        else {
            printf("OK, pas de souci !\n");
        }
    }
    else {
        printf("Vous n'êtes connecté à aucun compte !\n");
    }
}

/**
* Vérifie si le déplacement est valide
* 
* \param initial_position position initial 
* \param new_position nouvelle position
* \return 1 si le déplacement est valide, 0 sinon.
*/
int is_valid_move(int * initial_position, int * new_position) {
    /*
    Pour le test on fait rien avec les paramètre et on renvoie
    toujours 1. De plus on ne gère pas le fait qu'il y a 2 utilisateurs.
    */
    return 1;
}

/**
* Creer une nouvelle partie.
*/
void create_game() {
    printf("Lancement du plateau de jeu...\n");

    mes_create_game * res = req_create_game(current_player->username, current_player->password);

    if(strcmp(res->code, "OK") == 0) {
        //Affiche ici le plateau de jeu en appelant la fonction pour afficher le plateau de jeu (fonction à importer plus tard).
        //Initialise la structure current_game
        
        init_current_game();

        strcpy(current_game->game_id, res->game_id);
        current_game->player_side = res->player_side;
        current_game->board = res->board;

        mes_get_last_game_update * upd = req_get_last_game_update(current_game->game_id);
        //Attente de l'arrivée du second joueur dans la partie.
        
        while(upd != NULL && strcmp(upd->code, "WAIT_FOR_SECOND_PLAYER") == 0) {
            print_board(current_game->board);
            printf("\nEN ATTENTE DU SECOND JOUEUR\n");
            sleep(1);
            //free(upd);
            upd = req_get_last_game_update(current_game->game_id);
        }
        
        mes_move_game * move_upd;
        char * user_input = malloc(sizeof(char) * 6);
        int ** positions;
        int * initial_position;
        int * new_position;

        while(strcmp(user_input, "exit") != 0) {
            /*
            Ici boucle infini qui teste quel joueur à la main sur le jeu 
            en faisant une requête au serveur.
            */
            //Attente de l'arrivée du second joueur dans la partie.
            upd = req_get_last_game_update(current_game->game_id);
            while(strcmp(upd->code, "WAIT_SECOND_PLAYER_MOVE") == 0) {
                printf("coucou\n");
                print_board(current_game->board);
                printf("\nEN ATTENTE DE DEPLACEMENT DE PION DU SECOND JOUEUR\n");
                sleep(1);
                //free(upd);
                upd = req_get_last_game_update(current_game->game_id);
            }
            //free(current_game->board);
            current_game->board = upd->board;
            print_board(current_game->board);

            printf("Action : ");
            scanf("%s", user_input);
            if(strcmp(user_input, "exit") != 0) {
                positions = get_positions_by_parsing_user_input(user_input);
                initial_position = positions[0];
                new_position = positions[1];
                //On verifie si le déplacement est autorisé.
                if(is_valid_move(initial_position, new_position) == 1) {
                    //On envoie une requête au serveur.
                    move_upd = req_move_game(current_player->username, current_player->password, current_game->game_id, initial_position, new_position);

                    //On vérifie si la requête à la demande à réussit.
                    if(strcmp(move_upd->code, "OK") == 0) {
                        //Si la requête a réussit, on actualise le plateau de jeu.
                        //free(current_game->board);
                        current_game->board = move_upd->board;
                    }
                    else {
                        printf("Oups... Probleme");
                    }
                }

                //Libère la mémoire.
                //free(initial_position);
                //free(new_position);
                //free(positions);
            }
        }
        //free(res);
        //free(user_input);
        //free(upd);
    }
    else {
        //Si on a pas réussi à afficher le plateau de jeu, on affiche un message à l'utilisateur;
        printf("Oups, impossible de récupérer le plateau de jeu.\n");
    }
}

/**
* Rejoint une partie.
*/
void join_game() {
    /*
    Pour tester, la fonction prend en paramètre game_id
    plus tard la fonction devra lister des parties (en faisant appel à list_game()) et rejoindre une partie libre.
    */
    printf("Lancement du plateau de jeu...\n");
    mes_join_game * res = req_join_game(current_player->username, current_player->password);

    if(strcmp(res->code, "OK") == 0) {
        //Affiche ici le plateau de jeu en appelant la fonction pour afficher le plateau de jeu (fonction à importer plus tard).
        //Initialise la structure current_game
        init_current_game();
        strcpy(current_game->game_id, res->game_id);
        current_game->player_side = 2;
        current_game->board = res->board;

        mes_get_last_game_update * upd = req_get_last_game_update(current_game->game_id);;

        mes_move_game * move_upd;
        char * user_input = malloc(sizeof(char) * 6);
        int ** positions;
        int * initial_position;
        int * new_position;

        while(strcmp(user_input, "exit") != 0) {
            /*
            Ici boucle infini qui teste quel joueur à la main sur le jeu 
            en faisant une requête au serveur.
            */
            //Attente de l'arrivée du second joueur dans la partie.
            upd = req_get_last_game_update(current_game->game_id);
            while(upd != NULL && strcmp(upd->code, "WAIT_FIRST_PLAYER_MOVE") == 0) {
                print_board(current_game->board);
                printf("\nEN ATTENTE DE DEPLACEMENT DE PION DU PREMIER JOUEUR\n");
                sleep(1);
                //free(upd);
                upd = req_get_last_game_update(current_game->game_id);
            }
            current_game->board = upd->board;
            print_board(current_game->board);

            printf("Action : ");
            scanf("%s", user_input);
            if(strcmp(user_input, "exit") != 0) {
                positions = get_positions_by_parsing_user_input(user_input);
                initial_position = positions[0];
                new_position = positions[1];
                //On verifie si le déplacement est autorisé.
                if(is_valid_move(initial_position, new_position) == 1) {
                    //On envoie une requête au serveur.
                    move_upd = req_move_game(current_player->username, current_player->password, current_game->game_id, initial_position, new_position);

                    //On vérifie si la requête à la demande à réussit.
                    if(strcmp(move_upd->code, "OK") == 0) {
                        //Si la requête a réussit, on actualise le plateau de jeu.
                        //free(current_game->board);
                        current_game->board = move_upd->board;
                    }
                    else {
                        printf("Oups... Probleme");
                    }
                }

                //Libère la mémoire.
                //free(initial_position);
                //free(new_position);
                //free(positions);
                //free(upd);
                //free(move_upd);
                //free(res);
            }
        }
        //free(user_input);
    }
    else {
        //Si on a pas réussi à afficher le plateau de jeu, on affiche un message à l'utilisateur;
        printf("Oups, impossible de récupérer le plateau de jeu.\n");
    }
}

/**
* Menu de jeu.
*/
void print_game_menu() {
    int choice = 0;
    system("clear");
    printf("=== Jeu de dame en réseau === \n");
    printf("   === Partie ===   \n");
    printf("1. Créer une partie.\n");
    printf("2. Rejoindre une partie\n");
    printf("3. Voir une partie\n");
    printf("4. Se deconnecter\n");
    printf("Votre choix : ");

    while(choice < 1 || choice > 4) {
        scanf("%d", &choice);  
        if(choice == 1) {
            create_game();
        }
        else if(choice == 2) {
            join_game();
        }
        else if(choice == 3) {
            //start_game();
        }
        else if(choice == 4) {
            disconnect();
        }
    }
}

/**
* Menu de connexion.
*/

void print_connection_menu() {
    int choice = 0;
    system("clear");
    printf("=== Jeu de dame en réseau === \n");
    printf("   === Connexion ===   \n");
    printf("1. Créer un compte.\n");
    printf("2. Se connecter\n");
    printf("3. Quitter\n");
    printf("Votre choix : ");

    while(choice < 1 || choice > 3) {
        scanf("%d", &choice);  
        if(choice == 1) {
            //L'utilisateur décide de créer un compte.
            create_new_account();
        }
        else if(choice == 2) {
            //L'utilisateur décide de se connecter à son compte.
            login();
        }
        else if(choice == 3) {
            break;
        }
    }
}

/**
* Fonction principale du jeu.
*/
void run_game() {  
    int choice = 0;

    //Initialise manuellement l'utilisateur connecté (à modifier plus tard).
    /*
    init_current_player();
    strcpy(current_player->username, "buzzromain");
    strcpy(current_player->password, "superpassword");
    current_player->nb_win_game = -1;
    mes_login * log = req_login(current_player->username, current_player->password);
    */

    while(choice != 2) {
        system("clear");
        printf("=== Jeu de dame en réseau === \n");
        printf("   === Menu principale ===   \n");
        if(is_connected_player() == 0) {
            printf("1. Se connecter\n");
        }
        else if(is_connected_player() == 1) {
            printf("1. Jouer\n");
        }
        printf("2. Quitter le jeu\n");
        printf("Votre choix : ");
        scanf("%d", &choice);

        if(choice == 1 && is_connected_player() == 0) {
            print_connection_menu();
        }
        else if(choice == 1 && is_connected_player() == 1){
            print_game_menu();
        }
    }
}
