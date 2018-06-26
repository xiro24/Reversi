#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "player.h"

#define BOARD_HEIGHT 8
#define BOARD_WIDTH BOARD_HEIGHT
#define BOUNDARY 7

void initBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH]);
void displayBoard(
    Cell board[BOARD_HEIGHT][BOARD_WIDTH], Player * first, Player * second);
 

#endif
