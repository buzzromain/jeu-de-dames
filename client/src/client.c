/*******************************************************
Nom ......... : client.c
Role ........ : Gère la connexion au serveur
Auteur ...... : X
********************************************************/

#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "client.h"

/**
* Descripteur de fichier de la socket.
*/
static int sockfd;

/**
* Ferme la socket.
*/
void close_client() {
    //Fermeture de la socket
	close(sockfd);
}

/**
* Effectue une requête au serveur.
* 
* \param request une requête
*/
void sendToServer(void * request) {
    //Envoie de la requête vers le serveur.
    if(send(sockfd, request, strlen(request), 0) == -1) {
        perror("Error sending data to server.");
        exit(EXIT_FAILURE);
    }
}

/**
* Recupère la réponse à la requête.
* 
* \return réponse du serveur.
*/
void * recvFromServer() {
    char * response = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    //Recoit des données depuis le serveur.
    if(recv(sockfd, response, BUFFER_SIZE, 0) < 0) {
        perror("Error receiving data from server.");
        exit(EXIT_FAILURE);
    }
    return response;
}


/**
* Effectue une requête au serveur et attend une réponse
* 
* \param request une requête
* \return une réponse
*/
void * request(void * request) {
    sendToServer(request);
    return recvFromServer();
}

/**
* Initialise le client.
*
* \return 0 si la connexion à réussi, -1 sinon.
*/
int init_client() {
    //Structure adresse du serveur.
	struct sockaddr_in address;

	//Creation d'une socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1) {
		perror("Error creating socket ");
		return -1;
	}

    //Initialise la structure adresse du serveur.
    bzero(&address, sizeof(address));

    //IPv4
	address.sin_family = AF_INET;

    //Adresse localhost
	address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    //Port
	address.sin_port = htons(PORT);

	//Connexion au serveur.
	if(connect(sockfd, (struct sockaddr*)&address, sizeof(address)) != 0) {
		perror("Error connecting to server ");
		return -1;
    }
    
    //Connexion réussi au serveur.
	printf("Connected to the server.\n");
    return 0;
}