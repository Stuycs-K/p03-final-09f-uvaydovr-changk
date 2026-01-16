#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>

#define ROWS 6
#define COLS 7
#define BOARD_SIZE (ROWS * COLS)
#define COLOR_RESET  "\x1b[0m"
#define COLOR_RED    "\x1b[31m"
#define COLOR_CYAN   "\x1b[36m"
#define COLOR_GREEN  "\x1b[32m"
#define COLOR_BOLD   "\x1b[1m"

char checkBoard(char * board);
void printBoard(char * board);
int updateBoard(char * board,int col, char token);

#endif
