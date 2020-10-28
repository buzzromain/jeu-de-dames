#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "client.h"
#include "game.h"
#include "connector.h"

int main() {    
    //Initialise le client pour pouvoir effectuer des requête au serveur.
    int connected = init_client();
    int retry = 0;

    //Essaie de se connecter au serveur si la connexion a echoué.
    while(connected == -1 && retry < MAX_RETRY) {
        printf("Try to connect to the server again...\n\n");
        sleep(3);
        connected = init_client();
        retry++;
    }

    if(retry >= MAX_RETRY) {
        printf("Cannot connect to server.\n\n");
        exit(EXIT_FAILURE);
    }

    //Demarre le jeu.
    run_game();

    //Fermeture du client.
    close_client();

    //Quitte le programme.
    exit(EXIT_SUCCESS);
}