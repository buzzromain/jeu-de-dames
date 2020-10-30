#ifndef db_h
#define db_h

#define DB_PATH "user_db.txt"

int is_user_exist(char * username);
void * db_login_user(char * username, char * password);
void * db_register_new_user(char * username, char * password);
char * get_username_by_id(char * id);
int get_number_won_game_by_id(char * id);

#endif /* db_h */
