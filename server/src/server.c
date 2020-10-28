#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "server.h"
#include "request_handler.h"

/**
* Intialise tableau de descripteur de fichier de socket
* 
* \return tableau de descripteur de fichier de sockets.
*/
int * init_client_socket()
{
    int * client_socket = (int *)malloc(sizeof(int) * MAX_CLIENT);
    for(int i = 0; i < MAX_CLIENT; i++) 
    {
        client_socket[i] = 0;
    }
    return client_socket;
}

/**
* Initialise le serveur.
*/
void init_server() {    
    //Contient une nouvelle socket (temp).
    int new_socket;

    //Contient le descripteur de fichier courant (temp).
    int sockfd;

    //Contient valeur booléenne qui indique si un descripteur de fichier est prêt.
    int ready;

    //Socket principale du programme.
    int sock; 

    //Option de la socket.
    int opt = 1;

    //Structure d'une adresse du serveur.
    struct sockaddr_in address;

    //Taille en octets d'une structure sockaddr_in.
    int addrlen;
     
    //Ensemble de descripteurs de fichiers de socket prêt.
    fd_set readfds;

    //Index maximale de l'ensemble de descripteur de fichier.
    int max_sockfd;

    //Index du dernier caractère lu 
    int char_read;

    //Initialise le tableau de socket pour chaque client.
    int * client_socket = init_client_socket();

    //Buffer pour les requêtes.
    char * request = (char *)malloc(sizeof(char) * BUFFER_SIZE);
           
    //Création d'une socket principale qui attend de nouvelles connexions.
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    {
        perror("Error creating socket.");
        exit(EXIT_FAILURE);
    }
 
    //Permet à une socket d'accepter plusieurs connexions.
    if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
 
    //Initialise la structure adresse pour le socket.
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
     
    //Lie le socket à la structure adresse.
    if(bind(sock, (struct sockaddr *)&address, sizeof(address))<0) 
    {
        perror("Error binding socket to address");
        exit(EXIT_FAILURE);
    }
    
    //Permet à la socket principale d'accepter 3 connexions simultanée.
    if(listen(sock, 3) < 0)
    {
        perror("Error listening on socket.");
        exit(EXIT_FAILURE);
    }

    printf("Listening on port %d.\n", PORT);

    addrlen = sizeof(address);
    printf("Waiting for connection...\n\n");
    
    //En attente d'évenement.
    while(1) 
    {
        //Efface l'ensemble de socket.
        FD_ZERO(&readfds);
 
        //Ajoute la socket principale du serveur à l'ensemble de socket client.
        FD_SET(sock, &readfds);
        max_sockfd = sock;
        
        //Ajoute des socket client à l'ensemble de socket.
        for(int i = 0; i < MAX_CLIENT; i++) 
        {
            sockfd = client_socket[i];
            
            //Vérifie si aucune erreur sur le descripteur de fichier.
            if(sockfd > 0)
            {
                FD_SET(sockfd, &readfds);
            }

            //Trouve l'index du plus grand descripteur de fichier.
            if(sockfd > max_sockfd)
            {
                max_sockfd = sockfd;
            }
        }
 
        //Attends indefiniment un descripteur de fichier prêt à la lecture/écriture.
        ready = select(max_sockfd + 1, &readfds, NULL, NULL, NULL);
   
        if((ready < 0) && (errno!=EINTR)) 
        {
            printf("Error while waiting for a ready file descriptor.");
        }
         
        /*
        Verifie si le socket principale est présent dans l'ensemble de socket
        Si la socket principale est présente, cela signifie qu'il y a une écriture dans cette socket, 
        et donc qu'un nouveau client souhaite se connecter.
        */
        if(FD_ISSET(sock, &readfds)) 
        {
            //Création d'une nouvelle socket.
            if((new_socket = accept(sock, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
            {
                perror("Error when accepting new connection.");
                exit(EXIT_FAILURE);
            }
         
            printf("Host connected : %s:%d \n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
             
            //Ajoute de la nouvelle socket au tableau de socket client.
            for(int i = 0; i < MAX_CLIENT; i++) 
            {
                //Cherche une case égale à 0 pour ajouter la nouvelle socket.
                if(client_socket[i] == 0)
                {
                    client_socket[i] = new_socket;                  
                    break;
                }
            }
        }
         
        //Itere sur toutes les socket client.
        for(int i = 0; i < MAX_CLIENT; i++) 
        {
            sockfd = client_socket[i];
             
            /*
            Verifie si la socket client est présent dans l'ensemble de socket
            Si celle-ci est présente, cela signifie qu'il y a une écriture dans cette socket, 
            et donc qu'un client à envoyer une requête au serveur.
            */
            if(FD_ISSET(sockfd, &readfds)) 
            {
                //Verifie si le client souhaite se deconnecter du serveur.
                if((char_read = read(sockfd, request, 1024)) == 0)
                {
                    getpeername(sockfd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
                    printf("Host disconnected : %s:%d \n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
                     
                    //Ferme le descripteur de fichier de la socket.
                    close(sockfd);

                    //Libère la socket dans le tableau de socket client.
                    client_socket[i] = 0;
                }
                 
                //Réponse du serveur au client.
                else
                {
                    request[char_read] = '\0';
                    char * response = handle_request(request);
                    send(sockfd, response, strlen(response), 0);
                }
            }
        }
    }
}