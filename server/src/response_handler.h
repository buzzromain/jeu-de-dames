#ifndef response_handler_h
#define response_handler_h

#include "utils.h"

void * reply_create_account(char * code);
void * reply_login(char * code, int nb_won_game);
void * reply_disconnect(char * code);
void * reply_create_game(char * code, char * game_id, char * player_side, int ** board);
void * reply_get_last_game_update(char * code, int ** board);
void * reply_board_game(char * message_type, char * code, int ** board);
void * reply_join_game(char * code, char * game_id, int ** board);
void * reply_move_game(char * code, int ** board);

#endif /* response_handler_h */
