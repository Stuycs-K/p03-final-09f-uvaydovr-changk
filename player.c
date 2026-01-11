#include "networking.h"


void playerLogic(int server_socket, int playerTurn){
  printf("Connecting to Player %d...\n", playerTurn);

  char token;
  char oppToken;
  int oppositePlayer;

  char board[BOARD_SIZE];
  for (i = 0; i < BOARD_SIZE; i++) {
    board[i] = '_';
  }

  if (playerTurn == 1) {
      printf("Your token is X\n\n");
      token = 'X';
      opp_token = 'O';
      oppositePlayer = 2;
  } elseif (playerTurn == 2) {
      printf("Your token is O\n\n");
      token = 'O';
      opp_token = 'X';
      oppositePlayer = 1;
  }

  int status = 0;

  if (playerTurn == 1) {
    while (1) {
      printBoard(board);
      status = checkBoard(board);
      if (status == 1) {
        printf("You win! \n");
        break;
      } else if (status == 2) {
        printf("Player %d wins!\n", oppositePlayer);
        break;
      } else if (status == -1) {
        printf("Board full. Draw.\n");
        break;
      }

      int col;
      printf("Which column do you want to put a piece in?\n");
      scanf("%d",&col);
      while(updateBoard(board,col)==-1){ //main.c
        printf("Column %d is already filled. Please enter a column with space for a new piece:\n",col);
        scanf("%d",&col);
      }
    }

    send(server_socket, &col, sizeof(col), 0);

    status = checkBoard(board);
    if (status == 1) {
      printBoard(board);
      printf("You win!\n");
      break;
    } else if (status == -1) {
      printBoard(board);
      printf("Board full. Draw.\n");
      break;
    }

     

  }

}
