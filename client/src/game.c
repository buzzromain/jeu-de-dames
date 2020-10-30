/*******************************************************
Nom ......... : game.c
Role ........ : Gère la logique du jeu.
Auteur ...... : X
********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"


/**
* Fonction relatives à l'affichage du jeu
*/

/**
* Permet de renvoyer un caractères ASCII en prenant un nombre en paramètre
* 
* \param nombre un nombre à convertir en ASCII
* \return un caractère ASCII
*/
int int_to_ascii(int number) {
   return '0' + number;
}

/**
* Met le texte de la console en bleu.
*/
void blue_text_color() {
    printf("\033[0;34m");
}

/**
* Met le texte de la console en bleu.
*/
void red_text_color() {
    printf("\033[1;31m");
}

/**
* Met le texte de la console en couleur par défaut.
*/
void reset_text_color() {
    printf("\033[0m");
}

/**
* Affiche un pion blanc
*/
void print_white_draughts_man() {
    red_text_color();
    printf("%s ", "\u2B24");
    reset_text_color();
}

/**
* Affiche une dame blanche
*/
void print_white_draughts_king() {
    red_text_color();
    printf("%s ", "\u24C6");
    reset_text_color();
}

/**
* Affiche un pion noir
*/
void print_black_draughts_man() {
    blue_text_color();
    printf("%s ", "\u2B24");
    reset_text_color();
}

/**
* Affiche une dame noire
*/
void print_black_draughts_king() {
    blue_text_color();
    printf("%s ", "\u24C6");
    reset_text_color();
}

/**
* Parse une position saisit par l'utilisateur
*
* \param position une position à parser
* \return tableau de la position
*/
int * parse_position(char * stringify_position) {
    int * position = (int *)malloc(sizeof(int) * 2);
    /*
    Recupère position sous forme de tableau
    */
    if(stringify_position[0] == 'A') {
        position[1] = 0;
        position[0] = atoi(&stringify_position[1]) - 1;
    }  
    else if(stringify_position[0] == 'B') {
        position[1] = 1;
        position[0] = atoi(&stringify_position[1]) - 1;
    }  
    else if(stringify_position[0] == 'C') {
        position[1] = 2;
        position[0] = atoi(&stringify_position[1]) - 1;
    }  
    else if(stringify_position[0] == 'D') {
        position[1] = 3;
        position[0] = atoi(&stringify_position[1]) - 1;
    }  
    else if(stringify_position[0] == 'E') {
        position[1] = 4;
        position[0] = atoi(&stringify_position[1]) - 1;
    }  
    else if(stringify_position[0] == 'F') {
        position[1] = 5;
        position[0] = atoi(&stringify_position[1]) - 1;
    }  
    else if(stringify_position[0] == 'G') {
        position[1] = 6;
        position[0] = atoi(&stringify_position[1]) - 1;
    }  
    else if(stringify_position[0] == 'H') {
        position[1] = 7;
        position[0] = atoi(&stringify_position[1]) - 1;
    }  
    else if(stringify_position[0] == 'I') {
        position[1] = 8;
        position[0] = atoi(&stringify_position[1]) - 1;
    }  
    else if(stringify_position[0] == 'J') {
        position[1] = 9;
        position[0] = atoi(&stringify_position[1]) - 1;
    }  
    return position;
}

/**
* Parse les positions saisit par l'utilisateur.
* A faire : gestion des erreurs (très important).
*
* \param user_input positions saisit par l'utilisateur
* \return tableau de positions (initiale et nouvelle position)
*/

int ** get_positions_by_parsing_user_input(char * user_input) {
    int ** positions = (int **)malloc(sizeof(int *) * 2);

    /*
    Parse la chaîne de caractères pour récuperer position saisit 
    par l'utilisateur.
    */
    char *first_pos, *sec_pos;
    first_pos = strtok(user_input, "->");
    sec_pos = strtok(NULL, "->");

    positions[0] = parse_position(first_pos);
    positions[1] = parse_position(sec_pos);

    return positions;
}

/*
TODO : 
    -Modifier la fonction pour quelles prennent en paramètre un tableau 
    2D et non un pointeur vers le jeu.
*/

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
    Par exemple on peut vérifie que la création du code s'est bien déroulé, 
    en testant si le code de retour est "OK".
    */
    if(strcmp(res->code, "OK") == 0) {
        /*
        Si le code de retour est bon alors, on fait des actions comme actualiser une donnée dans le programme
        et affiche un message à l'utilisateur pour le prevenir que l'opération s'est bien déroulé.
        */
       printf("Compte créé avec succès !\n");
    }
    else if(strcmp(res->code, "USER_ALREADY_EXIST") == 0) {
        //L'utilisateur existe déjà.
        printf("Impossible de créer un compte. Ce compte existe déjà !\n");
    }
    else {
        printf("Une erreur du serveur est survenu\n");
    }

    current_user->username = username;
    current_user->password = password;
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
    Par exemple on peut vérifie que la création du code s'est bien déroulé, 
    en testant si le code de retour est "OK".
    */
    if(strcmp(res->code, "OK") == 0) {
        /*
        Si le code de retour est bon alors, on fait des actions comme actualiser une donnée dans le programme
        et affiche un message à l'utilisateur pour le prevenir que l'opération s'est bien déroulé.
        */
       printf("Connexion avec succès !\n");
    }
    else if(strcmp(res->code, "INVALID_LOGIN") == 0) {
        //L'utilisateur existe déjà.
        printf("Impossible de se connecter au compte. Les identifiants sont invalides.\n");
    }
    else {
        printf("Une erreur du serveur est survenu\n");
    }

    current_user->username = username;
    current_user->password = password;
}

/**
* Deconnexion de l'utilisateur
*/
void disconnect() {
    if(current_user->username != NULL) {
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
            mes_disconnect * res = req_disconnect(current_user->username, current_user->password);
            /*
            Par exemple on peut vérifie que la création du code s'est bien déroulé, 
            en testant si le code de retour est "OK".
            */
            if(strcmp(res->code, "OK") == 0) {
                /*
                Si le code de retour est bon alors, on fait des actions comme actualiser une donnée dans le programme
                et affiche un message à l'utilisateur pour le prevenir que l'opération s'est bien déroulé.
                */
            printf("Deconnexion avec succès !\n");
            }
            else if(strcmp(res->code, "INVALID_LOGIN") == 0) {
                //L'utilisateur existe déjà.
                printf("Impossible de se deconnecter au compte. Les identifiants sont invalides.\n");
            }
            else {
                printf("Une erreur du serveur est survenu\n");
            }

            free(current_user->username);
            free(current_user->password);
            current_user->username = NULL;
            current_user->password = NULL;
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
* Demarre une nouvelle partie.
* Ceci est une démo, toutes les fonctionnalités n'ont pas été implementés.
*/
void start_game() {
    //Le numero de la partie codé en dur (à changer plus tard)
    char * game_id = "1";
    printf("Lancement du plateau de jeu...\n");
    mes_start_game * res = req_start_game(current_user->username, current_user->password, game_id);
    if(strcmp(res->code, "OK") == 0) {
        //Affiche ici le plateau de jeu en appelant la fonction pour afficher le plateau de jeu (fonction à importer plus tard).
        current_game->board = res->board;
        char * user_input = malloc(sizeof(char) * 6);
        int ** positions;
        int * initial_position;
        int * new_position;
        mes_move_game * upd;

        while(strcmp(user_input, "exit") != 0) {
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
                    upd = req_move_game(current_user->username, current_user->password, game_id, initial_position, new_position);

                    //On vérifie si la requête à la demande à réussit.
                    if(strcmp(upd->code, "OK") == 0) {
                        //Si la requête a réussit, on actualise le plateau de jeu.
                        free(current_game->board);
                        current_game->board = upd->board;
                    }
                    else {
                      
                        /*
                        Problème à regler ici.
                        Ce message ne s'affichera jamais à cause de l'instruction
                        system('clear') dans la fonction d'affichage du jeu.
                        */
                        printf("Oups... Probleme");
                    }
                }

                //Libère la mémoire.
                free(initial_position);
                free(new_position);
                free(positions);
                free(upd);
            }
        }
        free(user_input);
    }
    else {
        //Si on a pas réussi à afficher le plateau de jeu, on affiche un message à l'utilisateur;
        printf("Oups, impossible de récupérer le plateau de jeu.\n");
    }
}

/**
* Initialise le jeu.
*/
void init_game() {
    current_game = malloc(sizeof(game));
    current_user = malloc(sizeof(user));
    current_user->username = NULL;
    current_user->password = NULL;
}

/**
* Fonction principale du jeu.
*/
void run_game() {  
    //Initialise le jeu.
    init_game();

    int choice = 0;
    /*
    Pour tester les fonctions, à changer plus tard.
    En effet, l'utilisateur doit pouvoir choisir seulement entre 
    se connecter ou creer un compte lors de l'affichage du première écran du jeu.
    */
    system("clear");
    printf("=== Jeu de dame en réseau === \n");
    printf("   === Menu ===   \n");
    printf("1. Créer un compte.\n");
    printf("2. Se connecter\n");
    printf("3. Se deconnecter\n");
    printf("4. Rejoindre une partie\n");
    printf("Votre choix : ");

    while(choice < 1 || choice > 4) {
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
            //L'utilisateur décide de se deconnecter de son compte.
            disconnect();
        }
        else if(choice == 4){
            //L'utilisateur décide de lancer une nouvelle partie.

            
            //On connecte l'utilisateur manuellement (à enlever plus tard, voir commentaire plus haut)
            current_user->username = malloc(sizeof(char) * 255);
            current_user->password = malloc(sizeof(char) * 255);
            strcpy(current_user->username, "buzzromain");
            strcpy(current_user->password, "superpassword");
            
            /*
            Ceci est demo, on ne peut qu'afficher le plateau de jeu et déplacer
            des pions sans tenir compte des règles et sans adversaire.
            */

            start_game();
        }
    }
}
