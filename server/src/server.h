#ifndef server_h
#define server_h

/*
    Paramètre du serveur
*/

//Port du serveur
#define PORT 8888

//Nombre de clients maximum
#define MAX_CLIENT 30

//Taille du buffer des descripteurs de fichier.
#define BUFFER_SIZE 1025

int * init_client_socket();
void init_server();

#endif /* server_h */
