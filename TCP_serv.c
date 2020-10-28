#include "TCP_serv.h"

void writeToGame(int * fildes,const char * buffer)
{
    if (write(fildes[1], buffer, GAME_BUFFER_SIZE) < 0) // On écrit le contenu de buf dans le pipe.
    {
            perror("Erreur ecriture" );  // Si l'écriture est impossible.
            exit(1);
    }
}

void readFromServ(int * fildes)
{
    char buf[20];
    int count;
    if ((count = read(fildes[0], buf, GAME_BUFFER_SIZE) < 0)) // On lit le contenu du pipe.
    {
            perror("Erreur lecture" ); // Si la lecture est impossible.
            exit(1);
    }
    printf("Message réceptionné : %s\n", buf);           

}

static int init_connection(int port){
    int socketServ;

    socketServ = socket(AF_INET, SOCK_STREAM, 0);
    
    if(socketServ == -1){
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

	if (bind(socketServ, (struct sockaddr *)&sin, sizeof(struct sockaddr_in))  == -1) {
		perror("\n\x1b[31m[Error]: bind() failed:  \x1b[0m");
        exit(errno);
	}
	
	if(listen(socketServ, MAX_CLIENTS) == -1){
        perror("\n\x1b[31m[Error]: listen() failed:  \x1b[0m");
        exit(errno);
    }

   return socketServ;
}


int servTCP(int socketServ,int * fildes){
    

    char buffer[BUFFER_SIZE];

    int actual = 0;
    int max = socketServ;
    
    Client clients[MAX_CLIENTS];

    fd_set rdfs;

    while(1)
    {


        int i = 0;
        FD_ZERO(&rdfs);


        /* add STDIN_FILENO */
        FD_SET(STDIN_FILENO, &rdfs);

        /* add the connection socket */
        FD_SET(socketServ, &rdfs);

        /* add socket of each client */
        for(i = 0; i < actual; i++)
        {
            FD_SET(clients[i].sock, &rdfs);
        }

        if(select(max + 1, &rdfs, NULL, NULL, NULL) == -1)
        {
            perror("select()");
            exit(errno);
        }

        if(FD_ISSET(socketServ, &rdfs))
        {
            /* new client */
            struct sockaddr_in socketAdressClient = { 0 };
            int sinsize = sizeof(socketAdressClient);
            int socketClient = accept(socketServ, (struct sockaddr  *)&socketAdressClient,&sinsize);
            if(socketClient == -1)
            {
                perror("accept()");
                continue;
            }

            /* what is the new maximum fd ? */
            max = socketClient > max ? socketClient : max;

            FD_SET(socketClient, &rdfs);

            Client c = { socketClient };
            clients[actual] = c;
            actual++;
        }
        else
        {
            int n = 0;
            int i = 0;
            for(i = 0; i < actual; i++)
            {
                /* a client is talking */
                if(FD_ISSET(clients[i].sock, &rdfs))
                {
                Client client = clients[i];

                n = 0;

                if((n = recv(client.sock, buffer, BUFFER_SIZE - 1, 0)) < 0)
                {
                    perror("recv()");
                    /* if recv error we disonnect the client */
                    n = 0;
                }

                buffer[n] = 0;   

                /* Envoie du client à une fonction de traitement.  protocole.c ?  */

                writeToGame(fildes,buffer);
                break;

                }
            }
        }
    }

    int i = 0;
    for(i = 0; i < actual; i++)
    {
        close(clients[i].sock);
    }

    close(socketServ);

	return 0;
}




int main(){

    pid_t id;

    int fildes[2];

    pipe(fildes);

    id = fork();
    
    if (id == 0) // On est dans le fils.
    {
            close(fildes[1]); // Fermer "write" end du pipe.

            while(1)
            {
                readFromServ(fildes);         
            }
            sleep(2); 
                
                
            close(fildes[0]); // Fermer "read end" du pipe.
            exit(0);

    } 
    
    else // On est dans le père.
    {

            close(fildes[0]); // Fermer "read-end" du pipe.
                
            fflush( stdout );

            int socketServ = init_connection(1234);
            servTCP(socketServ,fildes);

            close(fildes[1]); // Fermer "write" end du pipe.
                
            id = wait(NULL); // On attend la terminaison du fils.

    }

	

    return 0;
}
