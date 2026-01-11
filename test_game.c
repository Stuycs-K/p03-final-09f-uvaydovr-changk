#include "main.h"

int main(void) {
  char board[BOARD_SIZE];
  int i;

  // initialize board to '_'
  for (i = 0; i < BOARD_SIZE; i++) {
    board[i] = '_';
  }

  int currentPlayer = 1;
  char token;

  while (1) {
    printBoard(board);

    int status = checkBoard(board);
    if (status == 1) {
      printf("Player 1 (X) wins!\n");
      break;
    } else if (status == 2) {
      printf("Player 2 (O) wins!\n");
      break;
    } else if (status == -1) {
      printf("Board full, draw.\n");
      break;
    }

    if (currentPlayer == 1) {
      token = 'X';
    } else {
      token = 'O';
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
