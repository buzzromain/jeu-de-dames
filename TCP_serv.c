#include "Entete.h"

int init_connection(int port){
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

void send_client(int sock, const char *buffer)
{
   if(send(sock, buffer, strlen(buffer), 0) < 0)
   {
      perror("send()");
      exit(errno);
   }
}



int servTCP(int socketServ,int IdMsgRequest){
    

    char buffer[BUFFER_SIZE];
    

    int actual = 0;
    int max = socketServ;
    int continuer = TRUE;
    
    Client clients[MAX_CLIENTS];

    fd_set rdfs;

    m_msg   msg_snd;

    while(continuer == TRUE)
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

                    if(n == 0)
                    {
                        close(clients[i].sock);
                        memmove(clients + i, clients + i + 1, (actual - i - 1) * sizeof(Client));
                        actual--;
                    }
                    else
                    {
                        sprintf(msg_snd.text, "%s", buffer);
                        msg_snd.socket = clients[i].sock;
                        msg_snd.type = 1;

                        msgsnd(IdMsgRequest, &msg_snd, sizeof(msg_snd), 0);
                        /* printf("\n\x1b[32m[Father]:\x1b[0m Send: %s,!%d  ",msg_snd.text,msg_snd.socket); */
                        fflush(stdout);
                    }
                    if( strstr(buffer,"quit") !=  NULL ){
                        continuer = FALSE;
                    }
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


