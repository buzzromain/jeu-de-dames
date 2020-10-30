/*******************************************************
Nom ......... : connector_utils.c
Role ........ : Contient toutes les fonctions utilitaires
pour les fonctions de connector.c
Auteur ...... : X
********************************************************/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "connector_utils.h"

/**
* Parse une chaîne de caractère correspondant au plateau
* de jeu reçu par le programme depuis le serveur en plateau de jeu sous forme
* de tableau d'entier manipulable par le programme.
*
* \param stringify_board le plateau de jeu sous forme de chaîne de caractères
* \return un tableau representant le plateau de jeu.
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

/**
* Transforme une position sous forme de tableau en position
* sous forme de chaîne de caractère envoyable au serveur.
*
* \param position un tableau contenant une position [y, x]
* \return une position sous forme de chaîne de caractères
*/
char * stringify_position(int * position) {
    char * stringify_position = malloc(sizeof(char) * 2);
    char * tmp = malloc(sizeof(char));

    if(position[1] == 0) {
        strcat(stringify_position, "A");
        sprintf(tmp, "%d", position[0] + 1);
        strcat(stringify_position, tmp);
        tmp[0] = '\0';
    }
    else if(position[1] == 1) {
        strcat(stringify_position, "B");
        sprintf(tmp, "%d", position[0] + 1);
        strcat(stringify_position, tmp);
        tmp[0] = '\0';
    }
    else if(position[1] == 2) {
        strcat(stringify_position, "C");
        sprintf(tmp, "%d", position[0] + 1);
        strcat(stringify_position, tmp);
        tmp[0] = '\0';
    }
    else if(position[1] == 3) {
        strcat(stringify_position, "D");
        sprintf(tmp, "%d", position[0] + 1);
        strcat(stringify_position, tmp);
        tmp[0] = '\0';
    }
    else if(position[1] == 4) {
        strcat(stringify_position, "E");
        sprintf(tmp, "%d", position[0] + 1);
        strcat(stringify_position, tmp);
        tmp[0] = '\0';
    }
    else if(position[1] == 5) {
        strcat(stringify_position, "F");
        sprintf(tmp, "%d", position[0] + 1);
        strcat(stringify_position, tmp);
        tmp[0] = '\0';
    }
    else if(position[1] == 6) {
        strcat(stringify_position, "G");
        sprintf(tmp, "%d", position[0] + 1);
        strcat(stringify_position, tmp);
        tmp[0] = '\0';
    }
    else if(position[1] == 7) {
        strcat(stringify_position, "H");
        sprintf(tmp, "%d", position[0] + 1);
        strcat(stringify_position, tmp);
        tmp[0] = '\0';
    }
    else if(position[1] == 8) {
        strcat(stringify_position, "I");
        sprintf(tmp, "%d", position[0] + 1);
        strcat(stringify_position, tmp);
        tmp[0] = '\0';
    }
    else if(position[1] == 9) {
        strcat(stringify_position, "J");
        sprintf(tmp, "%d", position[0] + 1);
        strcat(stringify_position, tmp);
        tmp[0] = '\0';
    }
    free(tmp);
    return stringify_position;
}