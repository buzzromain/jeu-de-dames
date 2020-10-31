#ifndef utils_h
#define utils_h

int int_to_ascii(int number);
void blue_text_color();
void red_text_color();
void reset_text_color();
void print_white_draughts_man();
void print_white_draughts_king();
void print_black_draughts_man();
void print_black_draughts_king();
int * parse_position(char * stringify_position);
int ** get_positions_by_parsing_user_input(char * user_input);

#endif /* utils_h */
