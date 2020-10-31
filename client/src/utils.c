/*******************************************************
Nom ......... : utils.c
Role ........ : Contient un ensemble de petites fonctions
Auteur ...... : X
********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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