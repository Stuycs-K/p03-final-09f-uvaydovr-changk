#include "networking.h"
#include "game.h"

void playerLogic(int server_socket, int playerTurn){
  char token;
  char oppToken;
  int oppositePlayer;

  char board[BOARD_SIZE];
  for (int i = 0; i < BOARD_SIZE; i++) {
    board[i] = '_';
  }

  if (playerTurn == 1) {
      printf("Your token is X\n\n");
      token = 'X';
      oppToken = 'O';
      oppositePlayer = 2;
  } else if (playerTurn == 2) {
      printf("Your token is O\n\n");
      token = 'O';
      oppToken = 'X';
      oppositePlayer = 1;
  } else {
    printf("Invalid player number %d.\nPlease input either 1 or 2\n", playerTurn);
    return;
  }

  int rBuff = 0;
  int sBuff = 0;

  printf("Connecting to Player %d...\n", oppositePlayer);
  int r = recv(server_socket, &rBuff,sizeof(rBuff),0);
  err(r, "recv");
  printf("Connected to Player %d!\n\n", oppositePlayer);

  int currentTurn = 1;
  while(1){
    printBoard(board); //main.c

    char result = checkBoard(board);  //function in main.c
    if (result == token) {
      printf("You win!\n");
      break;
    } else if (result == oppToken) {
      printf("Player %d wins!\n", oppositePlayer);
      break;
    } else if (result == 'D') {
      printf("Board full. Draw.\n");
      break;
    }
    int col;
    if (currentTurn == playerTurn) {
      printf("Which column do you want to put a piece in?\n");
      if (scanf("%d", &col) != 1) {
        printf("Input error, quitting.\n");
        return;
      }

      while(updateBoard(board,col, token)==-1){ //main.c
        if(col>6||col<0){
          printf("Column %d does not exist. Please enter a valid column number:\n",col);
        }
        else{
          printf("Column %d is already filled. Please enter a column with space for a new piece:\n",col);
        }
        if (scanf("%d", &col) != 1) {
          printf("Input error, quitting.\n");
          return;
        }
      }

      sBuff=col;
      int s=send(server_socket,&sBuff,sizeof(sBuff),0);
      err(s,"send error");
    } else {
      printf("Player %d is taking their turn...\n\n", oppositePlayer);
      int r=recv(server_socket, &rBuff,sizeof(rBuff),0);
      err(r,"recv error");
      col=rBuff;
      updateBoard(board,col, oppToken);
    }

    if (currentTurn == 1) {
      currentTurn = 2;
    } else {
      currentTurn = 1;
    }
  }
}

int main(int argc, char *argv[]) {
  char *IP = "127.0.0.1";
  int pNum=0;
  if(argc==1){
    printf("Add argument '1' to be Player 1\n");
    printf("Add argument '2' to be Player 2\n");
    return -1;
  }
  pNum=(int) strtol(argv[1],NULL,10);
  int sd = player_tcp_handshake(IP);

  if (sd < 0) { printf("connect failed\n"); return 1; }
  printf("Connected to server\n\n");

  playerLogic(sd,pNum);

  close(sd);

  return 0;
}
