#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

void player1Logic();
void player2Logic();
int checkBoard(char * board);
void printBoard(char * board);
int updateBoard(char * board,int col);
