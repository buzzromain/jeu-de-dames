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
* Fonction principale du jeu.
*/
void run_game() {  
    //Ici, on fait plein de choses comme demander à l'utilisateur ce qu'il souhaite faire.
    //...

    //L'utilisateur décide de créer un nouveau compte : on appelle la fonction create_new_account.
    create_new_account();
}