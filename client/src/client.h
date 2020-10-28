#ifndef client_h
#define client_h

/*
    Paramètre du client
*/

//Port du serveur
#define PORT 8888

//Taille du buffer du descripteur de fichier.
#define BUFFER_SIZE 1025

//Nombre d'essai de reconnexion
#define MAX_RETRY 10

void close_client();
void sendToServer(void * request);
void * recvFromServer();
void * request(void * request);
int init_client();

#endif /* client_h */
