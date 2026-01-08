#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define SEM_KEY  24601
#define BOARD_FILE "board.txt"

#define ROWS 6
#define COLS 7
#define BOARD_SIZE (ROWS * COLS)

void player1Logic();
void player2Logic();
int checkBoard(char * board);
void printBoard(char * board);
int updateBoard(char * board,int col);

int  sem_down(int semd);
int  sem_up(int semd);

#endif