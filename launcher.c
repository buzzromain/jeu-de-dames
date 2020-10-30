#include "Entete.h"

void main(){

    pid_t id;
    key_t requestKey = ftok(KEY,'E');

    int IdMsgRequest;


    id = fork();
    
    if (id == 0) // On est dans le fils.
    {

        IdMsgRequest = msgget(requestKey, 0666);
        if(IdMsgRequest == -1 )  
        {
                perror("\x1b[31mmsgget\x1b[0m");
        }

        handler(IdMsgRequest);

        exit(0);

    } 
    
    else // On est dans le père.
    {
        
        IdMsgRequest = msgget(requestKey,IPC_CREAT| 0666);
        if(IdMsgRequest == -1 )  
        {
                perror("\x1b[31mmsgget\x1b[0m");
        }
        
        int socketServ = init_connection(1237);
        servTCP(socketServ,IdMsgRequest);

        msgctl(IdMsgRequest, IPC_RMID, NULL);

        id = wait(NULL); // On attend la terminaison du fils.

        exit(0);

    }

}
