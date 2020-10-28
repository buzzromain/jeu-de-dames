 
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BUFFER_SIZE     100

int  clientTcp(int port){
    int sock;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    
    if(sock == -1){
        perror("\n\x1b[31m[Error]: socket() failed: \x1b[0m");
        exit(errno);
    }
    
	struct sockaddr_in sin;

	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);

    for (int i=0; i<8; i++) {
        sin.sin_zero[i] = 0;
    }
    
    if(connect(sock,(struct sockaddr *) &sin, sizeof(struct sockaddr)) == -1){
        perror("\n\x1b[31m[Error]: connect() failed:  \x1b[0m");
        exit(errno);
    }

    return sock;

}

static void end_connection(int sock)
{
   close(sock);
}

static int read_server(int sock, char *buffer)
{
   int n = 0;

   if((n = recv(sock, buffer, BUFFER_SIZE - 1, 0)) < 0)
   {
      perror("recv()");
      exit(errno);
   }

   buffer[n] = 0;

   return n;
}

static void write_server(int sock, const char *buffer)
{
   if(send(sock, buffer, strlen(buffer), 0) < 0)
   {
      perror("send()");
      exit(errno);
   }
}

int main(){
	
    char buffer[BUFFER_SIZE];

    int sock = clientTcp(1234);

    while(1){

        fgets(buffer, BUFFER_SIZE - 1, stdin);
        {

               /* fclean */
               buffer[BUFFER_SIZE - 1] = 0;
            
        }
        write_server(sock, buffer);

/*
        int n = read_server(sock, buffer);
        if(n == 0)
        {
            printf("Server disconnected !\n");
            break;
        }
        puts(buffer);*/
    }
    
    return 0;
}





