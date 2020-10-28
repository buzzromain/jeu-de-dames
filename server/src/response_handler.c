/*******************************************************
Nom ......... : response_handler.c
Role ........ : Gère les réponse à envoyer au client
Auteur ...... : X
********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "response_handler.h"

void * reply_create_account(char * code) {
    //Construction de la requête vers le serveur 
    char * response = malloc(sizeof(char) * 1024);
    response[0] = '\0';
    strcat(response, "message_type: CREATE_ACCOUNT\n");
    strcat(response, "code: ");
    strcat(response, code);

    return response;
}