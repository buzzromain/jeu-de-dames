#ifndef Prototype
#define Prototype

#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MAX_CLIENTS         10

#define BUFFER_SIZE         100
#define MSG_FILE_SIZE 		200

#define TRUE         		1
#define FALSE        		0

#define KEY					"42"

typedef struct
{
	int * socketSpaectator;
	int socketPlayerOne;
	int socketPlayerTwo;
	int ** board;
}Game;

typedef struct
{
   int sock;
}Client;

typedef struct 
{
	long type;
	int socket;
	char text[100];
} m_msg;

/*TCP_serv.c*/
int init_connection(int port);
void send_client(int sock, const char *buffer);
int servTCP(int socketServ,int IdMsgRequest);

/*game.c*/
int ** initBoard( );
void printBoard(int ** tab);
int isVictory(int ** tab);
void mandatoryTake(int ** tab);
int moveQueen(int ** tab,int couleur,int pawnX,int pawnY,int destX,int destY);
int movePawn(int ** tab,int couleur,int pawnX,int pawnY,int destX,int destY);
int move(int ** tab,int couleur,int pawnX,int pawnY,int destX,int destY);
void convertQueen(int ** tab);

/*handler.c*/
int handler(int IdMsgRequest);

#endif 


