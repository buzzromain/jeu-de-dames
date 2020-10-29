#include "game.h"

int ** initBoard( ){ 

    int ** tab = malloc(sizeof(* tab)*10);
    for(int i=0;i<10;i++){
        tab[i] = malloc(sizeof(int)*10);
    }
    
    // On initialise le tableau
    /*
    0 --> vide
    1 --> noir
    2 --> blanc
    */
    for(int i=0;i<4;i++){
        for(int y=0;y<10;y++){
            if ( (i + y) % 2 == 0){
                tab[i][y] = 1;
            }
            else{
                tab[i][y] = 0;
            }
        }
    }

    for(int i=4;i<6;i++){
        for(int y=0;y<10;y++){
            tab[i][y] = 0;
        }
    }

    for(int i=6;i<10;i++){
        for(int y=0;y<10;y++){
            if ( (i + y) % 2 == 0){
                tab[i][y] = 2;
            }
            else{
                tab[i][y] = 0;
            }
        }
    }
    
    return(tab);

}

void printBoard(int ** tab){ 

    printf("\n");
    for(int i=0;i<10;i++){
        for(int y=0;y<10;y++){
            printf(" %d{x:%d,y:%d} |",tab[i][y],i,y);
        }
        printf("\n\n");
    }

}

int isVictory(int ** tab){ 

    int nbrNoir = 0;
    int nbrBlanc = 0;


    for(int i=0;i<10;i++){
        for(int y=0;y<10;y++){
            int c = tab[i][y];
            if( (c == 1) || (c == 3) ){
                nbrNoir ++ ;  
            }
            else if( (c == 2) || (c == 4) ){
                nbrBlanc ++;
            }
        }
    }

    if(nbrBlanc  = 0){
        return 1;
    }
    if(nbrNoir  = 0){
        return 2;
    }
    else{
        return 0;
    }

}

void mandatoryTake(int ** tab){ 

/* 
TODO
*/

}



int moveQueen(int ** tab,int couleur,int pawnX,int pawnY,int destX,int destY){ 
    
    
    int Origine = pawnX*5 + pawnY;
    int Destination = destX*5 + destY;
    int ratio = Origine - Destination;

    /*Nécessaire pour parcourir le chemin entre le pion et ça destination*/
    int destX0 = destX;
    int destY0 = destY;

    /*Coordonner du dernier pion rencontré sur le chemin*/
    int lastPawnMeetX = 0;
    int lastPawnMeetY = 0;

    /*Nombre de pions rencontré sur le chemin*/
    int nbrPawnMeet = 0;

    if( abs(ratio)%6 == 0 ){
        if( ratio > 0 ){
            while( (pawnX != destX0) && (pawnY != destY0)){

                if( (tab[destX0][destY0] == couleur) || (tab[destX0][destY0] == couleur+2) ){
                    return -1;
                }
                else if(tab[destX0][destY0] != 0){
                    lastPawnMeetX = destX0;
                    lastPawnMeetY = destY0;
                    nbrPawnMeet ++;
                }
                destX0 ++;
                destY0 ++;
            }
            
            if( nbrPawnMeet == 1 ){
                
                tab[pawnX][pawnY] = 0;
                tab[lastPawnMeetX][lastPawnMeetY] = 0;
                tab[destX][destY] = couleur+2;
                return(1);
            }
            else{
                return(0);
            }
            
            
        }
        else{
            while( (pawnX != destX0) && (pawnY != destY0)){
                
                if( (tab[destX0][destY0] == couleur) || (tab[destX0][destY0] == couleur+2) ){
                    return -1;
                }
                else if(tab[destX0][destY0] != 0){
                    lastPawnMeetX = destX0;
                    lastPawnMeetY = destY0;
                    nbrPawnMeet ++;
                }
                destX0 --;
                destY0 --;
            }
            if( nbrPawnMeet == 1 ){
                tab[pawnX][pawnY] = 0;
                tab[lastPawnMeetX][lastPawnMeetY] = 0;
                tab[destX][destY] = couleur+2;
                return(1);
            }
            else{
                return(0);
            }
        }
    }
    else if( abs(ratio)%4 == 0){
        if( ratio < 0 ){
            while( (pawnX != destX0) && (pawnY != destY0)){
                
                if( (tab[destX0][destY0] == couleur) || (tab[destX0][destY0] == couleur+2) ){
                    return -1;
                }
                else if(tab[destX0][destY0] != 0){
                    lastPawnMeetX = destX0;
                    lastPawnMeetY = destY0;
                    nbrPawnMeet ++;
                }
                destX0 --;
                destY0 ++;
            }
            if( nbrPawnMeet == 1 ){
                tab[pawnX][pawnY] = 0;
                tab[lastPawnMeetX][lastPawnMeetY] = 0;
                tab[destX][destY] = couleur+2;
                return(1);
            }
            else{
                return(0);
            }
        }
        else{
            while( (pawnX != destX0) && (pawnY != destY0)){
                
                if( (tab[destX0][destY0] == couleur) || (tab[destX0][destY0] == couleur+2) ){
                    return -1;
                }
                else if(tab[destX0][destY0] != 0){
                    lastPawnMeetX = destX0;
                    lastPawnMeetY = destY0;
                    nbrPawnMeet ++;
                }
                destX0 ++;
                destY0 --;
            }
            if( nbrPawnMeet == 1 ){
                tab[pawnX][pawnY] = 0;
                tab[lastPawnMeetX][lastPawnMeetY] = 0;
                tab[destX][destY] = couleur+2;
                return(1);
            }
            else{
                return(0);
            }
        }
    }
    else{
        return(-1);
    }


}


int movePawn(int ** tab,int couleur,int pawnX,int pawnY,int destX,int destY){ 
    
    int Origine = pawnX*5 + pawnY;
    int Destination = destX*5 + destY;
    int ratio = Origine - Destination;


    if( abs(ratio) == 6 || abs(ratio) == 4){
        
        tab[destX][destY] = couleur;
        tab[pawnX][pawnY] = 0;
        return(1);
    }
    else if( abs(ratio) == 12 ){
        if( ratio > 0 ){
            tab[pawnX][pawnY] = 0;
            tab[pawnX-1][pawnX-1] = 0;
            tab[destX][destY] = couleur;
            return(1);
        }
        else{
            
            tab[pawnX][pawnY] = 0;
            tab[pawnX+1][pawnX+1] = 0;
            tab[destX][destY] = couleur;
            return(0);
        }
    }
    else if( abs(ratio) == 8){
        if( ratio < 0 ){
            tab[pawnX][pawnY] = 0;
            tab[pawnX+1][pawnX-1] = 0;
            tab[destX][destY] = couleur;
            return(1);
        }
        else{
            tab[pawnX][pawnY] = 0;
            tab[pawnX-1][pawnX+1] = 0;
            tab[destX][destY] = couleur;
            return(0);
        }
    }
    else{
        return(-1);
    }

}

int move(int ** tab,int couleur,int pawnX,int pawnY,int destX,int destY){ 
    
    int Origine = pawnX*5 + pawnY;
    int Destination = destX*5 + destY;
    int ratio = Origine - Destination;
    int result;
    

    if( Origine > 50 || Destination > 50 || Origine < 0 || Destination < 0 ||  tab[destX][destY] != 0){
        return(-1);
    }
    else if(tab[pawnX][pawnY] == couleur ){
        result = movePawn(tab, couleur, pawnX, pawnY, destX, destY);
    }
    else if(tab[pawnX][pawnY] == (couleur+2) ){
        result = moveQueen(tab, couleur, pawnX, pawnY, destX, destY);
    }
    else{
        return -1;
    }

    return result;

}

void convertQueen(int ** tab){ 

    for(int y=0;y<10;y++){
        if( tab[0][y] == 2){
            tab[0][y] == 4;
        }
    }
    
    for(int y=0;y<10;y++){
        if( tab[9][y] == 1){
            tab[9][y] == 3;
        }
    }

}

int main(){
/* 
    int ** refBoard = initBoard( );

    for(int i=0;i<10;i++){
        for(int y=0;y<10;y++){
            refBoard[i][y] = 0;
        }
    }

    refBoard[5][5] = 4;
    refBoard[3][3] = 3;

    printBoard(refBoard);

    move(refBoard,2, 5, 5, 1, 1) ;

    printBoard(refBoard);

    
    while(isVictory(refBoard) == 0){ 

        printBoard(refBoard);
        mandatoryTake(refBoard);
        move(refBoard,2, 6, 2, 5, 3) ;
        printBoard(refBoard);
        move(refBoard,2, 5, 3, 4, 4) ;
        printBoard(refBoard);
        move(refBoard,1, 3, 3, 5, 5) ;
        printBoard(refBoard); 

         printBoard(refBoard);
        mandatoryTake(refBoard);
        while( move(refBoard,1, pawnX, pawnY, destX, destY) != 1 ){
            
        } 

     } 
    printf("GG %d \n",isVictory(refBoard));
 */
    return 0;
}
