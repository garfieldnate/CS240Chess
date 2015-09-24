#ifndef CHESS_CONSTANTS
#define CHESS_CONSTANTS

#define BOARD_SIZE 8
#define NUM_OF_PIECES 32

//col positions for pieces
#define CASTLE_1_LOC 0
#define KNIGHT_1_LOC 1
#define BISHOP_1_LOC 2
#define QUEEN_LOC 4
#define KING_LOC 3
#define BISHOP_2_LOC 5
#define KNIGHT_2_LOC 6
#define CASTLE_2_LOC 7

#define WHITE_MAIN_ROW 7
#define WHITE_PAWN_ROW 6

#define BLACK_PAWN_ROW 1
#define BLACK_MAIN_ROW 0

//colors
#define WHITE 0
#define BLACK 1

#define WHITE_TEXT "white"
#define BLACK_TEXT "black"

//directios
#define WHITE_DIRECTION -1
#define BLACK_DIRECTION 1

//player types
#define HUMAN 0
#define COMPUTER 1

#endif
