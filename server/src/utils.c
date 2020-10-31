/*******************************************************
Nom ......... : utils.c
Role ........ : Contient toutes les fonctions utilitaires
dont les autres fonctions du serveur ont besoin
Auteur ...... : X
********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

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
* Transforme en chaîne de caractères un plateau de jeu
* pour l'envoi du plateau de jeu au client.
* 
* \param board plateau de jeu
* \return plateau de jeu en chaîne de caractères
*/
void * stringify_board(int ** board) {
    char * tmp = malloc(sizeof(char) * 3);
    tmp[0] = '\0';

    char * stringify_board = malloc(sizeof(char) * 200);
    stringify_board[0] = '\0';

    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            sprintf(tmp, "%d,", board[i][j]);
            strcat(stringify_board, tmp);
        }
    }
    stringify_board[strlen(stringify_board) - 1] = '\0';

    free(tmp);

    return stringify_board;
}