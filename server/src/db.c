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
int db_is_user_exist(char * username) {
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
int get_nb_won_game_by_id(char * id) {
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

/**
* Met à jour le nombre de parties gagné
* 
* \param id l'identifiant de l'utilisateur
* \param new_nb_won_game le nouveau nombre de parties gagné.
* \return 0 si l'opération à reussi, -1 si une erreur est survenue.
*/
/*
int update_nb_won_game(char * id, int new_nb_won_game) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(DB_PATH, "r+");
    if(fp == NULL) {
        return 0;
    }

    int i = 0;
    int is_found = 0;

    int last_row_size = 0;
    char * db_id = malloc(sizeof(char) * 255);
    char * db_username = malloc(sizeof(char) * 255);
    char * db_password = malloc(sizeof(char) * 255);

    //On parcourt toutes les lignes jusqu'à que l'on trouve l'identifiant de l'utilisateur
    while((read = getline(&line, &len, fp)) != -1 && is_found == 0) {
        char * token = strtok(line, ",");

        while(token != NULL) {
            //Id est en premiere position
            if(i == 0) { 
                strcpy(db_id, token);
            }

            //Nom d'utilisateur est en deuxième position
            else if(i == 1) {
                strcpy(db_id, token);
            }

            //Mot de passe est en troisieme position
            else if(i == 2) {
                strcpy(db_password, token);
            }

            //Mot de passe est en troisieme position
            else if(i == 3) {
                last_row_size = strlen(token);
            }


            //Si on a trouvé l'utilisateur dans la base de données.
            if(strcmp(id, db_id) == 0) {
                is_found = 1;
                fseek(fp, ftell(fp) + (last_row_size - 1), SEEK_CUR);
                char * tmp = malloc(sizeof(char) * 10);
                sprintf(tmp, "%d", new_nb_won_game);
                fprintf(fp, "%s", tmp);
                free(tmp);
            }

            token = strtok(NULL, ",");
            i++;
        }
        i = 0;
    }


    fclose(fp);
    if(is_found == 1) {
        return 0;
    }
    else {
        return -1;
    }
}
*/


/**
* Enregistre un nouvelle utilisateur dans la base de données.
* 
* \param username nom d'utilisateur
* \param password mot de passe utilisateur
* \return structure contenant toutes les informations sur l'utilisateur, null si erreur.
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

    char * id = malloc(sizeof(char) * 4);
    char * db_username = malloc(sizeof(char) * 255);
    char * db_password = malloc(sizeof(char) * 255);
    int nb_won_game = 0;

    int i = 0;
    int is_found = 0;

    //On parcourt toutes les lignes jusqu'à que l'on trouve le nom d'utilisateur
    while((read = getline(&line, &len, fp)) != -1 && is_found == 0) {
        char * token = strtok(line, ",");

        while(token != NULL) {
            //Id est en première position
            if(i == 0) {
                strcpy(id, token);
            }
            //Nom d'utilisateur est en deuxième position
            if(i == 1) { 
                strcpy(db_username, token);
            }

            //Mot de passe est en troisième position
            if(i == 2) {
                strcpy(db_password, token);
            }

            //Nombre de parties gagnés est en troisième position
            if(i == 3) {
                nb_won_game = atoi(token);
            }

            //Si on a trouvé le nom d'utilisateur dans la base de données.
            if(strcmp(username, db_username) == 0) {
                //On verifie si il s'agit du bon mot de passe.
                if(strcmp(password, db_password) == 0) {
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

    
    //On renvoie l'id l'utilisateur est bien authentifié.
    if(is_found == 1) {
        db_user * user = malloc(sizeof(db_user));
        user->id = id;
        user->username = db_username;
        user->password = db_password;
        user->nb_won_game = nb_won_game;
        return user;
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
* \return structure contenant toutes les informations sur l'utilisateur, null si erreur.
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
    if(db_is_user_exist(username) == 0) {
        char * db_id = malloc(sizeof(char) * 4);
        char * db_username = malloc(sizeof(char) * 255);
        char * db_password = malloc(sizeof(char) * 255);
        int nb_won_game = 0;

        //Ajoute dans la base de données un nouvel utilisateur

        //Id
        sprintf(db_id, "%d", rand() % 1000); 
        fputs(db_id, fp);
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

        db_user * user = malloc(sizeof(user));
        user->id = db_id;
        user->username = db_username;
        user->password = db_password;
        user->nb_won_game = nb_won_game;
        return user;
    }
    else {
        fclose(fp);
        return NULL;
    }
}

