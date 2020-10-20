#ifndef server_h
#define server_h

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

#endif /* server_h */
