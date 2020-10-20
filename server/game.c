#include "game.h"

//Juste une fonction pour tester.
void test_function(char * response) 
{
    //Fait plein de choses.

    //Copie une réponse pour le client à la fin de chaque fonction.
    strcpy(response, "Fonction de test 1 !\n");
}

//Plein de fonctions ici...


char * handle_request(char * request, int request_size) 
{
    char * response = (char *)malloc(sizeof(char) * RESPONSE_SIZE);

    //Message de bienvenue
    strcpy(response, "Bienvenue sur le serveur de Jeu de Dames !\n");

    //Si la requête est "test" alors on appelle la fonction de test.
    if(strcmp("test", request) == 0) 
    {
        test_function(response);
    }
    //Plein de if..else ici pour gérer toutes les requêtes du client.

    //Renvoie la réponse au client.
    return response;
}