/*******************************************************
Nom ......... : db.c
Role ........ : Contient les fonctions pour gérer 
la base de données utilisateur.
Auteur ...... : X
********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "db.h"

/**
* Verifie si un utilisateur existe dans la base de données
* 
* \param username nom d'utilisateur
* \return 1 si l'utilisateur existe, 0 si l'utilisateur n'existe pas.
*/
int is_user_exist(char * username) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(DB_PATH, "r");
    if(fp == NULL) {
        return 0;
    }

    int i = 0;
    int is_found = 0;
    char * db_username = malloc(sizeof(char) * 255);

    //On parcourt toutes les lignes jusqu'à que l'on trouve le nom d'utilisateur
    while((read = getline(&line, &len, fp)) != -1 && is_found == 0) {
        char * token = strtok(line, ",");

        while(token != NULL) {
            //Nom d'utilisateur est en deuxième position
            if(i == 1) { 
                strcpy(db_username, token);
            }

            //Si on a trouvé le nom d'utilisateur dans la base de données.
            if(strcmp(username, db_username) == 0) {
                is_found = 1;
            }

            token = strtok(NULL, ",");
            i++;
        }
        i = 0;
    }

    //Liberation de la mémoire.
    free(db_username);

    fclose(fp);
    if(is_found == 1) {
        return 1;
    }
    else {
        return 0;
    }
}

/**
* Enregistre un nouvelle utilisateur dans la base de données.
* 
* \param username nom d'utilisateur
* \param password mot de passe utilisateur
* \return id de l'utilisateur, null si une erreur est survenu
*/
void * db_login_user(char * username, char * password) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(DB_PATH, "r");
    if(fp == NULL) {
        return NULL;
    }

    char * tmp_id = malloc(sizeof(char) * 4);
    char * id = malloc(sizeof(char) * 4);
    char * db_username = malloc(sizeof(char) * 255);
    char * db_password = malloc(sizeof(char) * 255);
    int i = 0;
    int is_found = 0;

    //On parcourt toutes les lignes jusqu'à que l'on trouve le nom d'utilisateur
    while((read = getline(&line, &len, fp)) != -1 && is_found == 0) {
        char * token = strtok(line, ",");

        while(token != NULL) {
            if(i == 0) {
                strcpy(tmp_id, token);
            }
            //Nom d'utilisateur est en deuxième position
            if(i == 1) { 
                strcpy(db_username, token);
            }

            //Mot de passe est en troisième position
            else if(i == 2) {
                strcpy(db_password, token);
            }

            //Si on a trouvé le nom d'utilisateur dans la base de données.
            if(strcmp(username, db_username) == 0) {
                //On verifie si il s'agit du bon mot de passe.
                if(strcmp(password, db_password) == 0) {
                    strcpy(id, tmp_id);
                    is_found = 1;
                }
            }
            token = strtok(NULL, ",");
            i++;
        }
        i = 0;
    }

    //Libération de la mémoire.
    fclose(fp);
    if(line) {
        free(line);
    }

    free(tmp_id);
    free(db_username);
    free(db_password);
    
    //On renvoie l'id l'utilisateur est bien authentifié.
    if(is_found == 1) {
        return id;
    } 
    else {
        return NULL;
    }
}

/**
* Enregistre un nouvelle utilisateur dans la base de données.
* 
* \param username nom d'utilisateur
* \param password mot de passe utilisateur 
* \return l'id de l'utilisateur enregistré, null si une erreur est survenu.
*/
void * db_register_new_user(char * username, char * password) {
    srand(time(NULL)); 
    /*
    TODO : Gestion des erreurs.
    Verifier que l'utilisateur n'existe pas en parcourant la base de données.
    */
    //Ouverture du fichier
    FILE * fp;
    fp = fopen(DB_PATH, "a+");
    if(fp == NULL) {
        return NULL;
    }

    //Si l'utilisateur n'existe pas déjà
    if(is_user_exist(username) == 0) {
        //Ajoute dans la base de données un nouvel utilisateur
        char * id = malloc(sizeof(char) * 4);
        sprintf(id, "%d", rand() % 1000); 
        fputs(id, fp);
        fputs(",", fp);

        //Nom d'utilisateur.
        fputs(username, fp);
        fputs(",", fp);

        //Mot de passe.
        fputs(password, fp);
        fputs(",", fp);

        //Nombre de parties gagné.
        fputs("0", fp);

        fputs("\n", fp);
        fclose(fp);

        return id;
    }
    else {
        fclose(fp);
        return NULL;
    }
}

/**
* Obtenir le nom d'utilisateur à partir de l'id utilisateur
* 
* \param id l'identifiant de l'utilisateur
* \return le nom d'utilisateur, null si une erreur est survenue.
*/
char * get_username_by_id(char * id) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(DB_PATH, "r");
    if(fp == NULL) {
        return 0;
    }

    int i = 0;
    int is_found = 0;
    char * db_username = malloc(sizeof(char) * 255);
    char * db_id = malloc(sizeof(char) * 255);

    //On parcourt toutes les lignes jusqu'à que l'on trouve l'identifiant de l'utilisateur
    while((read = getline(&line, &len, fp)) != -1 && is_found == 0) {
        char * token = strtok(line, ",");

        while(token != NULL) {
            //Nom d'utilisateur est en deuxième position
            if(i == 0) { 
                strcpy(db_id, token);
            }

            //Nom d'utilisateur est en deuxième position
            if(i == 1) { 
                strcpy(db_username, token);
            }

            //Si on a trouvé le nom d'utilisateur dans la base de données.
            if(strcmp(id, db_id) == 0) {
                is_found = 1;
            }

            token = strtok(NULL, ",");
            i++;
        }
        i = 0;
    }

    //Liberation de la mémoire.
    free(db_id);

    fclose(fp);
    if(is_found == 1) {
        return db_username;
    }
    else {
        return NULL;
    }
}

/**
* Obtenir le nombre de parties gagnés
* 
* \param id l'identifiant de l'utilisateur
* \return le nombre de parties gagné, -1 si une erreur est survenues
*/
int get_number_won_game_by_id(char * id) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(DB_PATH, "r");
    if(fp == NULL) {
        return 0;
    }

    int i = 0;
    int is_found = 0;
    int nb_won_game = 0;
    char * db_id = malloc(sizeof(char) * 255);

    //On parcourt toutes les lignes jusqu'à que l'on trouve l'identifiant de l'utilisateur
    while((read = getline(&line, &len, fp)) != -1 && is_found == 0) {
        char * token = strtok(line, ",");

        while(token != NULL) {
            //Id est en premiere position
            if(i == 0) { 
                strcpy(db_id, token);
            }

            //Nombre de parties gagné
            else if(i == 3) {
                nb_won_game = atoi(token);
            }

            //Si on a trouvé l'utilisateur dans la base de données.
            if(strcmp(id, db_id) == 0) {
                is_found = 1;
            }

            token = strtok(NULL, ",");
            i++;
        }
        i = 0;
    }

    //Liberation de la mémoire.
    free(db_id);

    fclose(fp);
    if(is_found == 1) {
        return nb_won_game;
    }
    else {
        return -1;
    }
}