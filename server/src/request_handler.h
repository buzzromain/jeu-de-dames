#ifndef request_handler_h
#define request_handler_h

#include "game.h"

void * get_message_type(char * request);
void * handle_create_account(char * request);
void * handle_request(char * request);

#endif /* request_handler_h */
