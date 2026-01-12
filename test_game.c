#include "game.h"

int main(void) {
  char board[BOARD_SIZE];
  int i;

  // initialize board to '_'
  for (i = 0; i < BOARD_SIZE; i++) {
    board[i] = '_';
  }

  int currentPlayer = 1;
  char token;
  char oppToken;

  while (1) {
    printBoard(board);

    if (currentPlayer == 1) {
      token = 'X';
      oppToken = 'O';
    } else {
      token = 'O';
      oppToken = 'X';
    }


    char result = checkBoard(board);  //function in main.c
    printf("CHECKBOARD: %c \n", result);
    if (result == token) {
      printf("You win!\n");
      break;
    } else if (result == oppToken) {
      printf("Player 2 wins!\n");
      break;
    } else if (result == 'D') {
      printf("Board full. Draw.\n");
      break;
    }

    printf("Player %d (%c), choose a column (0-%d): ", currentPlayer, token, COLS - 1);
    int col;
    if (scanf("%d", &col) != 1) {
      printf("Input error, quitting.\n");
      break;
    }

    while (updateBoard(board, col, token) == -1) {
      printf("Full Column. Try another column: ");
      if (scanf("%d", &col) != 1) {
        printf("Input error, quitting.\n");
        return 0;
      }
    }

    if (currentPlayer == 1) {
      currentPlayer = 2;
    } else {
      currentPlayer = 1;
    }
  }

  return 0;
}
