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

/*
TODO : 
    -Modifier la fonction pour quelles prennent en paramètre un tableau 
    2D et non un pointeur vers le jeu.
*/

/**
* Affiche le plateau de jeu.
*
* \param current_game une partie
*/
void print_board(game * current_game) {
    system("clear");
    printf("    1    2     3    4    5    6    7    8    9   10\n");
    printf("   ─────────────────────────────────────────────────\n");
    for(int j = 0; j < NB_COLUMNS; j++) {
        printf("%c ┃ ", int_to_ascii(17 + j));
        for(int i = 0; i < NB_LINES; i++) {
            if(current_game->board[i][j] == 1) {
                print_black_draughts_man();
            }
            else if(current_game->board[i][j] == -1) {
                print_white_draughts_man();
            }
            else if(current_game->board[i][j] == 2) {
                print_black_draughts_king();
            }
            else if(current_game->board[i][j] == -2) {
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
    //Ici, on demande à l'utilisateur de saisir un pseudo et un mot de passe.
    //...

    /*
    Appelle la fonction req_create_account qui effectue une requête au serveur.
    On lui passe simplement en paramètre le pseudo et le mot de passe.
    Elle renvoie une structure de données que l'on va manipuler pour savoir si la requête a bien réussi.
    */
    mes_create_account * res = req_create_account("buzzromain", "superpassword");

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
    else {
        //L'utilisateur existe déjà.
        printf("Impossible de créer un compte. Ce compte existe déjà !\n");
    }

}

/**
* Demarre une nouvelle partie.
* Ceci est une démo, toutes les fonctionnalités n'ont pas été implementés.
*/
void start_game() {
    printf("Lancement du plateau de jeu...\n");
    //Initialise le plateau de jeu.
    init_game();
    mes_start_game * res = req_start_game("buzzromain", "superpassword", "1");
    if(strcmp(res->code, "OK") == 0) {
        //Affiche ici le plateau de jeu en appelant la fonction pour afficher le plateau de jeu (fonction à importer plus tard).
        //...
        current_game->board = res->board;
        print_board(current_game);
    }
    else {
        //Si on a pas réussi à afficher le plateau de jeu, on affiche un message à l'utilisateur;
        printf("Oups, impossible de récupérer le plateau de jeu");
    }

}

/**
* Initialise le plateau de jeu.
*/
void init_game() {
    current_game = malloc(sizeof(game));
}

/**
* Fonction principale du jeu.
*/
void run_game() {  
    //Ici, on fait plein de choses comme demander à l'utilisateur ce qu'il souhaite faire.
    //...

    //L'utilisateur décide de créer un nouveau compte : on appelle la fonction create_new_account.
    //create_new_account();

    //L'utilisateur décide de lancer une nouvelle partie.
    start_game();
}
