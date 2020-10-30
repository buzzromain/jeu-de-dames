#ifndef request_handler_h
#define request_handler_h

#include "utils.h"
#include "game.h"

void * get_message_type(char * request);
void * handle_create_account(char * request);
void * handle_login(char * request);
void * handle_disconnect(char * request);
void * handle_start_game(char * request);
void * handle_request(char * request);

#endif /* request_handler_h */
