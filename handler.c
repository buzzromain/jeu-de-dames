#include "Entete.h"

char * getSubRequest(char * request, char separator)
{
    char *  subRequest = strchr(request, separator);
    if (subRequest != NULL)
    {
        return (subRequest + 1);
    }

    return NULL;
}

void gameGestionHandeling(Game * gameList, char * request)
{
    if(request != NULL){
        printf("\n\x1b[33m[Son]:\x1b[0m Gestion: %s  ",request);

        char * gameName = getSubRequest(request, '*');

        switch(request[0]) {
            case '1' :
                printf("\n\x1b[34m[Son]:\x1b[0m  Création d'ne partie nommé %s",gameName);
                fflush(stdout);
                break;
            case '2' :
                printf("\n\x1b[34m[Son]:\x1b[0m  Je veux regarder une partie %s",gameName);
                fflush(stdout);
                break;
            default :
                printf("\n\x1b[36m[Son]:\x1b[0m The heck !: ");
                fflush(stdout);
        }
    }
    else{
        printf("\n\x1b[36m[Son]:\x1b[0m The heck !:%s  ",request);
    }

}

void gameMoveHandeling(Game * gameList, char * request)
{
    if(request != NULL){

        int posX = request[0] - '0';
        int posY = request[1] - '0';

        int desX = request[2] - '0';
        int desY = request[3] - '0';

        printf("\n\x1b[33m[Son]:\x1b[0m Move posX:%d, posY:%d, desX,%d, desY,%d  ",posX,posY,desX,desY);

    }
    else{
        printf("\n\x1b[36m[Son]:\x1b[0m The heck !:%s  ",request);
    }

}

int handler(int IdMsgRequest){
    int continuer = TRUE;
    int n = 0;

    m_msg   msg_snd;
    Game * gameList;


    while(continuer == TRUE){

        if( ( n = msgrcv(IdMsgRequest, &msg_snd, sizeof(msg_snd),1 , 0) ) < 0)
        {
            perror("msgrcv()");
            /* if recv error we disonnect the client */
            n = 0;
        }


        if( strstr(msg_snd.text,"quit") !=  NULL ){
            continuer = FALSE;
        }
        switch(msg_snd.text[0]) {
            case '1' :
                gameMoveHandeling(gameList, getSubRequest(msg_snd.text, '*'));
                break;
            case '2' :
                gameGestionHandeling(gameList, getSubRequest(msg_snd.text, '*'));
                break;
            case '3' :
                printf("\n\x1b[35m[Son]:\x1b[0m Partie action: %s  ",msg_snd.text);
                fflush(stdout);
                break;
            default :
                printf("\n\x1b[36m[Son]:\x1b[0m The heck !:%s  ",msg_snd.text);
                fflush(stdout);
        }

    }

    return 0;

}

