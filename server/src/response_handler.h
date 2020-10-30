#ifndef response_handler_h
#define response_handler_h

void * reply_create_account(char * code);
void * reply_login(char * code);
void * reply_disconnect(char * code);
void * reply_board_game(char * message_type, char * code, int ** board);
void * reply_start_game(char * code, int ** board);
void * reply_move_game(char * code, int ** board);

#endif /* response_handler_h */
