#ifndef db_h
#define db_h

#define DB_PATH "user_db.txt"

struct db_user {
    char * id;
    char * username; 
    char * password;
    int nb_won_game;
};
typedef struct db_user db_user;

/*
    Fonction utilitaires
*/
int db_is_user_exist(char * username);
char * get_username_by_id(char * id);
int get_nb_won_game_by_id(char * id);

/*
    Fonctions principales de la base de données
*/
void * db_login_user(char * username, char * password);
void * db_register_new_user(char * username, char * password);
int update_nb_won_game(char * id, int new_nb_won_game);


#endif /* db_h */
