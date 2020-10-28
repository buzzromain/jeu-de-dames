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