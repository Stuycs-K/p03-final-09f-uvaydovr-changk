#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>

#define ROWS 6
#define COLS 7
#define BOARD_SIZE (ROWS * COLS)

void playerLogic();
int checkBoard(char * board);
void printBoard(char * board);
int updateBoard(char * board,int col);

#endif
